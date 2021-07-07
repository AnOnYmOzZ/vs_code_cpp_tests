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


/** C Standard library */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>

/** user library */
#include "..\inc\sdp_efueling_c_lib.h"

/** Instantiating the states */
Auto auto_state;
Manual manual_state;

BaseState* BaseState::otto = &auto_state;
BaseState* BaseState::manua = &manual_state;



void BaseState::setButton(Machine* d){
	machine = d;
}

void BaseState::entry(BaseState* from)
{
	printf("state set: %s", getName() );
}

void BaseState::exit(BaseState* to)
{
}

BaseState::BaseState(){
    machine = NULL;
}

BaseState::~BaseState(){
    ;
}


/**
 * @class: Auto, Manual : 	derived class of BaseClass,
 * 								They have virtual function that carry out specific tasks
 * 
 * This is where the most of the work has to be done 
 */


void Auto::activity(Events_st* evt){
	//you can allocate memory here "new Busy" or use a pointer to preallocated variables &busy
	if (evt->pump == MANUAL){
		machine -> state_transition(manua);
	}
	else if (evt->btn == NOT_PRESSED){
		machine-> state_transition( manua);
	}

}

void Manual::activity( Events_st* evt ){
	if (evt->pump == AUTO){
		machine -> state_transition(otto);
	}
	else if (evt->btn == PRESSED){
		machine-> state_transition(otto);
	}
}


/**
 * ------------------------
 * Machine: Context / States manager
 * ------------------------
 */

/* Initialize current_state to a null ptr 'current_state(nullptr)' before assigning it a default value*/
Machine::Machine(const char* objName, BaseState* d_state_): current_state(nullptr){
    setObjName(objName);
    state_transition(d_state_);
}

Machine::Machine(){
    setObjName(__FUNCTION__);
    this->init();
    state_transition( BaseState::manua );
}

Machine::~Machine(){
    ;
}

void Machine::init(){
    this->current_state = BaseState::manua;
}

void Machine::state_transition(BaseState* to){
//  if(current_state != nullptr)   //don't bother deleting memory since we are not using dynamic memory
//      delete current_state; //i.e. deallocate the memory at current_state before assiging a new one

    BaseState* from = this->current_state;
    this->current_state = to;
    from->exit(to);
    this->current_state->setButton(this);
    this->current_state->entry(from);
}

int Machine::operate(){
    int mode = 0, btn = 0;
    char str[100] = {0};
    char ch = '\0';
    printf( "\n Enter mode and btn (separated by space): ");
    scanf("%d %d", &mode, &btn);
    printf( "\n Mode: %s, Btn: %s \n", 
            (mode)? "MANUAL":"AUTO", 
            (btn)? "NOT PRESSED": "PRESSED");

    Events_st evt = { (ButtonStateInputEnum)btn, (PumpModeInputEnum)mode };
    this->current_state->activity( &evt );
    return mode;
}

