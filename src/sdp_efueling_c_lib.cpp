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

BtnStateClass* BtnStateClass::otto = &auto_state;
BtnStateClass* BtnStateClass::manua = &manual_state;



void BtnStateClass::setButton(Button* d){
	button_ = d;
}

void BtnStateClass::entry(BtnStateClass* from)
{
	printf("state set: %s", getObjName() );
}

void BtnStateClass::exit(BtnStateClass* to)
{
}

BtnStateClass::BtnStateClass(){
    button_ = NULL;
}

BtnStateClass::~BtnStateClass(){
    ;
}


/**
 * @class: Idle, busy, off : 	derived class of DeviceStateClass,
 * 								They have virtual function that carry out specific tasks
 */

void Auto::activity(Events_st* evt){
	//you can allocate memory here "new Busy" or use a pointer to preallocated variables &busy
	if (evt->pump == MANUAL){
		button_ -> state_transition(manua);
	}
	else if (evt->btn == NOT_PRESSED){
		button_-> state_transition( manua);
	}

}

void Manual::activity( Events_st* evt ){
	if (evt->pump == AUTO){
		button_ -> state_transition(otto);
	}
	else if (evt->btn == PRESSED){
		button_-> state_transition(otto);
	}
}


/**
 * ------------------------
 * Context: States manager
 * ------------------------
 */

/* Initialize current_state to a null ptr 'current_state(nullptr)' before assigning it a default value*/
Button::Button(const char* objName, BtnStateClass* d_state_): current_state(nullptr){
    setObjName(objName);
    state_transition(d_state_);
}

Button::Button(){
    setObjName(__FUNCTION__);
    this->init();
    state_transition( BtnStateClass::manua );
}

Button::~Button(){
    ;
}

void Button::init(){
    this->current_state = BtnStateClass::manua;
}

void Button::state_transition(BtnStateClass* to){
//  if(current_state != nullptr)   //don't bother deleting memory since we are not using dynamic memory
//      delete current_state; //i.e. deallocate the memory at current_state before assiging a new one

    //You can also call the exit() function of the "from" state 
    BtnStateClass* from = this->current_state;
    this->current_state = to;
    from->exit(to);
    this->current_state->setButton(this);
    this->current_state->entry(from);
}

int Button::operate(){
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

