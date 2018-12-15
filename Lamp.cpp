#include <cmath>
#include "Lamp.h"
#include "IDMAP.h"

namespace cg
{
	namespace vis
	{
		Reference<DataTable> Lamp::getSampleData() {
			if (samplesize == 0) { //Samplesize cannot be 0, sqrt(length) is an acceptable value
				samplesize = (int)std::sqrt(this->length);
			}

			this->sampler->setInput(_input); //Set the input
			this->sampler->setSampleSize(samplesize);
			this->sampler->sample();

			return this->sampler->getOutput();
		}

		void Lamp::projectSample() {
			//Now we project the sample with IDMAP
			Reference<IDMAP> idmap = new IDMAP(sampledata, dimension);
			idmap->setInput(sampledata);
			idmap->setFractionDelta(fracdelta);
			idmap->setInitialization(IDMAP::InitializationType.FASTMAP);
			idmap->setNumberIterations(nriteractions);
			idmap->project();
			sampleproj = idmap->output();
		}

		void Lamp::project() {
			if (_input == nullptr) //Check if we have input set
				throw std::runtime_error("Input not set");

			if (sampledata == nullptr) //Check if we have already sampled the data, if not sample it
				sampledata = getSampleData();

			if (sampleproj == nullptr)
				this->projectSample();
		}
	}
}
