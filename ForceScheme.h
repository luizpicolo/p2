#pragma once

#include <vector>
#include "DataTable.h"
#include "Object.h"

using DistanceMatrix = cg::vis::DataTable;

namespace cg {
	namespace vis {
		class ForceScheme : public SharedObject {
			private:
				float fractionDelta;
				int* index;
				const float EPSILON = 0.0000001f;

			public:
				ForceScheme(int dimension, int numberPoints) {
					this->fractionDelta = 8.0f;

					//Create the indexes and shuffle them
					std::vector<int> index_aux;
					for (int i = 0; i < numberPoints; i++) {
						index_aux.push_back(i);
					}

					this->index = new int[numberPoints];
					for (int ind = 0, j = 0; j < numberPoints; ind += (int)index_aux.size() / 10, j++) {
						if (ind >= index_aux.size()) {
							ind = 0;
						}

						this->index[j] = index_aux.at(ind);
						index_aux.erase(index_aux.begin()+ind);
					}
				}

				float iteration(Reference<DistanceMatrix> dmat, Eigen::MatrixXf& proj) {
					float error = 0.0;
					int length = (int)proj.rows();
					int x, y;

					//for each instance
					for (int ins1 = 0; ins1 < length; ins1++) {
						int instance = this->index[ins1];

						//for each other instance
						for (int ins2 = 0; ins2 < length; ins2++) {
							int instance2 = this->index[ins2];

							if (instance == instance2) {
								continue;
							}

							//distance between projected instances
							float x1x2 = (proj(instance2, 0) - proj(instance, 0));
							float y1y2 = (proj(instance2, 1) - proj(instance, 1));
							float dr2 = std::sqrt(x1x2 * x1x2 + y1y2 * y1y2);

							if (dr2 < EPSILON)
								dr2 = EPSILON;

							float drn = dmat->getEntry(instance, instance2);
							float normdrn = (drn - dmat->getData().minCoeff(&x,&y));
							//(dmat.getMaxDistance() - dmat.getMinDistance());

							float max, min;
							max = dmat->getData().maxCoeff(&x, &y);
							min = dmat->getData().minCoeff(&x, &y);
							if ( max > min) {
								normdrn = normdrn / (max - min);
							}

							//Calculating the (fraction of) delta
							float delta = normdrn - dr2;
							delta *= std::abs(delta);
							// delta = (float) Math.sqrt(Math.abs(delta));
							delta /= this->fractionDelta;

							error += std::abs(delta);

							float aux = proj(instance2, 0);
							proj(instance2, 0) = aux + delta * (x1x2 / dr2);
							aux = proj(instance2, 1);
							proj(instance2, 1) = aux + delta * (y1y2 / dr2);
						}
					}
					error /= (length * length) - length;
					return error;
				}
		};
	}
}