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

/**
 * @public Normalize values between [0,1].
 * @param {double} minNumber Minimum number from dataset.
 * @param {double} maxNumber Maximum number from dataset.
 * @param {double} value Value to be normalized.
 * @returns {double} normalized value.
 */
double normalizeValue(double minNumber, double maxNumber, double value);
#endif
