#pragma once

#include "DataTable.h"
#include "Filter.h"
#include "Lamp.h"

namespace cg
{
	namespace vis
	{
        class ProjectionFilter : public Filter<DataTable, DataTable>
        {
            public:
                // Ainda será adicionado o tipo
                // void projection;
            
                // projectionFilter->setProjection(Lamp::New());
                // Ainda será adicionado o tipo
                void setProjection(Lamp projection);
                Eigen::MatrixXf project();
                static Reference<ProjectionFilter> New()
                {
                    return new ProjectionFilter;
                }
        };
	}
}
