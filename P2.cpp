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
//    auto projection = ProjectionFilter::New();
//    auto writer = DataTableWriter::New();

	reader->setFilename((char*)"/Users/picolo/CPP/P2/caltech.data-NORM.data.txt");
	reader->update();
//    projection->setInputConnection(reader->outputPort());
//    writer->setFilename(...);
//    writer->setInputConnection(projection->outputPort());
//    writer->write();

//    auto pointToPolyFilter = DataTableToPolyData::New();
//    auto polyMapper = GLPolyDataMapper::New();
//
//    pointToPolyFilter->setInputConnection(projection->outputPort());
//    polyMapper->setInputConnection(pointToPolyFilter->outputPort());
//    scene()->addActor(new Actor{polyMapper});
  }
  catch (const std::exception& e)
  {
    std::cout << "Error: " << e.what() << '\n';
  }
}
