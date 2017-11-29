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
static u32 UserApp3_au32KeyCode[10] = {BUTTON0, BUTTON1, BUTTON2};
//static u32 UserApp3_u32CodeIndex = (u32)0;
static u32 UserApp3_u32KeyCodeIndex = (u32)0;
static u32 UserApp3_u32KeyCodeLength = (u32)3;

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
/*
static void UserApp3InitializeStates()
{
  State
}
*/
/*---------------------------------------------------------------------------------------------------------------------
Function LockedState



*/
void LockedState(StateType* pstCurrent)
{
  pstCurrent -> u32CurrentState = INCORRECT;
  pstCurrent -> u32NextState = GET_CODE;
  pstCurrent -> bLocked = 1;
  pstCurrent -> bRedBlink = 1;
  pstCurrent -> bGreenBlink = 0;
  pstCurrent -> bRedOn = 0;
  pstCurrent -> bGreenOn = 0;
  
}

/*---------------------------------------------------------------------------------------------------------------------
Function UnlockedState



*/
void UnlockedState(StateType* pstCurrent)
{
  pstCurrent -> u32CurrentState = CORRECT;
  pstCurrent -> u32NextState = GET_CODE;
  pstCurrent -> bLocked = 0;
  pstCurrent -> bRedBlink = 0;
  pstCurrent -> bGreenBlink = 1;
  pstCurrent -> bRedOn = 0;
  pstCurrent -> bGreenOn = 0;
  
}

/*---------------------------------------------------------------------------------------------------------------------
Function NextState



*/

void NextState(StateType* pstCurrent)
{
  //if(pstCurrent -> u32CurrentState != pstCurrent -> u32NextState)
  //{
  switch(pstCurrent -> u32NextState){
    case GET_CODE:
      EnterCodeState(pstCurrent);
      break;
      
    case CORRECT:
      UnlockedState(pstCurrent);
      break;
      
    case INCORRECT:
      LockedState(pstCurrent);
      break;
      
    case NEW_KEY:
      NewKeyState(pstCurrent);
      break;
       
    case START:
      StartState(pstCurrent);
      break;
  }
  
  Lights(pstCurrent);
      
      
}

/*---------------------------------------------------------------------------------------------------------------------
Function RedLigt

Turns red light on/off/blink

*/

void RedLight(StateType* pstCurrent)
{
  if(pstCurrent -> bRedOn)
    LedOn(RED);
  else if(pstCurrent -> bRedBlink)
    LedBlink(RED, LED_4HZ);
  else
    LedOff(RED);
}

/*---------------------------------------------------------------------------------------------------------------------
Function GreenLight

Turns green light on/off/blink

*/

void GreenLight(StateType* pstCurrent)
{
  if(pstCurrent -> bGreenOn)
    LedOn(GREEN);
  else if(pstCurrent -> bGreenBlink)
    LedBlink(GREEN, LED_4HZ);
  else
    LedOff(GREEN);
}

/*---------------------------------------------------------------------------------------------------------------------
Function LightS

Turns lights on/off/blink

*/
void Lights(StateType* pstCurrent)
{
  GreenLight(pstCurrent);
  RedLight(pstCurrent);
}

/*---------------------------------------------------------------------------------------------------------------------
Function NewCodeState



*/
void NewKeyState(StateType* pstCurrent)
{
  pstCurrent -> u32CurrentState = NEW_KEY;
  pstCurrent -> u32NextState = GET_CODE;
  pstCurrent -> bLocked = 0;
  pstCurrent -> bRedBlink = 0;
  pstCurrent -> bGreenBlink = 0;
  pstCurrent -> bRedOn = 1;
  pstCurrent -> bGreenOn = 1;
  
}

/*---------------------------------------------------------------------------------------------------------------------
Function EnterCodeState



*/
void EnterCodeState(StateType* pstCurrent)
{
  pstCurrent -> u32CurrentState = GET_CODE;
  pstCurrent -> bLocked = 1;
  pstCurrent -> bRedBlink = 0;
  pstCurrent -> bGreenBlink = 0;
  pstCurrent -> bRedOn = 1;
  pstCurrent -> bGreenOn = 0;
  
  //Lights(pstCurrent);
  
  //static u8 u8CodeIndex = 0;
  GetCode(pstCurrent);
  
  if(WasButtonPressed(BUTTON3))
  {
    if(Compare(pstCurrent))
      pstCurrent -> u32NextState = CORRECT;
    
    else
    {
      ClearCodeEntered(pstCurrent);
      pstCurrent -> u32NextState = INCORRECT;
    }
  }
}

