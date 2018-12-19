#pragma once

#include "projection.h"

using DistanceMatrix = cg::vis::DataTable;

namespace cg {
	namespace vis {
		class FastMap : public Projection{
			private:
				Reference<DistanceMatrix> dmat = nullptr;

				void updateDistances(Reference<DistanceMatrix> dmat, Eigen::MatrixXf& points, int currentDimension);
				void doTheFastmap(Eigen::MatrixXf& points, Reference<DistanceMatrix> dmat);
				int* chooseDistantObjects(Reference<DistanceMatrix> dmat);
				void normalize(Eigen::MatrixXf& points);

			public:
				FastMap(int dimension, Reference<DistanceMatrix> dmat): Projection(dimension) {
					this->dmat = dmat;
				}

				void project() override;
		};
	}
}