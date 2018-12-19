#include <limits.h>
#include "IDMAP.h"
#include "FastMap.h"
#include "ForceScheme.h"

namespace cg {
	namespace vis {
		void IDMAP::project(){
			Reference<DataTable> projection = nullptr;
			//DistanceMatrix dmat = new DataTable(input.getData(), diss);

			int length = _input->getLength();
			for (int i = 0; i < length; i++)
				for (int j = 0; j < length; j++)
					dmat->setEntry(i, j, this->_dissimilarity->value(_input->getRow(i), _input->getRow(j)));

			if (ini == InitializationType::FASTMAP) {
				FastMap* fastmap = new FastMap(dimension, dmat);
				fastmap->setInput(this->_input);
				fastmap->setDissimilarity(this->_dissimilarity);
				fastmap->project();
				projection = fastmap->output();

				if (projection != nullptr) {
					Reference<ForceScheme> force = new ForceScheme(dimension, projection->getLength());
					double error = std::numeric_limits<double>::max();

					for (int i = 0; i < this->nriterations; i++) {
						error = force->iteration(dmat, projection->getlData());
					}
				}
			}

			_output = projection;
		}
	}
}