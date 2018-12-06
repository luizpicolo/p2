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

		double parseStringToDouble(string value) {

			if (value == "\n" || value == "") {
				cout << "Error: String empty or \\n - change for zero to debug tests";
				return 0;
			}

			return stod(value);
		}

		void DataTableWriter::write()
		{
			const char* DY = "DY";
			const char* DELIMITED = ";";
			vector <string> ids;
			vector <double> labels;
			int length, dimension;
			ofstream dataFile(this->pathname);

			if (!dataFile.is_open())
                //throw exception("Error: Unable to open file\n");

			dataFile << DY << endl;

			// Criar uma função para receber o dados que serão escritos no arquivo (igual a função pathname) ou usar através do SOURCE
			//auto table = this->outputDataTable;
			//ids = table.getRowIds();
			//labels = table.getRowLabels;

			//length = table.getLength()
			length = 18; // TODO: Remover quando datable estiver compilando apenas para testes
			dataFile << length << endl << endl;

			//dimension = table.getDimension();
			dimension = 2; // TODO: Remover quando datable estiver compilando apenas para testes
			dataFile << dimension << endl;

			for (int i = 0; i < length; i++) {
				//dataFile << ids[i] << DELIMITED;
				dataFile << "id" << i << DELIMITED; // TODO: Remover quando datable estiver compilando apenas para testes

				for (int j = 0; j < dimension; j++) {
					//dataFile << table.getEntry(i, j) << DELIMITED;
					dataFile << 5 << DELIMITED; // TODO: Remover quando datable estiver compilando apenas para testes
				}

				//dataFile << labels[i] << endl;
				dataFile << "label" << i << endl; // TODO: Remover quando datable estiver compilando apenas para testes
			}

			dataFile.close();
		}
	}
}
