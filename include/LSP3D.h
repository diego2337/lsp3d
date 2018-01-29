#ifndef _LSP3D_H_
#define _LSP3D_H_

#include <cstdlib>
#include "DataFrame.h"

class LSP3D
{
  public:
    LSP3D();
    ~LSP3D();
    DataFrame *execute(DataFrame *df);
  private:
};

#endif
