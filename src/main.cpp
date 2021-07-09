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



void clrscr(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

int main(){
    
    uint8_t hex[]={0x88, 0x3e,0xfa};

    uint8_t strOut[300]={0};
    uint8_t hexOut[30]={0};

    hexToString(hex, sizeof(hex), strOut, sizeof(strOut));
    hexFromString(strOut, strlen((const char*)strOut), hexOut, sizeof(hexOut));

    system("pause");
    return 0;
}


