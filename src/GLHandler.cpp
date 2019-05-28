#include "../include/GLHandler.h"
#include "../include/DataFrame.h"

/**
 * Global variables - needed because GLUT callback functions must be static, and do not accept attributes from GLHandler class
 */
double **m = NULL;
double maxX = -1000000.000, maxY = -1000000.000, maxZ = -1000000.000, minX = 1000000.000, minY = 1000000.000, minZ = 1000000.000;
int mRows = 0, mCols = 0, rotationAngle = 0, rotationAngle2 = 0;
double xPos, yPos, zPos, angle = 0.00000000;
char position = '\n';

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
  /** Set projection matrix and frustum */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // gluPerspective(50.0, 1.0, 1.0, 15.0);
  // std::cout << minX << " " << maxX << " " << minY << " " << maxY << " " << minZ << " " << maxZ << std::endl;
  // glFrustum(minX, maxX, minY, maxY, 1, 10);
  glFrustum(-1, 1, -1, 1, 1, 10);
  // glOrtho(minX, maxX, minY, maxY, 1, 5);
  glutDisplayFunc(this->displayCallback);
  // glutIdleFunc(this->displayCallback);
  // glutReshapeFunc(reshapeCallback);
  glutMouseFunc(this->mouseCallback);
  // glutMotionFunc(motionCallback);
  glutSpecialFunc(this->specialCallback);
  glutKeyboardFunc(this->keyboardCallback);
  /** Render */
  glutMainLoop();
}

/** TODO - function to delete - just for testing */
// double fRand(double fMin, double fMax)
// {
//     double f = (double)rand() / RAND_MAX;
//     return fMin + f * (fMax - fMin);
// }

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
    maxX = df->getMaxX();
    maxY = df->getMaxY();
    maxZ = df->getMaxZ();
    minX = df->getMinX();
    minY = df->getMinY();
    minZ = df->getMinZ();
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
        // if(j == 0 && maxX < m[i][j]) maxX = m[i][j];
        // if(j == 0 && minX > m[i][j]) minX = m[i][j];
        // if(j == 1 && maxY < m[i][j]) maxY = m[i][j];
        // if(j == 1 && minY > m[i][j]) minY = m[i][j];
        // if(j == 2 && maxZ < m[i][j]) maxZ = m[i][j];
        // if(j == 2 && minZ > m[i][j]) minZ = m[i][j];
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
 * @public Draw scenes axes.
 */
void GLHandler::drawAxes()
{
  /** Draw x, y and z axes */
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
  glEnd();
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
  glEnd();
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
  glEnd();
}

/**
 * @public Draw local coordinates axes, given maxX and maxY values.
 */
void GLHandler::drawLocalCoordinateAxes()
{
  /** Draw x, y and z axes */
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(0.0 + (maxX/2.0), 0.0 + (maxY/2.0), 0.0 + (maxZ/2.0));
    glVertex3f(1.0 + (maxX/2.0), 0.0 + (maxY/2.0), 0.0 + (maxZ/2.0));
  glEnd();
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(0.0 + (maxX/2.0), 0.0 + (maxY/2.0), 0.0 + (maxZ/2.0));
    glVertex3f(0.0 + (maxX/2.0), 1.0 + (maxY/2.0), 0.0 + (maxZ/2.0));
  glEnd();
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(0.0 + (maxX/2.0), 0.0 + (maxY/2.0), 0.0 + (maxZ/2.0));
    glVertex3f(0.0 + (maxX/2.0), 0.0 + (maxY/2.0), 1.0 + (maxZ/2.0));
  glEnd();
}

/**
* @public Rotate camera leftwards.
*/
void GLHandler::rotateLeft()
{
  rotationAngle = (rotationAngle - 5) % 360;
  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();
  // angle = angle - 0.1;
  // xPos = (maxX * 3 * sin(angle));
  // zPos = (maxX * 3 * cos(angle));
  // std::cout << "angle: " << angle << std::endl;
  // gluLookAt(xPos, yPos, zPos, (maxX)/2.0, (maxY)/2.0, (maxZ)/2.0, 0.0, 1.0, 0.0);
}

/**
 * @public Rotate camera rightwards.
 */
void GLHandler::rotateRight()
{
  rotationAngle = (rotationAngle + 5) % 360;
  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();
  // angle = angle + 0.1;
  // xPos = (maxX * 3 * sin(angle));
  // zPos = (maxX * 3 * cos(angle));
  // std::cout << "angle: " << angle << std::endl;
  // gluLookAt(xPos, yPos, zPos, (maxX)/2.0, (maxY)/2.0, (maxZ)/2.0, 0.0, 1.0, 0.0);
}

