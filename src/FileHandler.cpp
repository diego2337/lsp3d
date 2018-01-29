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
  FILE *f = fopen(file, "r");
  if(f)
  {
    /** @brief Read contents of file and store them in FileHandler object
     */
    /** Read matrix type */
    this->matrixType = read(f, '\n');
    /** Read number of rows */
    this->numRows = this->toNum(read(f, '\n'));
    /** Read number of columns */
    this->numCols = this->toNum(read(f, '\n'));
    /** Next line contains column descriptors - skip */
    char *skip = read(f, '\n');
    free(skip);
    /** Read contents */
    this->matrix = new double*[this->numRows];

  }
  fclose(f);
}

/**
 * @destructor Destructor for FileHandler.
 */
FileHandler::~FileHandler()
{
  int i;
  if(this->matrix)
  {
    for(i = 0; i < this->numRows; i++)
    {
      delete [] this->matrix[i];
    }
    delete [] this->matrix;
  }

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
