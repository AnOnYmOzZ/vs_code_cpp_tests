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

#include "..\inc\basestate_n_machine.h"
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
    Machine *mach = new Machine();
    int input;
    do{
        printf( "\n Enter mode and btn (separated by space): ");
        scanf("%d", &input);

        Events_st evt = { (ep_intn_evt_en)input, 0};
        mach->current_state->on_event( &evt );
    }
    while( input != 99);

    system("pause"); 

    return 0;
}