/**
* @public Rotate camera upwards.
*/
void GLHandler::rotateUp()
{
  rotationAngle2 = (rotationAngle2 - 5) % 360;
  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();
  // // position == 'u' ? angle = angle + 0.1 : angle = 0.0;
  // // position = 'u';
  // angle = angle + 0.1;
  // yPos = (maxY * 3 * sin(angle));
  // zPos = (maxY * 3 * cos(angle));
  // std::cout << "angle: " << angle << std::endl;
  // gluLookAt(xPos, yPos, zPos, (maxX)/2.0, (maxY)/2.0, (maxZ)/2.0, 0.0, 1.0, 0.0);
}

/**
 * @public Rotate camera downwards.
 */
void GLHandler::rotateDown()
{
  rotationAngle2 = (rotationAngle2 + 5) % 360;
  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();
  // // position == 'd' ? angle = angle + 0.1 : angle = 0.0;
  // // position = 'd';
  // angle = angle - 0.1;
  // yPos = (maxY * 3 * sin(angle));
  // zPos = (maxY * 3 * cos(angle));
  // std::cout << "angle: " << angle << std::endl;
  // gluLookAt(xPos, yPos, zPos, (maxX)/2.0, (maxY)/2.0, (maxZ)/2.0, 0.0, 1.0, 0.0);
}

/**
 * @public Reset camera to original position.
 */
void GLHandler::rotateReset()
{
  rotationAngle = 0;
  rotationAngle2 = 0;
  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();
  // xPos = (maxX)/2.0;
  // yPos = (maxY)/2.0;
  // zPos = 3.0;
  // angle = 0.0;
  // gluLookAt(xPos, yPos, zPos, (maxX)/2.0, (maxY)/2.0, (maxZ)/2.0, 0.0, 1.0, 0.0);
}

/**
 * @public Display callback function for glutDisplayFunc.
 * @param df DataFrame object containing data resulting from LSP projection.
 */
void GLHandler::displayCallback()
{
  /** Define background color */
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  /** Clear buffer */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /** Set camera */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  xPos = 0;
  yPos = 0;
  zPos = 2.1;

  // std::cout << "xPos: " << xPos << " yPos: " << yPos << " zPos: " << zPos << " maxX: " << maxX << " minX: " << minX << "maxY: " << maxY << " minY: " << minY << " minZ: " << minZ << " maxZ: " << maxZ << std::endl;
  // gluLookAt(xPos, yPos, zPos, (maxX)/2.0, (maxY)/2.0, (maxZ)/2.0, 0.0, 1.0, 0.0);
  gluLookAt(xPos, yPos, zPos, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  /** Set scene according to DataFrame object points */
  for(int i = 0; i < mRows; i++)
  {
    /** Set initial drawing color */
    double *vector = mapToColor(m[i][3]);
    // glColor3f(0.0,0.0,1.0);
    glColor3f(vector[0], vector[1], vector[2]);
    // std::cout << vector[0] << " " << vector[1] << " " << vector[2] << std::endl;
    delete [] vector;
    /** Draw spheres with glut - First, apply any translation or rotation required, then draw polygon */
    glPushMatrix();
        glRotatef((GLfloat)rotationAngle, 0.0, 1.0, 0.0);
        glRotatef((GLfloat)rotationAngle2, 1.0, 0.0, 0.0);
        // std::cout << "m[i][0]: " << normalizeValue(minX, maxX, m[i][0]) << " m[i][1]: " << normalizeValue(minY, maxY, m[i][1]) << " m[i][2]: " << normalizeValue(minZ, maxZ, m[i][2]) << std::endl;
        // glTranslatef(normalizeValue(minX, maxX, m[i][0]), normalizeValue(minY, maxY, m[i][1]), normalizeValue(minZ, maxZ, m[i][2]));
        // std::cout << "m[i][0]: " << m[i][0] << " m[i][1]: " << m[i][1] << " m[i][2]: " << m[i][2] << std::endl;
        glTranslatef(m[i][0], m[i][1], m[i][2]);
        glutSolidSphere(0.01, 32, 32);
    glPopMatrix();
    // glBegin(GL_POLYGON);
    //   for(double j = 0.0; j < 2 * M_PI; j += M_PI / 32)
    //   {
    //     glVertex3f((cos(j) * 0.01) + m[i][0], (sin(j) * 0.01) + m[i][1], 0.0 + m[i][2]);
    //   }
    // glEnd();
  }
  glPushMatrix();
    glRotatef((GLfloat)rotationAngle, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)rotationAngle2, 1.0, 0.0, 0.0);
    GLHandler::drawAxes();
    // GLHandler::drawLocalCoordinateAxes();
  glPopMatrix();
  // for(double i = 0.0; i < 2 * PI; i += PI / 12)
  // {
  //   glVertex3f(cos(i) * 0.5, sin(i) * 0.5, 0.0);
  // }
  glFlush();
  // glutSwapBuffers();
}

