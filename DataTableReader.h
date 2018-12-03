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
		class DataTableReader : public Source<DataTable*>
		{
			public:
				char* pathname;
				void setFilename(char* pathname);
				void execute() override;
				static Reference<DataTableReader> New()
				{
					return new DataTableReader;
				}

			private:
		};
	}
}