/*---------------------------------------------------------------------------------------------------------------------
Function StartState



*/
void StartState(StateType* pstCurrent)
{
  pstCurrent -> u32CurrentState = START;
  pstCurrent -> bLocked = 0;
  pstCurrent -> bRedBlink = 0;
  pstCurrent -> bGreenBlink = 0;
  pstCurrent -> bRedOn = 1;
  pstCurrent -> bGreenOn = 1;
  
  Lights(pstCurrent);
}

/*---------------------------------------------------------------------------------------------------------------------
Function ClearCodeEntered



*/

void ClearCodeEntered(StateType* pstCurrent)
{
  for(u32 i = 0; i < MAX_CODE_LENGTH; i++)
    pstCurrent -> au32CodeEntered[i] = 5;
  pstCurrent -> u32CodeIndex = 0;
}

/*---------------------------------------------------------------------------------------------------------------------
Function GetCode



*/

void GetCode(StateType* pstCurrent)
{
  //pstCurrent -> u8CodeIndex = 0;
  //while(!WasButtonPressed(BUTTON3) && u8CodeIndex < MAX_CODE_LENGTH)
  //{
    if(pstCurrent -> u32CodeIndex < MAX_CODE_LENGTH)
    {
      if(WasButtonPressed(BUTTON0))
      {
        ButtonAcknowledge(BUTTON0);
        pstCurrent -> au32CodeEntered[pstCurrent -> u32CodeIndex++] = BUTTON0;
        //pstCurrent -> u32CodeIndex++;
      }
    
      else if(WasButtonPressed(BUTTON1))
      {
        ButtonAcknowledge(BUTTON1);
        pstCurrent -> au32CodeEntered[pstCurrent -> u32CodeIndex++] = BUTTON1;
        //pstCurrent -> u32CodeIndex++;
      }
    
      else if(WasButtonPressed(BUTTON2))
      {
        ButtonAcknowledge(BUTTON2);
        pstCurrent -> au32CodeEntered[pstCurrent -> u32CodeIndex++] = BUTTON2;
        //pstCurrent -> u32CodeIndex++;
      }
    }
  //}
  //ButtonAcknowledge(BUTTON3);
}


/*---------------------------------------------------------------------------------------------------------------------
Function GetNewCode



*/

static void GetNewKeyCode(void)
{
  //static u8 u8KeyCodeIndex = 0;
  if(UserApp3_u32KeyCodeIndex < MAX_CODE_LENGTH)
  {
    if(WasButtonPressed(BUTTON0))
    {
      ButtonAcknowledge(BUTTON0);
      UserApp3_au32KeyCode[UserApp3_u32KeyCodeIndex++] = BUTTON0;
    }
    
    else if(WasButtonPressed(BUTTON1))
    {
      ButtonAcknowledge(BUTTON1);
      UserApp3_au32KeyCode[UserApp3_u32KeyCodeIndex++] = BUTTON1;
    }
    
    else if(WasButtonPressed(BUTTON2))
    {
      ButtonAcknowledge(BUTTON2);
      UserApp3_au32KeyCode[UserApp3_u32KeyCodeIndex++] = BUTTON2;
    }
  }
  
  
}

/*---------------------------------------------------------------------------------------------------------------------
Function Compare



*/
bool Compare(StateType* pstCurrent)
{
  if(UserApp3_u32KeyCodeLength != pstCurrent -> u32CodeIndex)
    return 0;
  
  for(u32 i = 0; i < UserApp3_u32KeyCodeLength; i++)
  {
    if(pstCurrent -> au32CodeEntered[i] != UserApp3_au32KeyCode[i])
      return 0;
  }
}

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp3SM_Idle(void)
{
    static StateType stCurrent = {.u32NextState = GET_CODE};
    StateType* pstCurrent = &stCurrent;
    LedBlink(RED, LED_8HZ);
    //NextState(pstCurrent);
    
    //EnterCodeState(pstCurrent);
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
