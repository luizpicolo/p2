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
				DataTableReader(const std::wstring &pathname);
				//double parseStringToDouble(string value);
				void execute() override;

			private:
				std::wstring pathname;
				//static double parseStringToDouble(const std::wstring &s);
		};
	}
}
