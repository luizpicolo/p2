#include "DataTableReader.h"
#include "DataTable.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace cg
{
	namespace vis
	{
		DataTableReader::DataTableReader(const std::wstring &_pathname)
		{
			pathname = _pathname;
		}

		double parseStringToDouble(string value) {

			if (value == "\n" || value == "") {
				cout << "Error: String empty or \\n - change for zero to debug tests";
				return 0;
			}

			return stod(value);
		}

		void DataTableReader::execute()
		{
			vector <string> ids;
			vector <double> labels;
			string line, formatFile, buffer;
			int length, dimension;
			double bufferDouble;
			ifstream dataFile(this->pathname);

			if (!dataFile.is_open())
				cout << "Error: Unable to open file\n";

			getline(dataFile, formatFile);
			if (formatFile != "DY")
				cout << "Error: Unknown data file\n";

			dataFile >> length;
			if (length <= 0)
				cout << "Error: Bad data length\n";

			dataFile >> dimension;
			if (dimension <= 0)
				cout << "Bad data dimension\n";

			cout << "formatFile=" << formatFile << " length=" << length << " dimension=" << dimension << endl;

			// Ignora /n do ultimo número lido e ignora a próxima linha em branco
			getline(dataFile, buffer);
			getline(dataFile, buffer);

			//TODO: Atualizar com as funçoes do EIGIN e da classe DataTable não implementada até o momento
			/*
				data = new Array2DRowRealMatrix(length, dimension);
			DataTable table = new DataTable(data);
			*/

			for (int i = 0; i < length; i++) {
				cout << endl;

				// Pega o ID da linha usando ; como separador e adiciona ao vetor de ids
				getline(dataFile, buffer, ';');
				cout << " ID=" << buffer;
				ids.push_back(buffer);

				for (int j = 0; j < dimension; j++) {
					// Pega o dado da linha usando ; como separador
					getline(dataFile, buffer, ';');
					bufferDouble = parseStringToDouble(buffer);
					cout << " buffer=" << bufferDouble;

					// TODO:Função Datable não implementada ainda
					// data.setEntry(i, j, bufferDouble);
				}

				// Pega o LABEL da linha usando ; como separador e adiciona ao vetor de labels convertido para double
				getline(dataFile, buffer);
				bufferDouble = parseStringToDouble(buffer);
				cout << " LABEL=" << bufferDouble;
				labels.push_back(bufferDouble);
			}

			//TODO: Atualizar com as funçoes da classe DataTable não implementada até o momento
			//table.setRowIds(ids);
			//table.setRowLabels(labels);

			dataFile.close();
		}
	}
}
