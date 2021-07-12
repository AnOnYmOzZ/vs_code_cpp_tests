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

#include "ep_main.h"
#include "stringToHex.h"


#define DELIM_PRE_1 (char)0xab
#define DELIM_PRE_2 (char)0xcd

void clrscr(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

int main(){
    
    uint8_t hex[]= {0xab, 0xcd, 0x02, 0x07, 0x07, 0x03, 0x04, 0x00};

    uint8_t strOut[300]={0};
    uint8_t hexOut[30]={0};

    hexToString(hex, sizeof(hex), strOut, sizeof(strOut));
    int ret = hexFromString(strOut, strlen((const char*)strOut), hexOut, sizeof(hexOut));
    

    char* data = (char*)hexOut;
    int i;
    for (i=0; i< ret-1; i++){ //it is len-1 because there are two characters to search for
        if ( (data[i] == DELIM_PRE_1) && (data[i+1] == DELIM_PRE_2) ) break;
    }

    printf("i: %d, ret: %d\n", i, ret);
    // if (i >= len-1) return -2; 

    system("pause");
    return 0;
}


