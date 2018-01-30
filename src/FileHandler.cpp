#ifndef _FILEHANDLER_H_
#include "../include/FileHandler.h"
#include "../include/DataFrame.h"
#include "../include/utils.h"

#include <iostream>
#include <fstream>

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
//   int i, j;
//   FILE *f = fopen(file, "r");
//   if(f)
//   {
//     /**
//      * @brief Read contents of file and store them in FileHandler object
//      */
//     /** Read matrix type */
//     this->matrixType = read(f, '\n');
//     /** Read number of rows */
//     char *str = read(f, '\n');
//     this->numRows = toInt(str);
//     this->rows = (row*)calloc(this->numRows, sizeof(row));
//     free_string(&str);
//     /** Read number of columns */
//     str = read(f, '\n');
//     for(i = 0; i < this->numRows; i++)
//     {
//       this->numCols = toInt(str);
//       this->rows[i].values = (double*)calloc(this->numCols, sizeof(double));
//       // this->rows[i].values = new double[this->rows[i].numCols];
//     }
//     free_string(&str);
//     /** Next line contains column descriptors - skip */
//     str = read(f, '\n');
//     free_string(&str);
//     /** Read contents */
//     for(i = 0; i < this->numRows; i++)
//     {
//       this->rows[i].rowName = read(f, ';');
//       for(j = 0; j < this->numCols; j++)
//       {
// //         (j+1) == this->numCols ? str = read(f, '\n') : str = read(f, ';');
//         str = read(f, ';');        
//         this->rows[i].values[j] = toDouble(str);
//         free_string(&str);
//       }
//       
//       str = read(f, '\n');
//       this->rows[i].label = toDouble(str);
//       free_string(&str);
//     }
//   }
//   fclose(f);
}

/**
 * @destructor Destructor for FileHandler.
 */
FileHandler::~FileHandler()
{
//   int i;
//   if(this->matrixType) free(this->matrixType);
//   for(i = 0; i < this->numRows; i++)
//   {
//     free(this->rows[i].rowName);
//     free(this->rows[i].values);
//   }
//   free(this->rows);
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

DataFrame *FileHandler::read_file(char *path)
{
  std::string file_path = path, file_type = "";
  size_t index = file_path.find_last_of('.');
  DataFrame *df = NULL;
  
  if(index != std::string::npos)
  {
    std::ifstream file(path, std::ifstream::in);
    df = new DataFrame();

    file_type = file_path.substr(index + 1);
    this->delimiter = ',';
    
    if(file_type == "csv")
      this->read_csv_header(file, df);
    else if(file_type == "prj")
    {
      this->delimiter = ';';
      this->read_prj_header(file, df);
    }  
    
    this->read_data(file, df);
    file.close();
    df->validate();
  }
 
  return df;
}

void FileHandler::read_csv_header(std::ifstream &file, DataFrame *df)
{
  std::string line;
  getline(file, line);
  std::cout<<line<<"\n";
}

void FileHandler::read_prj_header(std::ifstream &file, DataFrame *df)
{
  std::string line;
  int count = 0;
  
  while(!file.eof() && count < 4)
  {
    getline(file, line);  
    
    if(line.size() > 0 && line[line.size() - 1] == '\r')
      line = line.substr(0, line.size() - 1);
    
    switch(count)
    {
      case 0: 
      {
        df->set_matrixType((char*) line.c_str());
        break;
      }  
      case 1: 
      {
        df->set_config_numRows(toInt((char*) line.c_str()));
        break;
      }
      case 2: 
      {
        df->set_config_numCols(toInt((char*) line.c_str()));    
        break;
      }  
      default: break;
    }  
    
//     std::cout<<line<<"\n";
    count++;
  }
}

//TODO: Muito específico para o .prj. Encontrar maneira para
//ficar mais genérico para ler os dados de um .csv que pode ter qualquer
//tipo de dado em qualquer posição da linha.
void FileHandler::read_data(std::ifstream &file, DataFrame *df)
{
  std::string line;
  
  while(!file.eof())
  {
    getline(file, line); 
    
    if(line.size() > 0 && line[line.size() - 1] == '\r')
      line = line.substr(0, line.size() - 1);    
    
    row r;
    int count = 0;
    bool row_inserted = false;
    
    while(line.size() > 0)
    {
      row_inserted = true;
      size_t index = line.find(this->delimiter);
     
      if(index == std::string::npos)
      {  
        r.label = toDouble((char*) line.c_str());
        line    = "";
      } 
      else if(count == 0)
      {
         r.name = line.substr(0, index);      
         line   = line.substr(index + 1);
      }
      else
      {
         r.values.push_back(toDouble((char*) line.substr(0, index).c_str()));
         line   = line.substr(index + 1);        
      }
      
      count++;
    }
    
    if(row_inserted)
      df->insert_row(r);
  }  
}
