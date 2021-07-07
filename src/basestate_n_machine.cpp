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
#include "..\inc\basestate_n_machine.h"

/** Instantiating the states */
St_undef st_undef_i;
St_idle st_idle_i;
St_starting st_starting_i;
St_new_session st_new_session_i;
St_trans_filling st_tr_fueling_started_i;
St_trans_completed st_trans_completed_i;
St_trans_ending st_trans_ending_i;
St_error st_error_i;

BaseState* BaseState::st_undef = &st_undef_i;
BaseState* BaseState::st_idle = &st_idle_i;
BaseState* BaseState::st_starting = &st_starting_i;
BaseState* BaseState::st_new_session = &st_new_session_i;
BaseState* BaseState::st_tr_filling = &st_tr_fueling_started_i;
BaseState* BaseState::st_trans_completed = &st_trans_completed_i;
BaseState* BaseState::st_trans_ending = &st_trans_ending_i;
BaseState* BaseState::st_error = &st_error_i;





void BaseState::setButton(Machine* d){
	machine = d;
}

void BaseState::on_event( Events_st* evt )
{
    switch (evt->e){
    case EP_FSM_EVT_TIMEOUT: on_evt_timeout(evt); break;
    default: activity(evt); break;
    
    }

}

void BaseState::entry(BaseState* from)
{
	printf("state set: %s", getName() );
}

void BaseState::activity( Events_st* evt){
}

void BaseState::exit(BaseState* to)
{
}

BaseState::BaseState(){
    machine = NULL;
}

BaseState::~BaseState(){
}

void BaseState::on_evt_timeout(Events_st* evt ){
    machine -> state_transition(st_error, evt);
}


/**
 * ------------------------
 * Machine: Context / States manager
 * ------------------------
 */

/* Initialize current_state to a null ptr 'current_state(nullptr)' before assigning it a default value*/
Machine::Machine(const char* objName, BaseState* d_state_){
    this->init(objName, d_state_);
}

Machine::Machine(){
    this->init(__FUNCTION__, BaseState::st_undef);
}

Machine::~Machine(){
}

void Machine::init(const char* objName, BaseState* state_){
    setObjName(objName);
    this->current_state = state_;
    state_transition( state_ );
}

void Machine::state_transition(BaseState* to_state, Events_st* evt){
//  if(current_state != nullptr)   //don't bother deleting memory since we are not using dynamic memory
//      delete current_state; //i.e. deallocate the memory at current_state before assiging a new one

    BaseState* from_state = this->current_state;
    this->current_state = to_state;

    /** copy the data of the event that caused the state transition */
    if (evt != NULL) memcpy(&this->current_state->entry_event, evt, sizeof (Events_st));

    /** launch all the functions */
    from_state->exit(to_state);
    this->current_state->setButton(this);
    this->current_state->entry(from_state);
}

int Machine::operate(){
    return 0;
}










/**
 * @class: St_undef, St_idle : 	derived class of BaseClass,
 * 								They have virtual function that carry out specific tasks
 * 
 * This is where the most of the work has to be done 
 */

void St_undef::activity(Events_st* evt){
	//you can allocate memory here "new Busy" or use a pointer to preallocated variables &busy
    if (evt->e == EP_FSM_EVT_INIT){
		machine -> state_transition(st_idle, evt);
        return;
	}
}

void St_idle::activity( Events_st* evt ){
    if (evt->e == EP_FSM_EVT_START_TR){
        machine -> state_transition(st_starting, evt);
        return;
    }
}

void St_starting::activity( Events_st* evt ){
	if (evt->e == EP_FSM_EVT_CONFIRM_START_TR){
		machine -> state_transition(st_new_session);
	}
}

void St_new_session::activity( Events_st* evt ){
	if (evt->e == EP_FSM_EVT_FUELING_STARTED){
		machine -> state_transition(st_tr_filling);
	}
}

void St_trans_filling::activity( Events_st* evt ){
	if (evt->e == EP_FSM_EVT_END_TR){
		machine -> state_transition(st_trans_ending);
        return;
	}
    if (evt->e == EP_FSM_EVT_COMPLETE_TR){
        machine -> state_transition(st_trans_completed);
        return;
    }
}

void St_trans_ending::activity( Events_st* evt ){
	if (evt->e == EP_FSM_EVT_COMPLETE_TR){
		machine -> state_transition(st_trans_completed);
	}
}

void St_trans_completed::activity( Events_st* evt ){
	if (evt->e == EP_FSM_EVT_CLEAR_TR){
		machine -> state_transition(st_idle);
	}
}


void St_error::entry( BaseState *from){
    printf( "\n Just experienced an ERROR, from state: %s, event id: %d", from->getName(), entry_event.e);
}

void St_error::activity( Events_st* evt )
{
	if (evt->e == EP_FSM_EVT_CLEAR_ERROR){
		machine -> state_transition(st_idle);
	}
}

void St_error::on_evt_timeout(Events_st* evt ){
}
