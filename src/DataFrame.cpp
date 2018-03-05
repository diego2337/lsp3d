#include "../include/DataFrame.h"

DataFrame::DataFrame()
{
  this->maxX = this->maxY = this->maxZ = -1000000.00000;
  this->minX = this->minY = this->minZ = 1000000.00000;
}

DataFrame::~DataFrame()
{

}

std::string DataFrame::get_matrixType() const
{
  return this->matrixType;
}

int DataFrame::get_numCols() const
{
  if(this->rows.size() > 0)
    return this->rows[0].values.size() + 2; //+ nome e label

  return 0;
}

int DataFrame::get_numRows() const
{
  return this->rows.size();
}

int DataFrame::get_config_numCols() const
{
  return this->config_numCols + 2;
}

int DataFrame::get_config_numRows() const
{
  return this->config_numRows;
}

void DataFrame::set_matrixType(char *v)
{
  this->matrixType = v;
}

void DataFrame::set_config_numCols(int v)
{
  this->config_numCols = v;
}

void DataFrame::set_config_numRows(int v)
{
  this->config_numRows = v;
}

double DataFrame::getMaxX() const
{
  return this->maxX;
}

double DataFrame::getMaxY() const
{
  return this->maxY;
}

double DataFrame::getMaxZ() const
{
  return this->maxZ;
}

double DataFrame::getMinX() const
{
  return this->minX;
}

double DataFrame::getMinY() const
{
  return this->minY;
}

double DataFrame::getMinZ() const
{
  return this->minZ;
}

int DataFrame::insert_row(row &r)
{
  /** Check to see maximum and minimum values */
  if(this->minX > r.values[0]) this->minX = r.values[0];
  if(this->maxX < r.values[0]) this->maxX = r.values[0];
  if(this->minY > r.values[1]) this->minY = r.values[1];
  if(this->maxY < r.values[1]) this->maxY = r.values[1];
  if(this->minZ > r.values[2]) this->minZ = r.values[2];
  if(this->maxZ < r.values[2]) this->maxZ = r.values[2];
  if( (int) r.values.size() + 2 == this->get_config_numCols())
    this->rows.push_back(r);
  else
    throw "Wrong column number.";

return this->rows.size() - 1;
}

void DataFrame::validate()
{
  if(this->get_numCols() != this->get_config_numCols())
    throw "Wrong column number.";
    // std::cout << this->get_numRows() << " " << this->get_config_numRows() << std::endl;
  if(this->get_numRows() != this->get_config_numRows())
    throw "Wrong row number.";
  /** Normalize values */
  row *r;
  for(int i = 0; i < this->get_config_numRows(); i++)
  {
    r = (row*)malloc(sizeof(row));
    r = this->getReferenceRow(i);
    for(unsigned int j = 0; j < r->values.size(); j++)
    {
      switch(j)
      {
        case 0:
          r->values[j] = normalizeValue(this->minX, this->maxX, r->values[j]);
        break;
        case 1:
          r->values[j] = normalizeValue(this->minY, this->maxY, r->values[j]);
        break;
        case 2:
          r->values[j] = normalizeValue(this->minZ, this->maxZ, r->values[j]);
        break;
        default:
        break;
      }
    }
    // free(r);
    r = NULL;
  }
}

row DataFrame::get_row(int i) const
{
  if(i < this->get_numRows())
    return this->rows[i];
  else
    throw "Wrong data index.";
}

/**
 * @public Returns reference to row.
 * @param {int} i index for row position.
 * @returns {row*} Reference to row.
 */
row *DataFrame::getReferenceRow(int i)
{
  if(i < this->get_numRows())
    return &this->rows[i];
  else
    throw "Wrong data index.";
}

void DataFrame::print_row(int i) const
{
  row r = this->get_row(i);
  std::cout<<r.name;

  for(int j = 0; j < (int) r.values.size(); j++)
    std::cout<<'\t'<<r.values[j];

  std::cout<<'\t'<<r.label<<"\n";
}
