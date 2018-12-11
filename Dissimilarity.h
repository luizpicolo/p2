#pragma once

namespace cg
{
	namespace vis
	{
        class Dissimilarity : public SharedObject
        {
            public:
                virtual float value(Eigen::VectorXf a, Eigen::VectorXf b) = 0;
        };
	}
}
