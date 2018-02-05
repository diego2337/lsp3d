#ifndef _GL_HANDLER_H
#define _GL_HANDLER_H
  #include <iostream>
  #include <math.h>
  #include <GL/glut.h>
  #include "DataFrame.h"
  #include "utils.h"

  /**
   * @class GLHandler class, used for registering glut callbacks and plotting received data with OpenGL.
   */
  class GLHandler
  {
  public:
      /**
       * @brief Public method signatures.
       */
      GLHandler(int, char**);
      ~GLHandler();
      void plot(DataFrame *df);
      static void drawAxes();
      static void displayCallback();
      static void mouseCallback(int,int,int,int);
      static void keyboardCallback(unsigned char,int,int);
      void setPoints(DataFrame *df);
  private:
      /**
       * @brief Private members and method signatures.
       */
  };
#endif
