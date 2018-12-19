#pragma once

#include <cstring>
#include "Projection.h"
#include "DataTable.h"

using DistanceMatrix = cg::vis::DataTable;

namespace cg {
	namespace vis {
		class IDMAP : public Projection {
			public:
				enum InitializationType {
					FASTMAP = 1
				};

				InitializationType getInitialization() {
					return ini;
				}

				void setInitialization(InitializationType ini) {
					this->ini = ini;
				}
				
				float getFractionDelta() {
					return fracdelta;
				}

				void setFractionDelta(float fracdelta) {
					this->fracdelta = fracdelta;
				}

				int getNumberIterations() {
					return nriterations;
				}

				void setNumberIterations(int nriterations) {
					this->nriterations = nriterations;
				}

				IDMAP(int dimension) : Projection(dimension) {
					Eigen::MatrixXf data = Eigen::MatrixXf::Zero(Eigen::Dynamic, Eigen::Dynamic);
					dmat = new DataTable(data);
				}

				IDMAP(DataTable* input, int dimension) :Projection(input, dimension) {
					Eigen::MatrixXf data = Eigen::MatrixXf::Zero(length, length);
					dmat = new DataTable(data);
				}

				void project() override;

			private:
				Reference<DistanceMatrix> dmat;
				InitializationType ini = FASTMAP;
				float fracdelta = 8.0f;
				int nriterations = 50;
		};
	}
}
