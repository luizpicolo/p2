#pragma once

#include "DataTable.h"
#include "Dissimilarity.h"

namespace cg
{
	namespace vis
	{
        class Projection : public SharedObject
        {
            public:
                int getDimension();
                virtual Dissimilarity *getDissimilarity();
                virtual void setDissimilarity(Dissimilarity* dissimilarity);
                void setInput(DataTable* input);
            
                DataTable* output() const
                {
                    return _output;
                }
            
                void execute()
                {
                    //_output = new DataTable(_input);
                }
                virtual void project() = 0;
            
            protected:
                Reference<DataTable> _input;
                Reference<DataTable> _output;
                const int dimension;
                Dissimilarity dissimilarity;
                int dataDimension;
                int length;
                static Dissimilarity getDefaultDissimilarity();
        };
	}
}
