#pragma once

#include "Object.h"
#include "Eigen/Core"
#include "DataTable.h"

namespace cg {
	namespace vis {
		class Sampler : public SharedObject {
			protected:
				int _sampleSize = 0;
				Reference<DataTable> input;
				Reference<DataTable> output;

				virtual Reference<DataTable> doSample() =0;

			public:
				void setInput(Reference<DataTable> in) {
					input = in;
				}

				void setSampleSize(int size) {
					_sampleSize = std::max(1, size);
				}

				void sample() {
					if (input == nullptr)
						throw std::runtime_error("Input not set");
					if (_sampleSize == 0)
						throw std::runtime_error("Sample size not set");

					output = input->getLength() <= _sampleSize ? input : doSample();
				}

				Reference<DataTable> getOutput() {
					return output;
				}
		};
	}
}
