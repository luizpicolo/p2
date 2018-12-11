#pragma once

#include "Dissimilarity.h"

namespace cg
{
	namespace vis
    {
		class Euclidean : public Dissimilarity
        {
            public:
                float value(Eigen::VectorXf a, Eigen::VectorXf b)
                {
                    return (a - b).lpNorm<2>();
                }
		};
	}
}
