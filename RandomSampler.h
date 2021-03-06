#pragma once

#include <random>
#include <set>
#include "Sampler.h"

namespace cg {
	namespace vis {
		class RandomSampler : public Sampler {
			protected:
				Reference<DataTable> doSample() {
					Eigen::MatrixXf data = Eigen::MatrixXf::Zero(_sampleSize, input->getDimension());
					output = new DataTable(data);

					std::random_device rd;
					std::default_random_engine generator(rd());
					std::uniform_int_distribution<int> distribution(1, input->getLength());
					std::set<int> indexes;

					for (int np = input->getLength(), count = 0; count < _sampleSize;) {
						int index = distribution(generator);

                        if (indexes.find(index) != indexes.end())
							continue;

						auto row = input->getRow(index);

						for (int x = 0; x < count; x++) {
							if (row.isApprox(output->getRow(x), (float)0.1))
								continue;
						}

						output->setRow(count, row);
						count++;
					}

					return output;
				}

			public:
				static Reference<RandomSampler> New() {
					return new RandomSampler;
				}

		};
	}
}
