#pragma once

#include "Projection.h"

namespace cg
{
	namespace vis
	{
        class Lamp : public Projection
        {
            public:
                static Reference<Lamp> New()
                {
                    return new Lamp;
                }
        };
	}
}
