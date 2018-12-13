#pragma once

#include "DataTable.h"
#include "Projection.h"
#include "Filter.h"

namespace cg
{
	namespace vis
	{
        class ProjectionFilter : public Filter<DataTable, DataTable>
        {
			private:
				Reference<Projection> _projection;
            public:
				void execute() override {
					_projection->setInput(this->input());
					_projection->project();
					this->setOutput(_projection->output());
				}

				void setProjection(Projection* projection) {
					_projection = projection;
				}

                static Reference<ProjectionFilter> New()
                {
                    return new ProjectionFilter;
                }
        };
	}
}
