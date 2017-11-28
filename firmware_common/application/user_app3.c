/**********************************************************************************************************************
File: user_app3.c                                                                

Description:
This is a user_app3.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp3Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp3RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp3"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp3Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp3_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp3_StateMachine;            /* The state machine function pointer */
//static u32 UserApp3_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp3Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp3Initialize(void)
{
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp3_StateMachine = UserApp3SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp3_StateMachine = UserApp3SM_FailedInit;
  }

} /* end UserApp3Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp3RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp3RunActiveState(void)
{
  UserApp3_StateMachine();

} /* end UserApp3RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------
Function UserApp3InitializeStates


*/
static void UserApp3InitializeStates()
{
  State
}

/*---------------------------------------------------------------------------------------------------------------------
Function LockedState



*/
StateType LockedState(StateType stCurrent)
{
  stCurrent.u8NextState = 0;
  stCurrent.bLocked = 1;
  stCurrent.bRedBlink = 1;
  stCurrent.bGreenBlink = 0;
  stCurrent.bRedOn = 0;
  stCurrent.bGreenOn = 0;
  
}

/*---------------------------------------------------------------------------------------------------------------------
Function UnlockedState



*/
StateType UnlockedState(StateType stCurrent)
{
  stCurrent.u8NextState = 0;
  stCurrent.bLocked = 0;
  stCurrent.bRedBlink = 0;
  stCurrent.bGreenBlink = 1;
  stCurrent.bRedOn = 0;
  stCurrent.bGreenOn = 0;
  
}

/*---------------------------------------------------------------------------------------------------------------------
Function RunCurrent



*/

void RunCurrent(StateType stCurrent)
{
  Lights(stCurrent);
    
}

/*---------------------------------------------------------------------------------------------------------------------
Function RedLigt

Turns red light on/off/blink

*/

void RedLight(StateType stCurrent)
{
  if(stCurrent.bRedOn)
    LedOn(RED);
  else if(stCurrent.bRedBlink)
    LedBlink(RED, LED_4HZ);
  else
    LedOff(RED);
}

/*---------------------------------------------------------------------------------------------------------------------
Function GreenLight

Turns green light on/off/blink

*/

void GreenLight(StateType stCurrent)
{
  if(stCurrent.bGreenOn)
    LedOn(GREEN);
  else if(stCurrent.bGreenBlink)
    LedBlink(GREEN, LED_4HZ);
  else
    LedOff(GREEN);
}

/*---------------------------------------------------------------------------------------------------------------------
Function LightS

Turns lights on/off/blink

*/
void Lights(StateType stCurrent)
{
  GreenLight(stCurrent);
  RedLight(stCurrent);
}

/*---------------------------------------------------------------------------------------------------------------------
Function NewCodeState



*/
StateType LockedState(StateType stCurrent)
{
  stCurrent.u8NextState = 0;
  stCurrent.bLocked = 0;
  stCurrent.bRedBlink = 0;
  stCurrent.bGreenBlink = 0;
  stCurrent.bRedOn = 1;
  stCurrent.bGreenOn = 1;
  
}

/*---------------------------------------------------------------------------------------------------------------------
Function EnterCodeState



*/
static StateType EnterCodeState(StateType stCurrent)
{
  stCurrent.bLocked = 1;
  stCurrent.bRedBlink = 0;
  stCurrent.bGreenBlink = 0;
  stCurrent.bRedOn = 1;
  stCurrent.bGreenOn = 0;
  
  Lights(stCurrent);
  
  static u8 u8CodeIndex = 0;
  GetCode();
  
}

/*---------------------------------------------------------------------------------------------------------------------
Function ClearCodeEntered



*/

void ClearCodeEntered()
{
  int i = 0;
  for(i; i < MAX_CODE_LENGTH; i++)
    au8CodeEntered[i] = 5;
  u8CodeIndex = 0;
}

/*---------------------------------------------------------------------------------------------------------------------
Function GetCode



*/

void GetCode()
{
  if(u8CodeIndex < MAX_CODE_LENGTH)
  {
    if(WasButtonPressed(BUTTON0))
    {
      ButtonAcknowledge(BUTTON0);
      au8CodeEntered[u8CodeIndex++] = BUTTON0;
    }
    
    else if(WasButtonPressed(BUTTON1))
    {
      ButtonAcknowledge(BUTTON1);
      au8CodeEntered[u8CodeIndex++] = BUTTON1;
    }
    
    else if(WasButtonPressed(BUTTON2))
    {
      ButtonAcknowledge(BUTTON2);
      au8CodeEntered[u8CodeIndex++] = BUTTON2;
    }
  }
}


/*---------------------------------------------------------------------------------------------------------------------
Function GetNewCode



*/

void GetNewKeyCode()
{
  static u8 u8KeyCodeIndex = 0;
  if(u8KeyCodeIndex < MAX_CODE_LENGTH)
  {
    if(WasButtonPressed(BUTTON0))
    {
      ButtonAcknowledge(BUTTON0);
      au8KeyCode[u8KeyCodeIndex++] = BUTTON0;
    }
    
    else if(WasButtonPressed(BUTTON1))
    {
      ButtonAcknowledge(BUTTON1);
      au8KeyCode[u8KeyCodeIndex++] = BUTTON1;
    }
    
    else if(WasButtonPressed(BUTTON2))
    {
      ButtonAcknowledge(BUTTON2);
      au8KeyCode[u8KeyCodeIndex++] = BUTTON2;
    }
  }
  
  
}
/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp3SM_Idle(void)
{
    static StateType stCurrent;
    static StateType S0;
    static u8 au8KeyCode[10] = {BUTTON0, BUTTON1, BUTTON2};
    static u8 au8CodeEntered[10] = {5};
    
    EnterCodeState(stCurrent);
} /* end UserApp3SM_Idle() */
     
#if 0
/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp3SM_Error(void)          
{
  
} /* end UserApp3SM_Error() */
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserApp3SM_FailedInit(void)          
{
    
} /* end UserApp3SM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
