#ifndef _FILEHANDLER_H_
#include "../include/FileHandler.h"
#include "../include/DataFrame.h"
#include "../include/utils.h"
#endif

/**
 * @constructor Constructor for FileHandler.
 */
FileHandler::FileHandler()
{
}

/**
 * @constructor Constructor for FileHandler.
 * @param file ".prj" file name to be read.
 */
FileHandler::FileHandler(char *file)
{
  int i, j;
  FILE *f = fopen(file, "r");
  if(f)
  {
    /**
     * @brief Read contents of file and store them in FileHandler object
     */
    /** Read matrix type */
    this->matrixType = read(f, '\n');
    /** Read number of rows */
    char *str = read(f, '\n');
    this->numRows = toInt(str);
    this->rows = (row*)calloc(this->numRows, sizeof(row));
    free_string(&str);
    /** Read number of columns */
    str = read(f, '\n');
    for(i = 0; i < this->numRows; i++)
    {
      this->numCols = toInt(str);
      this->rows[i].values = (double*)calloc(this->numCols, sizeof(double));
      // this->rows[i].values = new double[this->rows[i].numCols];
    }
    free_string(&str);
    /** Next line contains column descriptors - skip */
    str = read(f, '\n');
    free_string(&str);
    /** Read contents */
    for(i = 0; i < this->numRows; i++)
    {
      this->rows[i].rowName = read(f, ';');
      for(j = 0; j < this->numCols; j++)
      {
//         (j+1) == this->numCols ? str = read(f, '\n') : str = read(f, ';');
        str = read(f, ';');        
        this->rows[i].values[j] = toDouble(str);
        free_string(&str);
      }
      
      str = read(f, '\n');
      this->rows[i].label = toDouble(str);
      free_string(&str);
    }
  }
  fclose(f);
}

/**
 * @destructor Destructor for FileHandler.
 */
FileHandler::~FileHandler()
{
  int i;
  if(this->matrixType) free(this->matrixType);
  for(i = 0; i < this->numRows; i++)
  {
    free(this->rows[i].rowName);
    free(this->rows[i].values);
  }
  free(this->rows);
}

/**
 * @public Read from a file until a given character occur.
 * @param file file to be read, must be opened by 'fopen' function
 * @param delimiter character that delimits reading
 * @returns all that was read until delimiter
 */
char *FileHandler::read(FILE *file, char delimiter)
{
	int count;
    char c;
    count = 0;
    char *line = NULL;
    do{
        c = fgetc(file);
        line = (char*)realloc(line, sizeof(char)*(count+1));
        line[count++] = c;
    }while(c != delimiter && c != '\r' && !feof(file));
    line[count-1] = '\0';
    return line;
}

std::string FileHandler::get_file_type() const
{
  return this->file_type;
}

DataFrame *FileHandler::read_file(char *file_path)
{
  return NULL;
}
