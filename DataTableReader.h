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
				string pathname;
				//DataTableReader(const std::wstring &pathname);
				void setFilename(const std::wstring &pathname);
				void execute() override;
				static Reference<DataTableReader> New()
				{
					return new DataTableReader;
				}

			private:
				//string pathname;
				//static double parseStringToDouble(const std::wstring &s);
		};
	}
}
