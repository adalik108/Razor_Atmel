/**********************************************************************************************************************
File: user_app3.h                                                                

Description:
Header file for user_app3.c

**********************************************************************************************************************/

#ifndef __USER_APP3_H
#define __USER_APP3_H

/**********************************************************************************************************************
Type Definitions
**********************************************************************************************************************/
typedef struct
{
  u8 u8CurrentState;
  u8 u8NextState;
  //u8* pu8CodeIndex;
  //static u32 au32CurrentPassword[10] = {BUTTON0, BUTTON1, BUTTON2};
  u32 au32CodeEntered[10];
  bool bLocked;
  bool bRedOn;
  bool bRedBlink;
  bool bGreenOn;
  bool bGreenBlink;
  //StateType* pNextState;
}StateType;
  

/**********************************************************************************************************************
Constants / Definitions
**********************************************************************************************************************/
#define MAX_CODE_LENGTH (u8)10

/**********************************************************************************************************************
Function Declarations
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/
void UserApp3Initialize(void);
void UserApp3RunActiveState(void);


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/
void RunCurrent(StateType state_);
void ClearCodeEntered(StateType* pstate_);
void GetCode(StateType* pstate_);
static void GetNewKeyCode(void);
void RedLight(StateType* pstate_);
void GreenLight(StateType* pstate_);
void Lights(StateType* pstate_);
void EnterCodeState(StateType* pstate_);
void LockedState(StateType* pstate_);
StateType UnlockedState(StateType* pstate_);
StateType NewCodeState(StateType* pstate_);


/***********************************************************************************************************************
State Machine Declarations
***********************************************************************************************************************/
static void UserApp3SM_Idle(void);    

static void UserApp3SM_Error(void);         
static void UserApp3SM_FailedInit(void);        


#endif /* __USER_APP3_H */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
