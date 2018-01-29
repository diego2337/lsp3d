#ifndef _FILEHANDLER_H_
#define _FILEHANDLER_H_
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  /**
   * @struct Struct containing rows names and coordinates
   */
  typedef struct _row{
    int numCols;
    char *rowName;
    double *values;
  }row;

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
     double toDouble(char*);
     char *getMatrixType();
     void setMatrixType(char*);
     int getNumRows();
  private:
    /**
     * @brief Private members and method signatures.
     */
     char *matrixType = NULL;
     int numRows;
     row *rows;
  };
#endif
