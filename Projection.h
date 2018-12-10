#pragma once

#include "DataTable.h"
#include "Dissimilarity.h"
#include "Euclidean.h"

namespace cg
{
	namespace vis
	{
        class Projection : public SharedObject
        {
            public:
				Projection(DataTable* input, int newDimension) :dimension{ newDimension }, _input{ input }, _dissimilarity{ getDefaultDissimilarity() } {
					dataDimension = _input->getDimension();
					length = _input->getLength();
				}

				Projection(int newDimension) :dimension{ newDimension }, _dissimilarity{ getDefaultDissimilarity() } {
				}

				int getDimension() {
					return dimension;
				}
				Dissimilarity* getDissimilarity() {
					return _dissimilarity;
				}
				void setDissimilarity(Dissimilarity* dissimilarity) {
					_dissimilarity = dissimilarity;
				}
				void setInput(DataTable* input) {
					_input = input;
				}
				DataTable* getData() {
					return _output;
				}

                DataTable* output() const
                {
                    return _output;
                }

                virtual void project() = 0;
            
            protected:
                Reference<DataTable> _input;
                Reference<DataTable> _output;
                const int dimension;
                Reference<Dissimilarity> _dissimilarity;
                int dataDimension;
                int length;
				static Dissimilarity* getDefaultDissimilarity() {
					return new Euclidean();
				};
        };
	}
}
