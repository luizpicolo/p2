#include "Filter.h"
#include "PolyData.h"
#include "DataTable.h"

namespace cg
{
    namespace vis
    {
        class DataTableToPolyDataFilter : public Filter<DataTable, PolyData>
        {
            
        public:
            static Reference<DataTableToPolyDataFilter> New()
            {
                return new DataTableToPolyDataFilter;
            }
            
            DataTableToPolyDataFilter()
            {
                // TODO
            }
            
        private:
            void execute() override;
        };
    }
}
