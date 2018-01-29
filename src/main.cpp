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
   FileHandler *fileHandler = new FileHandler();
   DataFrame *df = fileHandler->read_file(argv[1]);
   
   if(fileHandler->get_file_type() == "csv")
   {
      LSP3D *lsp3d = new LSP3D();    
      DataFrame *aux = lsp3d->execute(df);
      delete df;
      df = aux;
      aux = NULL;
   } 
   else if(fileHandler->get_file_type() != "prj")
     std::cerr<<"";

   GLHandler *glHandler = new GLHandler();
   glHandler->plot(df);
  
   delete glHandler;
   delete df;
   delete fileHandler;
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
