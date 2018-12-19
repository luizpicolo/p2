#include "DataTableWriter.h"
#include "DataTable.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace cg
{
	namespace vis
	{
		void DataTableWriter::setFilename(char* pathname_)
		{
			pathname = pathname_;
		}
		
		void DataTableWriter::writeData()
		{
			const char* DY = "DY";
			const char* DELIMITED = ";";
			vector <string> ids;
			vector <double> labels;
			int length, dimension;
			ofstream dataFile(this->pathname);

			cout << "\nCreating File to Save Data: " << this->pathname;

			if (!dataFile.is_open())
                //throw exception("Error: Unable to open file\n");

			dataFile << DY << endl;
		
			DataTable *table = input();
			ids = table->getRowIds();
			labels = table->getRowLabels();

			if (ids.empty()) {
				table->setDefaultRowIds();
				ids = table->getRowIds();
			}

			if (labels.empty()) {
				table->setDefaultRowLabels();
				labels = table->getRowLabels();
			}

			length = table->getLength();
			dataFile << length << endl;

			dimension = table->getDimension();
			dataFile << dimension << endl << endl;

			for (int i = 0; i < length; i++) {
				dataFile << ids[i] << DELIMITED;

				for (int j = 0; j < dimension; j++) {
					dataFile << table->getEntry(i, j) << DELIMITED;
				}

				dataFile << labels[i] << endl;
			}

			dataFile.close();
		} 
		
	}
}
