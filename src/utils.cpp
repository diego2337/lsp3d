#include "../include/utils.h"

/**
 * @public Dynamically deallocates a string and set it to NULL.
 * @param str String to be deallocated.
 */
void free_string(char **str)
{
  free(*str);
  *str = NULL;
}

/**
 * @public Converts a null terminating string to integer
 * @param number char type number to be converted
 * @returns int type number
 */
int toInt(char *number)
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
double toDouble(char *number)
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

/**
 * @public Return a color vector given a number.
 * @param number Number for color mapping.
 * @returns Vector of length 3 containing specific color for that number.
 */
double *mapToColor(double number)
{
  /** Make a switch statement for 10 cases */
  int n = (int)number;
  double *color = new double[3];
  switch(n)
  {
    case 1:
      color[0] = 0.89;
      color[1] = 0.29;
      color[2] = 0.2;
      return color;
    break;
    case 2:
      color[0] = 0.19;
      color[1] = 0.63;
      color[2] = 0.32;
      return color;
    break;
    case 3:
      color[0] = 0.16;
      color[1] = 0.54;
      color[2] = 0.74;
      return color;
    break;
    case 4:
      color[0] = 0.86;
      color[1] = 0.10;
      color[2] = 0.46;
      return color;
    break;
    case 5:
      color[0] = 0.99;
      color[1] = 0.69;
      color[2] = 0.29;
      return color;
    break;
    case 6:
      color[0] = 0.45;
      color[1] = 0.41;
      color[2] = 0.69;
      return color;
    break;
    case 7:
      color[0] = 0.10;
      color[1] = 0.56;
      color[2] = 0.6;
      return color;
    break;
    case 8:
      color[0] = 0.74;
      color[1] = 0.74;
      color[2] = 0.74;
      return color;
    break;
    case 9:
      color[0] = 0.19;
      color[1] = 0.50;
      color[2] = 0.74;
      return color;
    break;
    case 10:
      color[0] = 1.0;
      color[1] = 0.92;
      color[2] = 0.62;
      return color;
    break;
    default:
      color[0] = 0.0;
      color[1] = 0.0;
      color[2] = 0.0;
      return color;
    break;
  }
}
