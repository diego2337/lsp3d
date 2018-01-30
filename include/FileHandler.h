#ifndef _FILEHANDLER_H_
#define _FILEHANDLER_H_
  #include <cstdio>
  #include <cstdlib>
  #include <cstring>
  #include <string>
  #include "DataFrame.h"

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
     int getNumRows();
     DataFrame *read_file(char *);
     std::string get_file_type() const;
  private:
    /**
     * @brief Private members and method signatures.
     */
    char delimiter;
     
    void read_csv_header(std::ifstream &file, DataFrame *df);
    void read_prj_header(std::ifstream &file, DataFrame *df);
    void read_data(std::ifstream &file, DataFrame *df);    
  };
#endif
