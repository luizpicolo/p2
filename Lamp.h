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
				Reference<Sampler> sampler;

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
            
                void project()
                {
                
                }
        };
	}
}
