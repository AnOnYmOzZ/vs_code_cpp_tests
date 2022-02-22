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

int main(){
    char a[3] = {0};
    int i = 49384789;

    bcd_from_int (i, (uint8_t*)a, sizeof(a));
    printf("A: %x %x %x", a[0], a[1], a[2]);

    // system("pause"); 

    return 0;
}


