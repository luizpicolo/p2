#pragma once

#include "Object.h"
#include "Eigen/Core"
#include "DataTable.h"

namespace cg {
	namespace vis {
		class Sampler : public SharedObject {
			protected:
				int _sampleSize;
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
					output = input->getLength() <= _sampleSize ? input : doSample();
				}

				Reference<DataTable> getOutput() {
					return output;
				}
		};
	}
}
