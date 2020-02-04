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
static void Game0(void);
static void Game1(void);
static void Game2(void);
static void Game3(void);

//Put global veribals here
u32 TimePressFirst = 0; //Stores the First button press to help genertate a "random number"
u32 TimePressSecond = 0;

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
    
  }
  else if (WasButtonPressed(BUTTON1))
  {
    TimePressFirst = G_u32SystemTime1ms + 250;
    UserApp1_pfStateMachine = ChooseGame;
    ButtonAcknowledge(BUTTON1);
    
  }
  else if (WasButtonPressed(BUTTON2))
  {
    TimePressFirst = G_u32SystemTime1ms + 500;
    UserApp1_pfStateMachine = ChooseGame;
    ButtonAcknowledge(BUTTON2);
    
  }
     
  else if (WasButtonPressed(BUTTON3))
  {
    TimePressFirst = G_u32SystemTime1ms + 750;
    UserApp1_pfStateMachine = ChooseGame;
    ButtonAcknowledge(BUTTON3);
    
  }
}

static void ChooseGame(void)
{
  static int buttonPress = -1; 
  /*buttonPress will have the values
    -2 which means "waiting for button input"
    -1 which means "display the main menu"
    0 which means "display Game0 menu"
    1 which means "display Game1 menu"
    2 which means "display Game2 menu"
    3 which means "display Game3 menu"
  */
  if (buttonPress == -1)
  {
    LcdMessage(LINE1_START_ADDR, "Select a Game   ");
    LcdMessage(LINE2_START_ADDR, "0    ");
    LcdMessage(LINE2_START_ADDR + 6, "1");
    LcdMessage(LINE2_START_ADDR + 13, "2");
    LcdMessage(LINE2_START_ADDR + 16, "   3");
    buttonPress = -2;
  }
  if (buttonPress == -2 && WasButtonPressed(BUTTON0) || buttonPress == 0) //this is a submenu//could turn this into a funciton
  {
    if (WasButtonPressed(BUTTON0))
    {
      LcdMessage(LINE1_START_ADDR, "Hangman      ");
      LcdMessage(LINE2_START_ADDR, "Start         ");
      LcdMessage(LINE2_START_ADDR + 16, "Back");
    }
    buttonPress = 0;
    ButtonAcknowledge(BUTTON0);
    TimePressFirst *= (G_u32SystemTime1ms % 100);
    if (WasButtonPressed(BUTTON0))
    {
      UserApp1_pfStateMachine = Game0;  //acivates the game //doesn't seem to want to activate
      ButtonAcknowledge(BUTTON0);
    }
    else if (WasButtonPressed(BUTTON3)) //quits the sub menu
    {
      buttonPress = -1;
      ButtonAcknowledge(BUTTON3);
    }
  }
  if (buttonPress == -2 && WasButtonPressed(BUTTON1) || buttonPress == 1) //this is a submenu//could turn this into a funciton
  {
    if (WasButtonPressed(BUTTON1))
    {
      LcdMessage(LINE1_START_ADDR, "Game1?        ");
      LcdMessage(LINE2_START_ADDR, "Start         ");
      LcdMessage(LINE2_START_ADDR + 16, "Back");
    }
    buttonPress = 1;
    ButtonAcknowledge(BUTTON1);
    TimePressFirst *= (G_u32SystemTime1ms % 75);
    if (WasButtonPressed(BUTTON0))
    {
      UserApp1_pfStateMachine = Game1;  //acivates the game
      ButtonAcknowledge(BUTTON1);
    }
    else if (WasButtonPressed(BUTTON3)) //quits the sub menu
    {
      buttonPress = -1;
      ButtonAcknowledge(BUTTON3);
    }
  }
  if (buttonPress == -2 && WasButtonPressed(BUTTON2) || buttonPress == 2) //this is a submenu//could turn this into a funciton
  {
    if (WasButtonPressed(BUTTON2))
    {
      LcdMessage(LINE1_START_ADDR, "Game2?       ");
      LcdMessage(LINE2_START_ADDR, "Start         ");
      LcdMessage(LINE2_START_ADDR + 16, "Back");
    }
    buttonPress = 2;
    ButtonAcknowledge(BUTTON2);
    TimePressFirst *= (G_u32SystemTime1ms % 80);
    if (WasButtonPressed(BUTTON0))
    {
      UserApp1_pfStateMachine = Game2;  //acivates the game
      ButtonAcknowledge(BUTTON0);
    }
    else if (WasButtonPressed(BUTTON3)) //quits the sub menu
    {
      buttonPress = -1;
      ButtonAcknowledge(BUTTON3);
    }
  }
  if (buttonPress == -2 && WasButtonPressed(BUTTON3) || buttonPress == 3) //this is a submenu//could turn this into a funciton
  {
    if (WasButtonPressed(BUTTON3))
    {
      LcdMessage(LINE1_START_ADDR, "Game3?       ");
      LcdMessage(LINE2_START_ADDR, "Start         ");
      LcdMessage(LINE2_START_ADDR + 16, "Back");
    }
    buttonPress = 3;
    ButtonAcknowledge(BUTTON3);
    TimePressFirst *= (G_u32SystemTime1ms % 90);
    if (WasButtonPressed(BUTTON0))
    {
      UserApp1_pfStateMachine = Game3;  //acivates the game
      ButtonAcknowledge(BUTTON0);
    }
    else if (WasButtonPressed(BUTTON3)) //quits the sub menu
    {
      buttonPress = -1;
      ButtonAcknowledge(BUTTON3);
    }
  }
  /*
  else if (WasButtonPressed(BUTTON1))
  {
    TimePressFirst *= (G_u32SystemTime1ms % 75);
    UserApp1_pfStateMachine = Game1;
    ButtonAcknowledge(BUTTON1);
  }
  else if (WasButtonPressed(BUTTON2))
  {
    TimePressFirst *= (G_u32SystemTime1ms % 80);
    UserApp1_pfStateMachine = Game2;
    ButtonAcknowledge(BUTTON2);
  }
  else if (WasButtonPressed(BUTTON3))
  {
    TimePressFirst *= (G_u32SystemTime1ms % 90);
    UserApp1_pfStateMachine = Game3;
    ButtonAcknowledge(BUTTON3);
  }
  */
}

static void Game0(void)
{
  LcdMessage(LINE1_START_ADDR, "Game0        ");
  LedOn(RED);
}

static void Game1(void)
{
  LcdMessage(LINE1_START_ADDR, "Game1        ");
  LedOn(WHITE);
}

static void Game2(void)
{
  LcdMessage(LINE1_START_ADDR, "Game2        ");
  LedOn(CYAN);
}
static void Game3(void)
{
  LcdMessage(LINE1_START_ADDR, "Game3        ");
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