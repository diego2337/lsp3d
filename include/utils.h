#ifndef _UTILS_H_
#include <cstdlib>
#include <cstring>

void free_string(char **str);

/**
 * @public Converts a null terminating string to integer
 * @param number char type number to be converted
 * @returns int type number
 */
int toInt(char *number);

/**
 * @public Converts a null terminating string to double
 * @param number char type number to be converted
 * @returns double type number
 */
double toDouble(char *number);

/**
 * @public Return a color vector given a number.
 * @param number Number for color mapping.
 * @returns Vector of length 3 containing specific color for that number.
 */
double *mapToColor(double number);

#endif
