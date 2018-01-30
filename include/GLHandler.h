#ifndef _GL_HANDLER_H
#define _GL_HANDLER_H
  #include <stdio.h>
  #include <math.h>
  #include <time.h>
  #include <GL/glut.h>
  #include "DataFrame.h"
  #define PI 3.1415926535897932384626433832795

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
      static void displayCallback();
      static void mouseCallback(int,int,int,int);
      static void keyboardCallback(unsigned char,int,int);
      void setPoints();
  private:
      /**
       * @brief Private members and method signatures.
       */
      DataFrame *df;
  };
#endif
