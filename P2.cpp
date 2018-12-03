#include "GLPolyDataMapper.h"
#include "DataTableReader.h"
//#include "PointSetToPolyDataFilter.h"
//#include "PointWriter.h"
//#include "ProjectionFilter.h"
#include "P2.h"

void
P2::initialize()
{
  using namespace cg::vis;

  try
  {
    GLRenderWindow::initialize();

    auto reader = DataTableReader::New();
    // projection = ProjectionFilter::New();
    //auto writer = PointWriter::New();

    reader->setFilename((char*)"C:\\cpp\\caltech.data-NORM.data")
    //projection->setInputConnection(reader->outputPort());
    //writer->setFilename(...);
    //->setInputConnection(projection->outputPort());
    //writer->write();

    //auto pointToPolyFilter = PointSetToPolyData::New();
    //auto polyMapper = GLPolyDataMapper::New();

    //pointToPolyFilter->setInputConnection(projection->outputPort());
    //polyMapper->setInputConnection(pointToPolyFilter->outputPort());
    //scene()->addActor(new Actor{polyMapper});
  }
  catch (const std::exception& e)
  {
    std::cout << "Error: " << e.what() << '\n';
  }
}
