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

class Machine;
/**
 * ------------------------
 * States and events
 * ------------------------
 */

typedef enum{
    PRESSED,
    NOT_PRESSED
}ButtonStateInputEnum;

typedef enum{
    AUTO,
    MANUAL
}PumpModeInputEnum;

typedef struct{
    ButtonStateInputEnum btn;
    PumpModeInputEnum pump;

}Events_st;


/** Base State class */
class BaseState: public DomainClass{

public:
    Machine* machine; /**< "context" in state pattern terminology */
    void setButton(Machine* btn);

    virtual void entry( BaseState *from);
    virtual void activity( Events_st* evt) = 0;
    virtual void exit(BaseState* to);

    BaseState();
    virtual ~BaseState();

    /** states pointers */
    static BaseState* otto;
    static BaseState* manua;
};


/**
 * @class: Idle, busy, off :    derived class of DeviceStateClass,
 *                              They have virtual function that carry out specific tasks
 */

class Auto: public BaseState{
public:
    Auto(){setObjName(__FUNCTION__);}
    void activity( Events_st* evt = NULL);
};

class Manual: public BaseState
{
public:
    Manual(){setObjName(__FUNCTION__);}
    void activity( Events_st* evt = NULL);
};



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
    void init();
    void state_transition(BaseState* to);
    int operate();

};


#endif /* SDP_EFUELING_C_LIB_H_ */
/***** END OF FILE ******/
