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

#include "..\inc\sdp_efueling_c_lib.h"
#include "ctype.h"
#include "string.h"
#include "stddef.h"
#include "stdio.h"

void clrscr(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

int main(){
    Button *d_ = new Button();
    int ret;
    do{
        ret = d_->operate();
        if (ret == 'c') clrscr();
    }
    while( ret != 9);

    system("pause"); 
    
    return 0;
}
