#include "../include/GLHandler.h"
#include "../include/DataFrame.h"

/**
 * Global variables
 */
double **m = NULL;
double maxX = 0.000000000, maxY = 0.000000000;
int mRows = 0, mCols = 0;

/**
 * @constructor Constructor for GLHandler. Initialize glut callbacks.
 * @param argc Unmodified argument counter from 'main(argc, argv)' function.
 * @param argv Unmodified argument values from 'main(argc, argv)' function.
 */
GLHandler::GLHandler(int argc, char **argv)
{
  /** @brief Initialize glut
   */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 512);
  glutCreateWindow("LSP3D");
  /** Initialize DataFrame object */
  // this->df = NULL;
}

/**
 * @destructor Destructor for GLHandler.
 */
GLHandler::~GLHandler()
{

}

/**
 * @public Plots LSP3D projection, whose data is given by DataFrame object.
 * @param df DataFrame object containing data resulting from LSP projection.
 */
void GLHandler::plot(DataFrame *df)
{
  /** Shallow copy incoming DataFrame to GLHandler atributte DataFrame */
  // this->df = df;
  this->setPoints(df);
  gluLookAt((maxX)/2.0, (maxY)/2.0, 1.0, (maxX)/2.0, (maxY)/2.0, 0.0, 0.0, 1.0, 0.0);
  glutDisplayFunc(this->displayCallback);
  // glutIdleFunc(this->displayCallback);
  // glutReshapeFunc(reshapeCallback);
  glutMouseFunc(this->mouseCallback);
  // glutMotionFunc(motionCallback);
  glutKeyboardFunc(this->keyboardCallback);
  /** Render */
  glutMainLoop();
}

/** TODO - function to delete - just for testing */
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

/**
 * @public Set points resulting from LSP projection in OpenGL scene.
 * @param df DataFrame object containing data resulting from LSP projection.
 */
void GLHandler::setPoints(DataFrame *df)
{
  int i, j;
  row r;
  /** Only set points if DataFrame object is pointing to a DataFrame object containing data points */
  if(df)
  {
    /** Assigning values to global matrix due to static callback function */
    mRows = df->get_config_numRows();
    m = new double*[mRows];
    for(i = 0; i < mRows; i++)
    {
      mCols = df->get_config_numCols();
      /** m matrix will also store labels */
      m[i] = new double[mCols-1];
      r = df->get_row(i);
      for(j = 0; j < mCols-1; j++)
      {
        ((j+1) == (mCols-1)) ? m[i][j] = r.label : m[i][j] = r.values[j];
        if(j == 0 && maxX < m[i][j]) maxX = m[i][j];
        if(j == 1 && maxY < m[i][j]) maxY = m[i][j];
      }
      // if(maxX < m[i][0]) maxX = m[i][0];
      // if(maxY < m[i][1]) maxY = m[i][1];
      // for(j = 0; j < 3; j++)
      // {
      // }
    }
  }
}

/**
 * @public Display callback function for glutDisplayFunc
 * @param df DataFrame object containing data resulting from LSP projection.
 */
void GLHandler::displayCallback()
{
  /** Define background color */
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  /** Clear buffer */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /** Set scene according to DataFrame object points */
  for(int i = 0; i < mRows; i++)
  {
    /** Set initial drawing color */
    double *vector = mapToColor(m[i][3]);
    glColor3f(vector[0], vector[1], vector[2]);
    delete [] vector;
    glBegin(GL_POLYGON);
      for(double j = 0.0; j < 2 * M_PI; j += M_PI / 32)
      {
        glVertex3f((cos(j) * 0.01) + m[i][0], (sin(j) * 0.01) + m[i][1], 0.0 + m[i][2]);
      }
    glEnd();
    // glVertex3f(m[i][0], m[i][1], m[i][2]);
  }
  // for(double i = 0.0; i < 2 * PI; i += PI / 12)
  // {
  //   glVertex3f(cos(i) * 0.5, sin(i) * 0.5, 0.0);
  // }
  glFlush();
  // glutSwapBuffers();
}

/**
 * @public Mouse callback function for glutMouseFunc
 * @param button Indicates GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON or GLUT_RIGHT_BUTTON.
 * @param state Indicates GLUT_UP or GLUT_DOWN, being either a mouse press or release, respectively.
 * @param x x coordinates when state changed.
 * @param y y coordinates when state changed.
 */
void GLHandler::mouseCallback(int button, int state, int x, int y)
{
  // glutPostRedisplay();
}

/**
 * @public Keyboard callback function for glutKeyboardFunc
 * @param key ASCII character pressed on keyboard.
 * @param x x coordinates when key was pressed.
 * @param y y coordinates when key was pressed.
 */
void GLHandler::keyboardCallback(unsigned char key, int x, int y)
{
  /**
   * @brief Handle camera panning
   */
  switch(key)
  {
    /** Pan left */
    case 'a':
      gluLookAt((maxX)/2.0 - 1.0, (maxY)/2.0, 1.0, (maxX)/2.0, (maxY)/2.0, 0.0, 0.0, 1.0, 0.0);
    break;
    /** Pan right */
    case 'd':
      gluLookAt((maxX)/2.0 + 1.0, (maxY)/2.0, 1.0, (maxX)/2.0, (maxY)/2.0, 0.0, 0.0, 1.0, 0.0);
    break;
    /** Pan up */
    case 'w':
      gluLookAt((maxX)/2.0, (maxY)/2.0 + 1.0, 1.0, (maxX)/2.0, (maxY)/2.0, 0.0, 0.0, 1.0, 0.0);
    break;
    /** Pan down */
    case 's':
      gluLookAt((maxX)/2.0, (maxY)/2.0 - 1.0, 1.0, (maxX)/2.0, (maxY)/2.0, 0.0, 0.0, 1.0, 0.0);
    break;
    default:
    break;
  }
  glutPostRedisplay();
}
