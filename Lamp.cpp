#include <cmath>
#include "Lamp.h"
#include "IDMAP.h"

#include <Eigen/SVD>

namespace cg
{
	namespace vis
	{
		void Lamp::getSampleData() {
			if (samplesize == 0) { //Samplesize cannot be 0, sqrt(length) is an acceptable value
				samplesize = (int)std::sqrt(this->length);
			}

			this->sampler->setInput(_input); //Set the input
			this->sampler->setSampleSize(samplesize);
			this->sampler->sample();

			this->sampledata = this->sampler->getOutput();
		}

		void Lamp::projectSample() {
			//Now we project the sample with IDMAP
			Reference<IDMAP> idmap = new IDMAP(sampledata, dimension);
			idmap->setInput(sampledata);
			idmap->setFractionDelta(fracdelta);
			idmap->setInitialization(IDMAP::InitializationType::FASTMAP);
			idmap->setNumberIterations(nriteractions);
			idmap->project();
			sampleproj = idmap->output();
		}

		void Lamp::createTransformation(Eigen::MatrixXf& projection, Eigen::MatrixXf& matrix, int begin, int end) {
			// dimensions
			int d = matrix.cols();      // origin space: dimension
			int k = sampledata->getLength();    // sampling:  instances
			int r = sampleproj->getDimension();  // projected: dimension

			// scalars
			double Wsum, aij;
			double v00, v10, v01, v11;
			double uj0, uj1, x, y, diff;

			// arrays 1d
			double *W, *Wsqrt;
			double *Psum, *Pstar;
			double *Qsum, *Qstar;

			Eigen::RowVectorXf X, P, Q;

			Pstar = new double[d];
			Qstar = new double[r];

			Eigen::MatrixXf AtB = Eigen::MatrixXf::Zero(d,r);

			int p, i, j;
			for (p = begin; p <= end; p++)
			{
				// point to be projected

				X = matrix.row(p);

				//==============================================================
				// STEP 1: Obtain W, Pstar and Qstar
				//==============================================================
				W = new double[k] {0};
				Wsqrt = new double[k] {0};
				Psum = new double[d] {0};
				Qsum = new double[r] {0};
				Wsum = 0;
				bool jump = false;

				for (i = 0; i < k; i++)
				{
					P = sampledata->getRow(i);
					Q = sampleproj->getRow(i);

					W[i] = 0;
					for (j = 0; j < d; j++)
					{
						W[i] += (X[j] - P[j]) * (X[j] - P[j]);
					}

					// coincident points
					if (W[i] < epsilon)
					{
						projection(p, 0) = Q[0];
						projection(p, 1) = Q[1];
						jump = true;
						break;
					}

					W[i] = 1 / W[i];

					for (j = 0; j < d; j++) {
						Psum[j] = Psum[j] + P[j] * W[i];
					}

					Qsum[0] = Qsum[0] + Q[0] * W[i];
					Qsum[1] = Qsum[1] + Q[1] * W[i];

					Wsum = Wsum + W[i];
					Wsqrt[i] = (float)std::sqrt(W[i]);
				}

				if (jump) {
					continue;
				}

				for (j = 0; j < d; j++) {
					Pstar[j] = Psum[j] / Wsum;
				}

				Qstar[0] = Qsum[0] / Wsum;
				Qstar[1] = Qsum[1] / Wsum;

				//==============================================================
				// STEP 2: Obtain Phat, Qhat, A and B
				//==============================================================
				//calculating AtB
				for (i = 0; i < d; i++) {
					x = 0;
					y = 0;

					for (j = 0; j < k; j++)
					{
						P = sampledata->getRow(j);
						Q = sampleproj->getRow(j);

						aij = (P[i] - Pstar[i]) * Wsqrt[j];

						x = x + (aij * ((Q[0] - Qstar[0]) * Wsqrt[j]));
						y = y + (aij * ((Q[1] - Qstar[1]) * Wsqrt[j]));
					}

					AtB(i, 0) = x;
					AtB(i, 1) = y;
				}

				//==============================================================
				// STEP 3: Projection
				//==============================================================

				// SVD Computation
				Eigen::JacobiSVD<Eigen::MatrixXf> svd(AtB, Eigen::ComputeThinU | Eigen::ComputeThinV);

				Eigen::MatrixXf V = svd.matrixV();
				Eigen::MatrixXf U = svd.matrixU();

				v00 = V(0, 0);
				v01 = V(0, 1);
				v10 = V(1, 0);
				v11 = V(1, 1);

				x = 0;
				y = 0;
				for (j = 0; j < d; j++) {
					diff = (X[j] - Pstar[j]);
					uj0 = U(j, 0);
					uj1 = U(j, 1);

					x += diff * (uj0 * v00 + uj1 * v01);
					y += diff * (uj0 * v10 + uj1 * v11);
				}

				x = x + Qstar[0];
				y = y + Qstar[1];

				// Add point in the projection
				projection(p, 0) = x;
				projection(p, 1) = y;
			}
		}

		void Lamp::project() {
			if (_input == nullptr) //Check if we have input set
				throw std::runtime_error("Input not set");

			puts("");
			puts("Lamp initiated...");

			puts("\tSampling the data...");
			this->getSampleData(); //Sample the data

			puts("\tProjecting the sample...");
			this->projectSample(); //Project it

			puts("\tProjecting...");
			Eigen::MatrixXf proj_aux = Eigen::MatrixXf::Zero(_input->getLength(), dimension);
			createTransformation(proj_aux, _input->getlData(), 0, _input->getLength() - 1);

			//proj_aux = proj_aux * 10; //Scaling

			_output = new DataTable(proj_aux);
		}
	}
}
