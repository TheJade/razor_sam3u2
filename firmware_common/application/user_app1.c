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

static fnCode_type UserApp1_pfStateMachine;               /*!< @brief The state machine function pointer */
//static u32 UserApp1_u32Timeout;                           /*!< @brief Timeout counter used across states */
static void ChooseGame(void);
static void Startup(void);
static void Game1(void);
static void Game2(void);
static void Game3(void);
static void Game4(void);

//Put global veribals here
u32 TimePressFirst = 0; //Stores the
u32 numPressSecond = 0;

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
  LcdMessage(LINE1_START_ADDR, "Press a Button    ");
  
  /*make a wave like feture on the board */
  
  if( 1 )
  {
    UserApp1_pfStateMachine = Startup;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_pfStateMachine = UserApp1SM_Error;
  }
} /* end UserApp1Initialize() */

static void Startup(void) //start up
{
  LedOn(ORANGE); //Just for testing
  //void LcdMessage(u8 u8Address_, u8 *u8Message_) 
  if (WasButtonPressed(BUTTON0))
  {
    TimePressFirst = G_u32SystemTime1ms;
    UserApp1_pfStateMachine = ChooseGame;
    ButtonAcknowledge(BUTTON0);
    LcdMessage(LINE1_START_ADDR, "Select a Game   "); //i can't seem to change the display
    LcdMessage(LINE2_START_ADDR, "0");
    LcdMessage(LINE2_START_ADDR + 6, "1");
    LcdMessage(LINE2_START_ADDR + 13, "2");
    LcdMessage(LINE2_END_ADDR, "3");
  }
  else if (WasButtonPressed(BUTTON1))
  {
    TimePressFirst = G_u32SystemTime1ms + 250;
    UserApp1_pfStateMachine = ChooseGame;
    ButtonAcknowledge(BUTTON1);
    LcdMessage(LINE1_START_ADDR, "Select a Game   "); //i can't seem to change the display
    LcdMessage(LINE2_START_ADDR, "0");
    LcdMessage(LINE2_START_ADDR + 6, "1");
    LcdMessage(LINE2_START_ADDR + 13, "2");
    LcdMessage(LINE2_END_ADDR, "3");
  }
  else if (WasButtonPressed(BUTTON2))
  {
    TimePressFirst = G_u32SystemTime1ms + 500;
    UserApp1_pfStateMachine = ChooseGame;
    ButtonAcknowledge(BUTTON2);
    LcdMessage(LINE1_START_ADDR, "Select a Game   "); //i can't seem to change the display
    LcdMessage(LINE2_START_ADDR, "0");
    LcdMessage(LINE2_START_ADDR + 6, "1");
    LcdMessage(LINE2_START_ADDR + 13, "2");
    LcdMessage(LINE2_END_ADDR, "3");
  }
     
  else if (WasButtonPressed(BUTTON3))
  {
    TimePressFirst = G_u32SystemTime1ms + 750;
    UserApp1_pfStateMachine = ChooseGame;
    ButtonAcknowledge(BUTTON3);
    LcdMessage(LINE1_START_ADDR, "Select a Game   "); //i can't seem to change the display
    LcdMessage(LINE2_START_ADDR, "0");
    LcdMessage(LINE2_START_ADDR + 6, "1");
    LcdMessage(LINE2_START_ADDR + 13, "2");
    LcdMessage(LINE2_END_ADDR, "3");
  }
}

static void ChooseGame(void)
{
  static int button0press = 0;
  LedOn(GREEN);//testing
  LedOff(ORANGE);//testing
  LedOff(WHITE);//testing
  if (WasButtonPressed(BUTTON0) || button0press) //this is a submenu
  {
    button0press = 1;
    ButtonAcknowledge(BUTTON0);
    TimePressFirst *= (G_u32SystemTime1ms % 100);
    LcdMessage(LINE1_START_ADDR, "Hangman      ");
    LcdMessage(LINE2_START_ADDR, "Start        ");
    LcdMessage(LINE2_START_ADDR + 13, "Back");
    if (WasButtonPressed(BUTTON0))
    {
      UserApp1_pfStateMachine = Game1;  //acivates the game
      ButtonAcknowledge(BUTTON0);
    }
    else if (WasButtonPressed(BUTTON3)) //quits the sub menu
    {
      button0press = 0;
      ButtonAcknowledge(BUTTON3);
    }
  }
  else if (WasButtonPressed(BUTTON1))
  {
    TimePressFirst *= (G_u32SystemTime1ms % 75);
    UserApp1_pfStateMachine = Game2;
    ButtonAcknowledge(BUTTON1);
  }
  else if (WasButtonPressed(BUTTON2))
  {
    TimePressFirst *= (G_u32SystemTime1ms % 80);
    UserApp1_pfStateMachine = Game3;
    ButtonAcknowledge(BUTTON2);
  }
  else if (WasButtonPressed(BUTTON3))
  {
    TimePressFirst *= (G_u32SystemTime1ms % 90);
    UserApp1_pfStateMachine = Game4;
    ButtonAcknowledge(BUTTON3);
  }
}

static void Game1(void)
{
  LcdMessage(LINE1_START_ADDR, "Game1        ");
  LedOn(RED);
}

static void Game2(void)
{
  LcdMessage(LINE1_START_ADDR, "Game2        ");
  LedOn(WHITE);
}

static void Game3(void)
{
  LcdMessage(LINE1_START_ADDR, "Game3        ");
  LedOn(CYAN);
}
static void Game4(void)
{
  LcdMessage(LINE1_START_ADDR, "Game4        ");
  LedOn(YELLOW);
}
  
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


     

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */




/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/