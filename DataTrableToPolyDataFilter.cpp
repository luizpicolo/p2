#include "DataTableToPolyDataFilter.h"

namespace cg
{
    namespace vis
    {
        void DataTableToPolyDataFilter::execute()
        {
          auto output = new PolyData;
            auto input = this->input();
            auto points = input->getData();

            if (input->getDimension() > 2) {
                for (size_t i = 0; i < points.rows(); i++)
                {
                    Eigen::VectorXf p = points.row(i);
                    output->addPoint(vec3f{ p(0), p(1), p(2) });
                }
            }
            else if (input->getDimension() == 2) {
                for (size_t i = 0; i < points.rows(); i++)
                {
                    Eigen::VectorXf p = points.row(i);
                    output->addPoint(vec3f{ p(0), p(1) });
                }
            }
            else if (input->getDimension() == 1) {
                for (size_t i = 0; i < points.rows(); i++)
                {
                    Eigen::VectorXf p = points.row(i);
                    output->addPoint(vec3f{ p(0), 0 });
                }
            }
            else {
                puts("BAD DIMENSION FILTER");
            }

          this->setOutput(output);
          puts("GRID2 TO POLY DATA FILTER EXECUTED");
        }
    }
}
