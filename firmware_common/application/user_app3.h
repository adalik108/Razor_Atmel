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
typedef struct StateType
{
  u32 u32CurrentState;
  u32 u32NextState;
  u32 u32CodeIndex;
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
#define MAX_CODE_LENGTH (u32)10
#define START           (u32)0  
#define GET_CODE        (u32)1
#define CORRECT         (u32)2
#define INCORRECT       (u32)3
#define NEW_KEY         (u32)4
//#define CURRENT         (u32)8
#define WAIT            (u32)3000
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
void GetNewKeyCode(void);
void RedLight(StateType* pstate_);
void GreenLight(StateType* pstate_);
void Lights(StateType* pstate_);
void EnterCodeState(StateType* pstate_);
void LockedState(StateType* pstate_);
void UnlockedState(StateType* pstate_);
void NewKeyState(StateType* pstate_);
bool Compare(StateType* pstate_);
void StartState(StateType* pstate_);
void NextState(StateType* pstate_);
bool Wait(void);
void Run(StateType* pstate_);


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
