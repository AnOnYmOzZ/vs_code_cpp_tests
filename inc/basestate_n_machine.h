/** 
 * @file 	sdp_efueling_c_lib_main.h
 * 
 * @brief 	A description of the above named module in "cpp-test-programs".
 *
 * @details
 * @date 	Jul 6, 2021
 * @author 	jcliff
 *
 * @par       
 *
 * 			COPYRIGHT NOTICE: (c) 2020 fuelmetrics.  All rights reserved.
 */ 

#ifndef SDP_EFUELING_C_LIB_H_
#define SDP_EFUELING_C_LIB_H_

#define printf printf

#include "Domain_c.h"

/**
 * There are two approaches to implement the events handler for each of the states 
 * 1. Define the events handler in the BaseState class 
 * 2. use a switch case in the state.activity function 
 * 
*/


class Machine;
/**
 * ------------------------
 * States and events
 * ------------------------
 */

/* User code 1: */

typedef enum {
    EP_FSM_EVT_UNDEF,
    EP_FSM_EVT_INIT,
    EP_FSM_EVT_START_TR,
    EP_FSM_EVT_CONFIRM_START_TR,
    EP_FSM_EVT_FUELING_STARTED,
    EP_FSM_EVT_END_TR,      //from user 
    EP_FSM_EVT_COMPLETE_TR, //from GO
    EP_FSM_EVT_CLEAR_TR,    //After a completed transaction restart
    
    EP_FSM_EVT_TIMEOUT,
    EP_FSM_EVT_CLEAR_ERROR,

}ep_intn_evt_en;

typedef union{
    double vol;
    double amo;
    // ep_trans_start_data trans_data;
}ep_intn_evt_un;

typedef struct{
    ep_intn_evt_en e;
    ep_intn_evt_un data1;
}Events_st;

typedef enum {
    EP_FSM_UNDEF = 0,
    EP_FSM_IDLE,
    EP_FSM_STARTED,
    EP_FSM_NEW_SESSION,
    EP_FSM_PROCESSED,
    EP_FSM_ENDED
}ep_intn_state_en;

/** User code 1 ends */


/** Base State class */
class BaseState: public DomainClass{

public:
    Machine* machine;       /**< "context" in state pattern terminology */
    Events_st entry_event;  /**< Event and event data that led to this state */
    void setButton(Machine* btn);

    virtual void on_event( Events_st* evt );

    virtual void entry( BaseState *from);
    virtual void activity( Events_st* evt = NULL);
    virtual void exit(BaseState* to);

    BaseState();
    virtual ~BaseState();

    /** on events whose response is the same for multiple states */
    virtual void on_evt_timeout(Events_st* evt );

    /** states pointers */
    static BaseState* st_undef;
    static BaseState* st_idle;
    static BaseState* st_starting ;
    static BaseState* st_new_session;
    static BaseState* st_tr_filling;
    static BaseState* st_trans_completed;
    static BaseState* st_trans_ending;
    static BaseState* st_error;

};


/**
 * @class: Idle, busy, off :    derived class of DeviceStateClass,
 *                              They have virtual function that carry out specific tasks
 * 
 * 
 */
/* User code 2: */
class St_undef: public BaseState{
public:
    St_undef(){
        setObjName(__FUNCTION__); 
    }
    void activity(Events_st* evt);

};

class St_idle: public BaseState
{
public:
    St_idle(){setObjName(__FUNCTION__);}
    void activity(Events_st* evt);
};

class St_starting: public BaseState
{
public:
    St_starting(){setObjName(__FUNCTION__);}
    void activity( Events_st* evt);
};

class St_new_session: public BaseState
{
public:
    St_new_session(){setObjName(__FUNCTION__);}
    void activity( Events_st* evt);
};

class St_trans_filling: public BaseState
{
public:
    St_trans_filling(){setObjName(__FUNCTION__);}
    void activity( Events_st* evt = NULL);
};

class St_trans_completed: public BaseState
{
public:
    St_trans_completed(){setObjName(__FUNCTION__);}
    void activity( Events_st* evt = NULL);
};

class St_trans_ending: public BaseState
{
public:
    St_trans_ending(){setObjName(__FUNCTION__);}
    void activity( Events_st* evt = NULL);
};

class St_error: public BaseState
{
public:
    St_error(){setObjName(__FUNCTION__);}
    void entry( BaseState *from);
    void activity( Events_st* evt = NULL);

    void on_evt_timeout(Events_st* evt );
};




/** User code 2 ends */

/**
 * ------------------------
 * Context: States manager
 * ------------------------
 */

/**
 * @class: Device
 *      The object that owns that states, more like the state machine itself
 *      In "State Design Pattern" this is the "context"
 *
 *      There are two ways to implementing the state design pattern..
 *      1. have the set state
 *
 */

class Machine: public DomainClass{
//  friend class states;

public:
    Machine(const char* objName, BaseState* d_state_);
    Machine();
    ~Machine();

    /**/
    BaseState* current_state;
    void init(const char* objName, BaseState* d_state_);
    void state_transition(BaseState* to, Events_st* evt = NULL);
    int operate();

};


#endif /* SDP_EFUELING_C_LIB_H_ */
/***** END OF FILE ******/
