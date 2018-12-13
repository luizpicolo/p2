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
                Lamp() : Projection(getDimension())
                {
                    
                }
            
                static Reference<Lamp> New()
                {
                    return new Lamp;
                }
            
                void project()
                {
                
                }
        };
	}
}
