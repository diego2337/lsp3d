#ifndef _MAIN_H_
  #include "../include/main.h"
#endif

/**
 * Main function for LSP3D.
 */
 int main(int argc, char **argv)
 {
   /** @brief Catch arguments exceptions. TODO: Use a separate exception class
    */
   if(argc < 2)
   {
     printf("Usage: %s <input file>\n", argv[0]);
     return -1;
   }
   /** @brief Instantiate LSP, GLHandler and FileHandler, already reading input file
    */
   // GLHandler *glHandler = new GLHandler();
   // LSP3D * lsp3d = new LSP3D();
   // FileHandler *fileHandler = new FileHandler(argv[1]);

   /** @brief get fileHandler file, execute LSP and display using glHandler
    */
   // glHandler->display(TODO - LSP calculations)

   /** @brief register glut callbacks associated with glHandler
    */
   //  initGL(&argc, argv);
   //  glutDisplayFunc(displayCallback);
   //  glutReshapeFunc(reshapeCallback);
   //  glutMouseFunc(mouseCallback);
   //  glutMotionFunc(motionCallback);
   //  glutKeyboardFunc(keyboardCallback);
   //  glutMainLoop();
   return 0;

 }
