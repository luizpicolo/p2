#pragma once

#include "Projection.h"
#include "RandomSampler.h"

namespace cg
{
	namespace vis
	{
        class Lamp : public Projection
        {
			private:
				Reference<Sampler> sampler;

            public:
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
