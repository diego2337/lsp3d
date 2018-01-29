#ifndef _FILEHANDLER_H_
#define _FILEHANDLER_H_
  #include <cstdio>
  #include <cstdlib>
  #include <cstring>
  #include <string>
  #include "DataFrame.h"

  /**
   * @struct Struct containing rows names and coordinates
   */
  typedef struct _row{
    char *rowName;
    double *values;
    double label;
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
     char *getMatrixType();
     void setMatrixType(char*);
     int getNumRows();
     DataFrame *read_file(char *);
     std::string get_file_type() const;
  private:
    /**
     * @brief Private members and method signatures.
     */
     char *matrixType = NULL;
     int numCols;     
     int numRows;
     row *rows;
     std::string file_type;
  };
#endif
