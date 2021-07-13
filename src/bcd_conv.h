//
// Created by jcliff on 7/5/2021.
//

#include "ep_main.h"
#include "ep_types.h"

#ifndef EPUMPWIFITOOL_BCD_CONV_H
#define EPUMPWIFITOOL_BCD_CONV_H

/** Takes in a BCD array and size then convert to Decimal (int) */
long unsigned bcd_to_int(unsigned char* array, u32 size);
/** includes a third variable for decimal point */
double bcd_to_float(unsigned char* array, u32 size, u32 dp);

/** Converts an integer to bcd */
int bcd_from_int (int Decimal, unsigned char* res2, int size);

/** Converts a float/double to bcd */
int bcd_from_float (double flt, int dpoint, unsigned char* res2, int size);

/** Converts a number string to bcd */
int bcd_from_numstring(char* numstr, int len, unsigned char* res2, int ressize);

double d2f(long unsigned dec, int dp);



#endif //EPUMPWIFITOOL_BCD_CONV_H
