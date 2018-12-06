#pragma once

#include <string>
#include <vector>
#include <any>
#include "DataTable.h"
#include "Writer.h"

namespace cg
{
	namespace vis
	{
		class DataTableWriter : public Writer<DataTable>
		{
		public:
			void setFilename(char* pathname);
            virtual void write() override;
			static Reference<DataTableWriter> New()
			{
				return new DataTableWriter;
			}

		private:
			char* pathname;
			
		};
	}
}
