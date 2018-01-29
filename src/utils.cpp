#include "../include/utils.h"

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
