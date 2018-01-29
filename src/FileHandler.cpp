#ifndef _FILEHANDLER_H_
#include "../include/FileHandler.h"
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
    this->numRows = this->toNum(str);
    this->rows = (row*)calloc(this->numRows, sizeof(row));
    free(str);
    str = NULL;
    /** Read number of columns */
    str = read(f, '\n');
    for(i = 0; i < this->numRows; i++)
    {
      this->rows[i].numCols = this->toNum(str);
      this->rows[i].values = (double*)calloc(this->rows[i].numCols, sizeof(double));
      // this->rows[i].values = new double[this->rows[i].numCols];
    }
    free(str);
    str = NULL;
    /** Next line contains column descriptors - skip */
    str = read(f, '\n');
    free(str);
    str = NULL;
    /** Read contents */
    for(i = 0; i < this->numRows; i++)
    {
      this->rows[i].rowName = read(f, ';');
      for(j = 0; j < this->rows[i].numCols; j++)
      {
        (j+1) == this->rows[i].numCols ? str = read(f, '\n') : str = read(f, ';');
        this->rows[i].values[j] = this->toDouble(str);
        free(str);
        str = NULL;
      }
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

/**
 * @public Converts a null terminating string to integer
 * @param number char type number to be converted
 * @returns int type number
 */
int FileHandler::toNum(char *number)
{
  unsigned int i;
	int num = 0;
	for(i = 0; i < strlen(number); i++)
	{
		num = ((num)*10) + (number[i]-48);
	}
	return num;
}

/**
 * @public Converts a null terminating string to double
 * @param number char type number to be converted
 * @returns double type number
 */
double FileHandler::toDouble(char *number)
{
    unsigned int i;
    int point = 0, exponent;
    double num = 0.00000;
    for(i = 0; i < strlen(number); i++)
    {
        if(number[i] == '.')
        {
            point = 1;
            exponent = 1;
            i = i + 1;
        }
        if(point == 0)
        {
            num = ((num)*10) + (number[i]-48);
        }
        else
        {
            num = num + ((double)(number[i]-48)/(10*exponent));
            exponent = exponent * 10;
        }
    }
    return num;
}
