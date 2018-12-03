#pragma once

#include <string>
#include <vector>
#include <any>
#include "Source.h"
#include "DataTable.h"

namespace cg
{
	namespace vis
	{
		class DataTableReader : public Source<DataTable>
		{
			public:
				void setFilename(char* pathname);
				static Reference<DataTableReader> New()
				{
					return new DataTableReader;
				}

			private:
				char* pathname;
				void execute() override;
		};
	}
}
