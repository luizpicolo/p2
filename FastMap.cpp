#include "FastMap.h"

namespace cg {
	namespace vis {
		void FastMap::doTheFastmap(Eigen::MatrixXf& points, Reference<DistanceMatrix> dmat) {
			int currentDimension = 0;

			while (currentDimension < this->dimension) {
				int* lvchoosen = this->chooseDistantObjects(dmat);
				double lvdistance = dmat->getEntry(lvchoosen[0], lvchoosen[1]);

				 //if the distance between the pivots is 0, then set 0 for each instance for this dimension
				if (lvdistance == 0) {
					//for each instance in the table
					for (int lvi = 0; lvi < dmat->getLength(); lvi++) {
						points(lvi, currentDimension) = 0.0;
					}
				} else {
					//if the distance is not equal to 0, then
					//instances iterator
					for (int lvi = 0; lvi < dmat->getLength(); lvi++) {
						double lvxi = (double)((std::pow(dmat->getEntry(lvchoosen[0], lvi), 2)
							+ std::pow(dmat->getEntry(lvchoosen[0], lvchoosen[1]), 2)
							- std::pow(dmat->getEntry(lvi, lvchoosen[1]), 2))
							/ (2 * dmat->getEntry(lvchoosen[0], lvchoosen[1])));

						points(lvi, currentDimension) = lvxi;
					}

					//updating the distances table with equation 4 of Faloutsos' paper (in detail below)
					if (currentDimension < dimension - 1) {
						this->updateDistances(dmat, points, currentDimension);
					}
				}

				//Increase the current dimension
				currentDimension++;
			}
		};

		void FastMap::updateDistances(Reference<DistanceMatrix> dmat, Eigen::MatrixXf& points, int currentDimension) {
			//for each instance
			for (int lvinst = 0; lvinst < dmat->getLength(); lvinst++) {
				//for each another instance
				for (int lvinst2 = lvinst + 1; lvinst2 < dmat->getLength(); lvinst2++) {
					float value = (float)(std::sqrt(std::abs(std::pow(dmat->getEntry(lvinst, lvinst2), 2)
						- std::pow((points(lvinst, currentDimension)
							- points(lvinst2, currentDimension)), 2))));

					dmat->setEntry(lvinst, lvinst2, value);
				}
			}
		}

		int* FastMap::chooseDistantObjects(Reference<DistanceMatrix> dmat) {
			int* choosen = new int[2];
			int x = 0, y = 1;

			for (int i = 0; i < dmat->getLength() - 1; i++) {
				for (int j = i + 1; j < dmat->getLength(); j++) {
					if (dmat->getEntry(x, y) < dmat->getEntry(i, j)) {
						x = i;
						y = j;
					}
				}
			}

			choosen[0] = x;
			choosen[1] = y;

			return choosen;
		}

		void FastMap::normalize(Eigen::MatrixXf& result) {
			int lvdimensions = result.cols();
			int lvinstances = result.rows();

			//for normalization
			double* lvlowrange = new double[lvdimensions];
			double* lvhighrange = new double[lvdimensions];

			//for each instance
			for (int lvins = 0; lvins < lvinstances; lvins++) {
				//for each attribute
				for (int lvfield = 0; lvfield < lvdimensions; lvfield++) {
					//if it is the first instance then assign the first value
					if (lvins == 0) {
						lvlowrange[lvfield] = result(lvins, lvfield);
						lvhighrange[lvfield] = result(lvins, lvfield);
					} else {
						//otherwise compare
						lvlowrange[lvfield] = lvlowrange[lvfield] > result(lvins, lvfield) ? result(lvins, lvfield) : lvlowrange[lvfield];
						lvhighrange[lvfield] = lvhighrange[lvfield] < result(lvins, lvfield) ? result(lvins, lvfield) : lvhighrange[lvfield];
					}
				}
			}

			//for each instance
			for (int lvins = 0; lvins < lvinstances; lvins++) {
				//for each attribute
				for (int lvfield = 0; lvfield < lvdimensions; lvfield++) {
					if ((lvhighrange[lvfield] - lvlowrange[lvfield]) > 0.0) {
						double res = (result(lvins, lvfield) - lvlowrange[lvfield]) /
							(lvhighrange[lvfield] - lvlowrange[lvfield]);
						result(lvins, lvfield) = res;
					} else {
						result(lvins, lvfield) = 0;
					}
				}
			}
		};

		void FastMap::project() {
			Eigen::MatrixXf points(dmat->getLength(), dimension);

			Eigen::MatrixXf dissmatrix(this->dmat->getData());
			DataTable* diss = new DataTable(dissmatrix);

			this->doTheFastmap(points, diss);
			this->normalize(points);

			_output = new DataTable(points);
		}
	}
}