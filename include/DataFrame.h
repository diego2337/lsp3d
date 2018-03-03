#ifndef _DATA_FRAME_H_
#define _DATA_FRAME_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "utils.h"

  /**
   * @struct Struct containing rows names and coordinates
   */
  typedef struct _row{
    std::string name;
    std::vector<double> values;
    double label;
  }row;

class DataFrame
{
  public:
    DataFrame();
    ~DataFrame();

    int get_numCols() const;
    int get_numRows() const;

    std::string get_matrixType() const;
    int get_config_numCols() const;
    int get_config_numRows() const;

    double getMaxX() const;
    double getMaxY() const;
    double getMaxZ() const;
    double getMinX() const;
    double getMinY() const;
    double getMinZ() const;

    void set_matrixType(char *v);
    void set_config_numCols(int v);
    void set_config_numRows(int v);

    int insert_row(row &r);
    void validate() const;
    row get_row(int i) const;

    void print_row(int i) const;
  private:
    std::string matrixType;
    int config_numCols;
    int config_numRows;
    double maxX, maxY, maxZ, minX, minY, minZ;
    std::vector<row> rows;
};

#endif
