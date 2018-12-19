#pragma once

#include "Projection.h"
#include "RandomSampler.h"
#include "DataTable.h"

namespace cg
{
	namespace vis
	{
        class Lamp : public Projection
        {
			private:
				Reference<Sampler> sampler = nullptr;
				Reference<DataTable> sampledata = nullptr;
				Reference<DataTable> sampleproj = nullptr;
				const double epsilon = 1.0e-4;
				float fracdelta = 8.0f;
				int nriteractions = 100;
				int samplesize = 0;

				Reference<DataTable> getSampleData();
				void projectSample();
				void createTransformation(Eigen::MatrixXf& projection, Eigen::MatrixXf& matrix, int begin, int end);

            public:
				Lamp(int dimension) :Projection(dimension) {
				}

				Lamp(DataTable* input, int dimension) :Projection(input, dimension) {
				}

                static Reference<Lamp> New(int dimension)
                {
                    return new Lamp(dimension);
                }

				static Reference<Lamp> New(DataTable* input, int dimension) {
					return new Lamp(input, dimension);
				}

				float getFractionDelta() {
					return fracdelta;
				}

				void setFractionDelta(float fracdelta) {
					this->fracdelta = fracdelta;
				}

				int getNumberIteractions() {
					return nriteractions;
				}

				void setNumberIterations(int nriteractions) {
					this->nriteractions = nriteractions;
				}

				int getSampleSize()
				{
					return samplesize;
				}

				void setSampleSize(int samplesize)
				{
					this->samplesize = samplesize;
				}

				void setSampler(Sampler* sam) {
					sampler = sam;
				}

				void project() override;
        };
	}
}
