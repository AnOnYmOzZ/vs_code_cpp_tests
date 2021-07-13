//
// Created by jcliff on 7/5/2021.
//

#include <cstring>
#include "bcd_conv.h"
#include "ep_types.h" 
#include "math.h"

/*	*************************************************************
 * 	BCD2DECIMAL Function overload:
 *1. Takes in a vector containing BCD and convert to int
 *2. Takes in the same data but as array with included size
 *3. Serves the variables with decimal points
 *  **************************************************************/

unsigned long bcd_to_int(u8* array, u32 size){
    unsigned long result = 0;
    for (int i = ((size*2)-1); i > -1; i-=2){
        unsigned long a = (long unsigned)pow(10,i-1);
        unsigned long b = (long unsigned)pow(10,i);
        result += (((*array & 0xf0) >> 4) * b);
        result += ((*array & 0x0f) * a);
        //		TRACE_BP("debug naani: in result: %lu [%d] array: %x a: %lu, b: %lu   cal: %lu", result, result, *array, a, b, (((*array & 0xf0) >> 4) * b));
        array++;
    }
    return result;
}

double bcd_to_float(unsigned char* array, u32 size, u32 dp){
    unsigned long int_result = bcd_to_int(array, size);

    return (dp!= 0)? d2f(int_result, dp): int_result;
}

/*********************************************************
 *	BCD converts from binary coded decimal to decimal
 * in -> value in decimal to convert to array, MSB = index 0
 * in2 -> total size of final bcd
 * out <- pointer to array of converted int
 * return <- no. of bytes converted
 *********************************************************/

int bcd_from_int (int Decimal, unsigned char* res2, int size)
{
    memset(res2,0,size);
    unsigned char res1[30] ={0};
    unsigned int count = 0;

    while (Decimal!=0 && (count < sizeof(res1)) ){
        res1[count] = ((((Decimal/10)%10) << 4) | (Decimal % 10));
        Decimal/=100;
        count++;
    }

    for (uint32_t i=0; i<count; i++){
        res2[size-1] = res1[i];
        if (--size <= 0) ;//break;
    }
    return count;
}

int bcd_from_float (double flt, int dpoint, unsigned char* res2, int size)
{
    int dec = flt * (pow(10,dpoint));
    return bcd_from_int(dec, res2, size);
}

int bcd_from_numstring(char* numstr, int len, unsigned char* res2, int ressize)
{
    int numint = strtoll(numstr, NULL, 10);

    return bcd_from_int (numint, res2, ressize);

}

/* This converts from decimal to float as required by the pump */
double d2f(long unsigned dec, int dp){
    return (dec / pow(10,dp) );
}
