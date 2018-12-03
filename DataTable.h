#pragma once

#include <string>
#include <vector>
#include "exceptionhelper.h"
#include "Eigen/Core" 

namespace cg
{
	namespace vis
	{
		class DataTable
		{

	  private:
		  std::wstring name;
		  int length;
		  int dimension;
		  Eigen::Matrix2cd *data;
		  std::vector<std::wstring> columnNames;
		  std::vector<std::wstring> rowIds;
		  std::vector<double> rowLabels;

		  static int count;

	  public:
		  virtual ~DataTable()
		  {
			  delete data;
		  }

		  DataTable(Eigen::Matrix2cd *data);

		  DataTable(const std::wstring &name, Eigen::Matrix2cd *data);

		  int getLength();

		  virtual int getDimension();

		  Eigen::Matrix2cd *getData();

		  std::wstring getName();

		  virtual std::vector<double> getRow(int i);

		  virtual std::vector<std::wstring> getColumnNames();

		  virtual void setDefaultColumnNames();

		  virtual void setColumnNames(std::vector<std::wstring> &columnNames);

		  virtual std::vector<std::wstring> getRowIds();

		  virtual void setDefaultRowIds();

		  virtual void setRowIds(std::vector<std::wstring> &rowIds);

		  virtual std::vector<double> getRowLabels();

		  virtual void setDefaultRowLabels();

		  virtual void setRowLabels(std::vector<double> &rowLabels) throw(ExecutionException);

		}; // DataTable

	}
}
