#include "DataTable.h"
#include "Eigen/Core" 

namespace cg
{
	namespace vis
	{
		int DataTable::count = 0;

		DataTable::DataTable(Eigen::MatrixXf data_)
		{
			length = (int) data_.rows(); // Metodo da biblioteca
			dimension = (int) data_.cols();  // Metodo da biblioteca
			this->data = data_;
		}

		int DataTable::getLength()
		{
		  return length;
		}

		int DataTable::getDimension()
		{
		  return dimension;
		}

		Eigen::MatrixXf DataTable::getData()
		{
		  return data;
		}

		Eigen::MatrixXf& DataTable::getlData()
		{
			return data;
		}

		std::wstring DataTable::getName()
		{
		  return name;
		}

		Eigen::VectorXf DataTable::getRow(int i)
		{
		  return data.row(i);  // Metodo da biblioteca
		}

		std::vector<std::wstring> DataTable::getColumnNames()
		{
		  return columnNames;
		}

		void DataTable::setDefaultColumnNames()
		{
		  if (columnNames.empty())
		  {
			columnNames = std::vector<std::wstring>(length);
		  }

		  for (int i = 0; i < length; i++)
		  {
			columnNames[i] = L"column" + std::to_wstring(i + 1);
		  }
		}

		void DataTable::setColumnNames(std::vector<std::wstring> &columnNames)
		{
		  if (columnNames.size() != dimension)
		  {
			puts("Column names' dimension mismatch");
		  }
		  this->columnNames = columnNames;
		}

		std::vector<std::string> DataTable::getRowIds()
		{
		  return rowIds;
		}

		void DataTable::setDefaultRowIds()
		{
		  if (rowIds.empty())
		  {
			rowIds = std::vector<std::string>(length);
		  }

		  for (int i = 0; i < length; i++)
		  {
			rowIds[i] = std::to_string(i + 1);
		  }
		}

		void DataTable::setRowIds(std::vector<std::string> &rowIds)
		{
		  if (rowIds.size() > 0 && rowIds.size() != length)
		  {
			puts("Row ids' dimension mismatch");
		  }
		  this->rowIds = rowIds;
		}

		std::vector<double> DataTable::getRowLabels()
		{
		  return rowLabels;
		}

		void DataTable::setDefaultRowLabels()
		{
		  if (rowLabels.empty())
		  {
			rowLabels = std::vector<double>(length);
		  }

		  for (int i = 0; i < length; i++)
		  {
			rowLabels[i] = 0;
		  }
		}

		void DataTable::setRowLabels(std::vector<double> &rowLabels)
		{
		  if (rowLabels.size() > 0 && rowLabels.size() != length)
		  {
			puts("Row labels' dimension mismatch");
		  }
		  this->rowLabels = rowLabels;
		}

		void DataTable::setEntry(int i, int j, double d)
		{
			data(i, j) = (float) d;
		}

		float DataTable::getEntry(int i, int j)
		{
			return data(i, j);
		}
		void DataTable::setRow(int i, Eigen::VectorXf row)
		{
			data.row(i) = row;
		}
	}
}
