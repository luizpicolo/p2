#include "GLPolyDataMapper.h"
#include "DataTableReader.h"
#include "DataTableToPolyDataFilter.h"
#include "DataTableWriter.h"
#include "Lamp.h"
#include "ProjectionFilter.h"
#include "P2.h"

void
P2::initialize()
{
  using namespace cg::vis;

  try
  {
    GLRenderWindow::initialize();

    auto reader = DataTableReader::New();
    auto projectionFilter = ProjectionFilter::New();
    projectionFilter->setProjection(Lamp::New(2));
    auto writer = DataTableWriter::New();

	reader->setFilename((char*)"/Users/picolo/CPP/p2_git/input/caltech.data-NORM.data.txt");
    reader->update();
    
    projectionFilter->setInputConnection(reader->outputPort());
    
    writer->setFilename((char*)"/Users/picolo/CPP/p2_git/output/caltech.data-NORM.data.txt");
    writer->setInputConnection(projectionFilter->outputPort());
	// writer->setInputConnection(reader->outputPort());
	writer->write();

    auto DataTableToPolyDataFilter = DataTableToPolyDataFilter::New();
    auto polyMapper = GLPolyDataMapper::New();

    DataTableToPolyDataFilter->setInputConnection(projectionFilter->outputPort());
    polyMapper->setInputConnection(DataTableToPolyDataFilter->outputPort());
    scene()->addActor(new Actor{polyMapper});
  }
  catch (const std::exception& e)
  {
    std::cout << "Error: " << e.what() << '\n';
  }
}
