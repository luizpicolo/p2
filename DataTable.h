#pragma once

#include <string>
#include <vector>
#include "Eigen/Core" 
#include "DataSet.h"

namespace cg
{
	namespace vis
	{
		class DataTable : public DataSet
		{
		  private:
			  std::wstring name;
			  int length;
			  int dimension;
			  Eigen::MatrixXf data;
			  std::vector<std::wstring> columnNames;
			  std::vector<std::string> rowIds;
			  std::vector<double> rowLabels;

			  static int count;

		  public:
			  DataTable(Eigen::MatrixXf data);

			  //DataTable(const std::wstring &name, Eigen::MatrixXf data);

			  int getLength();

			  virtual int getDimension();

			  Eigen::MatrixXf getData();

			  std::wstring getName();

			  virtual Eigen::VectorXf getRow(int i);

			  virtual std::vector<std::wstring> getColumnNames();

			  virtual void setDefaultColumnNames();

			  virtual void setColumnNames(std::vector<std::wstring> &columnNames);

			  virtual std::vector<std::string> getRowIds();

			  virtual void setDefaultRowIds();

			  virtual void setRowIds(std::vector<std::string> &rowIds);

			  virtual std::vector<double> getRowLabels();

			  virtual void setDefaultRowLabels();

			  virtual void setRowLabels(std::vector<double> &rowLabels);

			  virtual void setEntry(int i, int j, double d);

			  float getEntry(int i, int j);

			  virtual void setRow(int i, Eigen::VectorXf);

			}; // DataTable
	}
}
