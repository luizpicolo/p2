#ifndef __P2_h
#define __P2_h

#include "GLRenderWindow.h"
#include "graphics/Application.h"

using namespace cg;

class P2 final: public GLRenderWindow
{
public:
  P2(int width, int height):
    GLRenderWindow{"vis2018 - P2", width, height}
  {
    // do nothing
  }

private:
  /// Initialize the app.
  void initialize() override;

}; // P2

#endif // __P2_h
