/*!*********************************************************************************************************************
@file user_app1.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1RunActiveState(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                          /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */
extern volatile u32 G_u32ApplicationFlags;                /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_<type>" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_pfStateMachine;               /*!< @brief The state machine function pointer */
//static u32 UserApp1_u32Timeout;                           /*!< @brief Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserApp1Initialize(void)

@brief
Initializes the State Machine and its variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserApp1Initialize(void)
{
  
/* All discrete LEDs to off */
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  LedOn(YELLOW);
  
  /*make a wave like feture on the board */
  
  if( 1 )
  {
    UserApp1_pfStateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_pfStateMachine = UserApp1SM_Error;
  }
} /* end UserApp1Initialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserApp1RunActiveState(void)

@brief Selects and runs one iteration of the current state in the state machine.

All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
- State machine function pointer points at current state

Promises:
- Calls the function to pointed by the state machine function pointer

*/
void UserApp1RunActiveState(void)
{
  UserApp1_pfStateMachine();

} /* end UserApp1RunActiveState */


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/
/*-------------------------------------------------------------------------------------------------------------------*/
/* What does this state do? */

//MY CODE STARTS HERE

#define ENTERPASSCODETIME 7000

static void UserApp1SM_Idle(void)
{
  static u16 u16PasscodePlace = 0;
  static bool bArrayPasscode[] = {TRUE, FALSE, FALSE, FALSE,
                                  FALSE, TRUE, FALSE, FALSE,
                                  FALSE, FALSE, TRUE, FALSE,
                                  FALSE, FALSE, FALSE, TRUE,
                                  FALSE, FALSE, FALSE, FALSE,
                                  FALSE, FALSE, FALSE, FALSE,
                                  FALSE, FALSE, FALSE, FALSE,
                                  FALSE, FALSE, FALSE, FALSE,
                                  FALSE, FALSE, FALSE, FALSE,
                                  FALSE, FALSE, FALSE, FALSE}; //can hold 10 numbers
  static bool bChanged = FALSE;
  
  //changes the passcode give the user till ENTERPASSCODETIME miliseconds
  if (G_u32SystemTime1ms < ENTERPASSCODETIME)
  {
    if (WasButtonPressed(BUTTON0))
    {
      ButtonAcknowledge(BUTTON0);
      bArrayPasscode[u16PasscodePlace * 4] = TRUE;
      bArrayPasscode[u16PasscodePlace * 4 + 1] = FALSE;
      bArrayPasscode[u16PasscodePlace * 4 + 2] = FALSE;
      bArrayPasscode[u16PasscodePlace * 4 + 3] = FALSE;u16PasscodePlace++;
      bChanged = TRUE;
    }
    if (WasButtonPressed(BUTTON1))
    {
      ButtonAcknowledge(BUTTON1);
      bArrayPasscode[u16PasscodePlace * 4] = FALSE;
      bArrayPasscode[u16PasscodePlace * 4 + 1] = TRUE;
      bArrayPasscode[u16PasscodePlace * 4 + 2] = FALSE;
      bArrayPasscode[u16PasscodePlace * 4 + 3] = FALSE;u16PasscodePlace++;
      bChanged = TRUE;
    }
    if (WasButtonPressed(BUTTON2))
    {
      ButtonAcknowledge(BUTTON2);
      bArrayPasscode[u16PasscodePlace * 4] = FALSE;
      bArrayPasscode[u16PasscodePlace * 4 + 1] = FALSE;
      bArrayPasscode[u16PasscodePlace * 4 + 2] = TRUE;
      bArrayPasscode[u16PasscodePlace * 4 + 3] = FALSE;u16PasscodePlace++;
      bChanged = TRUE;
    }
    if (WasButtonPressed(BUTTON3))
    {
      ButtonAcknowledge(BUTTON3);
      bArrayPasscode[u16PasscodePlace * 4] = FALSE;
      bArrayPasscode[u16PasscodePlace * 4 + 1] = FALSE;
      bArrayPasscode[u16PasscodePlace * 4 + 2] = FALSE;
      bArrayPasscode[u16PasscodePlace * 4 + 3] = TRUE;u16PasscodePlace++;
      bChanged = TRUE;
    }
  }
  static u16 u16PasscodeLength = 10000; //will be replaced after 7 seconds
  
  if (G_u32SystemTime1ms == ENTERPASSCODETIME && bChanged)
  {
    u16PasscodeLength = u16PasscodePlace;
    u16PasscodePlace = 0;
    LedOn(RED);
    LedOff(YELLOW);

  }
  else if (G_u32SystemTime1ms == ENTERPASSCODETIME)
  {
    u16PasscodeLength = 4;
    LedOn(RED);
    LedOff(YELLOW);
  }
  if (WasButtonPressed(BUTTON0) && bArrayPasscode[u16PasscodePlace * 4])
  {
    u16PasscodePlace++;
    ButtonAcknowledge(BUTTON0);
  }
  else if (WasButtonPressed(BUTTON1) && bArrayPasscode[u16PasscodePlace * 4 + 1])
  {
    u16PasscodePlace++;
    ButtonAcknowledge(BUTTON1);
  }
  else if (WasButtonPressed(BUTTON2) && bArrayPasscode[u16PasscodePlace * 4 + 2])
  {
    u16PasscodePlace++;
    ButtonAcknowledge(BUTTON2);
  }
  else if (WasButtonPressed(BUTTON3) && bArrayPasscode[u16PasscodePlace * 4 + 3])
  {
    u16PasscodePlace++;
    ButtonAcknowledge(BUTTON3);
  }
  
  if (WasButtonPressed(BUTTON0) || WasButtonPressed(BUTTON1) || WasButtonPressed(BUTTON2) || WasButtonPressed(BUTTON3))
    {
      ButtonAcknowledge(BUTTON0);
      ButtonAcknowledge(BUTTON1);
      ButtonAcknowledge(BUTTON2);
      ButtonAcknowledge(BUTTON3);
      LedOn(RED);
      u16PasscodePlace = 0;
      LedOff(WHITE);
      LedOff(PURPLE);
      LedOff(BLUE);
      LedOff(CYAN);
      LedOff(GREEN);
      LedOff(YELLOW);
      LedOff(ORANGE);
    }
  
  if (u16PasscodePlace == u16PasscodeLength)
  {
    static u16 u16WaveHeight = 0;
    
    //preforms a fancy light show
    if (G_u32SystemTime1ms % 80 == 0)//change num this to change rate of wave
    {
      u16WaveHeight++;
      LedPWM(WHITE, LED_PWM_75 - (u16WaveHeight % 8) * 2);
      LedPWM(PURPLE, LED_PWM_75 - ((u16WaveHeight + 1) % 8) * 2);
      LedPWM(BLUE, LED_PWM_75 - ((u16WaveHeight + 2) % 8) * 2);
      LedPWM(CYAN, LED_PWM_75 - ((u16WaveHeight + 3)% 8) * 2);
      LedPWM(GREEN, LED_PWM_75 - ((u16WaveHeight + 4) % 8) * 2);
      LedPWM(YELLOW, LED_PWM_75 - ((u16WaveHeight + 5)  % 8) * 2);
      LedPWM(ORANGE, LED_PWM_75 - ((u16WaveHeight + 6) % 8) * 2);
      LedPWM(RED, LED_PWM_75 - ((u16WaveHeight + 7) % 8) * 2);
      //the wave travels from right to left and it bright to dark
     }
#if 0  //i don't think this works here
    if (WasButtonPressed(BUTTON0) || WasButtonPressed(BUTTON1) || WasButtonPressed(BUTTON2) || WasButtonPressed(BUTTON3))
    {
      ButtonAcknowledge(BUTTON0);
      ButtonAcknowledge(BUTTON1);
      ButtonAcknowledge(BUTTON2);
      ButtonAcknowledge(BUTTON3);
      LedOn(RED);
      u16PasscodePlace = 0;
      LedOff(WHITE);
      LedOff(PURPLE);
      LedOff(BLUE);
      LedOff(CYAN);
      LedOff(GREEN);
      LedOff(YELLOW);
      LedOff(ORANGE);
    }
#endif
  }
  
  
} /* end UserApp1SM_Idle() */
     //This is just a comment to change the file

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */




/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
