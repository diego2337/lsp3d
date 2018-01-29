#ifndef _FILEHANDLER_H_
#define _FILEHANDLER_H_
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  /**
   * @class FileHandler class, used for handling input data in ".prj" format.
   */
  class FileHandler
  {
  public:
     /**
      * @brief Public method signatures.
      */
     FileHandler();
     FileHandler(char*);
     ~FileHandler();
     char *read(FILE*, char);
     int toNum(char*);
  private:
    /**
     * @brief Private members and method signatures.
     */
     double **matrix = NULL;
     char *matrixType = NULL;
     int numRows, numCols;
  };
#endif
