#include "DataTableReader.h"
#include "DataTable.h"

namespace cg
{
	namespace vis
	{
		DataTableReader::DataTableReader(const std::wstring &_pathname)
		{
			pathname = _pathname;
		}

		void DataTableReader::execute()
		{
		  // try (Scanner s = new Scanner(new File(pathname)))
		  {
			  File tempVar(pathname);
			  Scanner s = Scanner(&tempVar);
			  try
			  {
				s.useLocale(Locale::US);
				s.useDelimiter(L"[;\\s]");
				if (!s.nextLine().equals(L"DY"))
				{
				  error(L"Unknown data file");
				}
          
				int length = parseInt(s.nextLine());
          
				if (length <= 0)
				{
				  error(L"Bad data length");
				}
          
				int dimension = parseInt(s.nextLine());
          
				if (dimension <= 0)
				{
				  error(L"Bad data dimension");
				}
          
				RealMatrix *data = new Array2DRowRealMatrix(length, dimension);
				DataTable *table = new DataTable(data);
				std::vector<std::wstring> ids(length);
				std::vector<double> labels(length);
          
				{
				  std::wstring line = s.nextLine();
          
				  if (!line.isEmpty())
				  {
				  table->setColumnNames(line.split(L";"));
				  }
				}
				for (int i = 0; i < length; i++)
				{
				  ids[i] = s.next();
				  for (int j = 0; j < dimension; j++)
				  {
					data->setEntry(i, j, s.nextDouble());
				  }
				  labels[i] = parseDouble(s.next());
				  s.nextLine();
				}
				table->setRowIds(ids);
				table->setRowLabels(labels);
				// Adicionar Tipo para Output
				// output = table;
			  }
			  catch (FileNotFoundException | NoSuchElementException e)
			  {
				throw ExecutionException(e);
			  }
				}
		}

		void DataTableReader::error(const std::wstring &message, std::vector<std::any> &args) throw(ExecutionException)
		{
		  throw ExecutionException(message, args);
		}

		int DataTableReader::parseInt(const std::wstring &s) throw(ExecutionException)
		{
		  try
		  {
			return std::stoi(s);
		  }
		  catch (const NumberFormatException &e)
		  {
			throw ExecutionException(e);
		  }
		}

		double DataTableReader::parseDouble(const std::wstring &s) throw(ExecutionException)
		{
		  try
		  {
			return std::stod(s);
		  }
		  catch (const NumberFormatException &e)
		  {
			throw ExecutionException(e);
		  }
		}
	}
}
