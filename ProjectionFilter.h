#pragma once

#include "DataTable.h"
#include "Filter.h"
#include "Lamp.h"
#include "Dissimilarity.h"

namespace cg
{
	namespace vis
	{
        class ProjectionFilter : public Filter<DataTable, DataTable>
        {
            public:
                Eigen::MatrixXf project();
                void setProjection(Projection* projection);
                static Reference<ProjectionFilter> New()
                {
                    return new ProjectionFilter;
                }
        };
	}
}
