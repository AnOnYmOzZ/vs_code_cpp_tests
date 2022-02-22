/**
 * main-state-machine-cpp
 *
*  Created on: Nov 10, 2020
 *      Author: J.cliff
 *
 *      Desc: This was written in Cpp but used no std cpp lib
 *
 *      It is an adaption of the state_design_pattern code written for remis switch
 *      program now written to be more event driven
 *
 *
 */

#include "bcd_conv.h"
#include "ctype.h"
#include "string.h"
#include "stddef.h"
#include "stdio.h"
#include "math.h"

#define NUM_OF_LINES 60
#define line_60_mult 6;

int originX = 48;
int originY = 48;

int getXY(int radius, int degree, int8_t* x, int8_t* y)
{
    float radian = degree * 0.0174532925;
    *x = originX + ( radius *  cos(radian) );
    *y = originY + ( radius *  sin(radian) );

    printf("x: %d, y: %d, cos: %f, sin: %f\n", *x, *y,   cos(radian),   sin(radian));
    return 0;
}

int main(){
    char a[3] = {0};
    int i = 49384789;

<<<<<<< Updated upstream
    bcd_from_int (i, (uint8_t*)a, sizeof(a));
    printf("A: %x %x %x", a[0], a[1], a[2]);
=======
    // bcd_from_int (i, a, sizeof(a));
    printf("Hello \n");

    int line_angles[NUM_OF_LINES] = {0};
    int8_t x  = 0;
    int8_t y = 0;
    for (i = 0; i < NUM_OF_LINES; i++)
    {
        line_angles[i] = i * line_60_mult;
        printf("%d: ", line_angles[i]);
        getXY(30, line_angles[i], &x, &y);
    }

>>>>>>> Stashed changes

    // system("pause"); 

    return 0;
}


