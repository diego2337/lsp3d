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

}

/**
 * @destructor Destructor for FileHandler.
 */
FileHandler::~FileHandler()
{

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
    else
      throw("Incorrect file type.");


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
        // df->set_config_numRows(toInt((char*) line.c_str()));
        df->set_config_numRows(atoi((char*) line.c_str()));
        break;
      }
      case 2:
      {
        // df->set_config_numCols(toInt((char*) line.c_str()));
        df->set_config_numCols(atoi((char*) line.c_str()));
        break;
      }
      default: break;
    }

//     std::cout<<line<<"\n";
    count++;
  }
}

//TODO: Muito espec�fico para o .prj. Encontrar maneira para
//ficar mais gen�rico para ler os dados de um .csv que pode ter qualquer
//tipo de dado em qualquer posi��o da linha.
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
        // r.label = toDouble((char*) line.c_str());
        r.label = atof((char*) line.c_str());
        line    = "";
      }
      else if(count == 0)
      {
         r.name = line.substr(0, index);
         line   = line.substr(index + 1);
      }
      else
      {
         r.values.push_back(atof((char*) line.substr(0, index).c_str()));
         line   = line.substr(index + 1);
      }

      count++;
    }

    if(row_inserted)
      df->insert_row(r);
  }
}