/**
 * @public Mouse callback function for glutMouseFunc.
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
 * @public Special callback function for glutSpecialFunc.
 * @param key special glut type character pressed on arrows.
 * @param x x coordinates when key was pressed.
 * @param y y coordinates when key was pressed.
 */
 void GLHandler::specialCallback(int key, int x, int y)
 {
   switch(key)
   {
     case GLUT_KEY_UP:
      GLHandler::rotateUp();
     break;
     case GLUT_KEY_DOWN:
      GLHandler::rotateDown();
     break;
     case GLUT_KEY_LEFT:
      GLHandler::rotateLeft();
     break;
     case GLUT_KEY_RIGHT:
      GLHandler::rotateRight();
     break;
     default:
     break;
   }
   glutPostRedisplay();
 }

/**
 * @public Keyboard callback function for glutKeyboardFunc.
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
      // glTranslatef()
      // glRotatef(30.0, (maxX)/2.0, (maxY)/2.0, 0.0);
      /** Calculate angle between vectors */
      // angle = acos( ( ((maxX/2.0) - xPos) + ((maxY/2.0) - yPos) + (-zPos) ) / sqrt((xPos * xPos) + (yPos * yPos) + (zPos * zPos)) ) * M_PI;
      // std::cout << "sin(angle*M_PI): " << sin(angle*M_PI) << " cos(angle*M_PI): " << cos(angle*M_PI) << " angle: " << angle << std::endl;
      // std::cout << "xPos: " << xPos << " yPos: " << yPos << " zPos: " << zPos << " maxX: " << maxX << " maxY: " << maxY << " angle: " << angle << std::endl;
      GLHandler::rotateLeft();
    break;
    /** Pan right */
    case 'd':
      // (xPos < 0.00000) ? xPos = xPos - ((maxX)/2.0 * sin(angle)) : xPos = xPos + ((maxX)/2.0 * sin(angle));
      // (zPos < 0.00000) ? zPos = zPos + ((maxX)/2.0 * cos(angle)) : zPos = zPos - ((maxX)/2.0 * cos(angle));
      // angle = angle + 0.7;
      // gluLookAt(xPos, yPos, zPos, (maxX)/2.0, (maxY)/2.0, 0.0, 0.0, 1.0, 0.0);
      GLHandler::rotateRight();
    break;
    /** Pan up */
    case 'w':
      // yPos = yPos + ((maxY)/2.0 * sin(angle));
      // zPos = zPos + ((maxY)/2.0 * cos(angle));
      // angle = angle + 0.7;
      // // gluLookAt((maxX)/2.0, (maxY)/2.0 + 0.1, 3.0, (maxX)/2.0, (maxY)/2.0, 0.0, 0.0, 1.0, 0.0);
      // // yPos = yPos + 0.1;
      // gluLookAt(xPos, yPos, zPos, (maxX)/2.0, (maxY)/2.0, 0.0, 0.0, 1.0, 0.0);
      GLHandler::rotateUp();
    break;
    /** Pan down */
    case 's':
      // yPos = yPos - ((maxY)/2.0 * sin(angle));
      // zPos = zPos - ((maxY)/2.0 * cos(angle));
      // angle = angle + 0.7;
      // // gluLookAt((maxX)/2.0, (maxY)/2.0 - 0.1, 3.0, (maxX)/2.0, (maxY)/2.0, 0.0, 0.0, 1.0, 0.0);
      // // yPos = yPos - 0.1;
      // gluLookAt(xPos, yPos, zPos, (maxX)/2.0, (maxY)/2.0, 0.0, 0.0, 1.0, 0.0);
      GLHandler::rotateDown();
    break;
    /** Reset camera to default position */
    case 'r':
      GLHandler::rotateReset();
    break;
    default:
    break;
  }
  glutPostRedisplay();
}
