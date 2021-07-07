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

class Button;
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
class BtnStateClass: public DomainClass{

public:
    Button* button_; /**< "context" in state pattern terminology */
    void setButton(Button* btn);

    virtual void entry( BtnStateClass *from);
    virtual void activity( Events_st* evt) = 0;
    virtual void exit(BtnStateClass* to);

    BtnStateClass();
    virtual ~BtnStateClass();

    /** states pointers */
    static BtnStateClass* otto;
    static BtnStateClass* manua;
};


/**
 * @class: Idle, busy, off :    derived class of DeviceStateClass,
 *                              They have virtual function that carry out specific tasks
 */

class Auto: public BtnStateClass{
public:
    Auto(){setObjName(__FUNCTION__);}
    void activity( Events_st* evt = NULL);
};

class Manual: public BtnStateClass
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

class Button: public DomainClass{
//  friend class states;

public:
    Button(const char* objName, BtnStateClass* d_state_);
    Button();
    ~Button();

    /**/
    BtnStateClass* current_state;
    void init();
    void state_transition(BtnStateClass* to);
    int operate();

};


#endif /* SDP_EFUELING_C_LIB_H_ */
/***** END OF FILE ******/
