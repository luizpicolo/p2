#pragma once

#include <string>
#include <vector>
#include <any>

namespace cg
{
	namespace vis
	{
		class DataTableReader : public AbstractSource<DataTable*>
		{
			public:
				DataTableReader(const std::wstring &pathname);
				void execute() override;

			private:
				std::wstring pathname;
				static void error(const std::wstring &message, std::vector<std::any> &args);
				static int parseInt(const std::wstring &s);
				static double parseDouble(const std::wstring &s);
		};
	}
}
