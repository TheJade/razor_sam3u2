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
static void Game1 (void);

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
  
  /*make a wave like feture on the board */
  
  if( 1 )
  {
    UserApp1_pfStateMachine = Game1;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_pfStateMachine = UserApp1SM_Error;
  }
} /* end UserApp1Initialize() */

void UserApp1RunActiveState(void)
{
  UserApp1_pfStateMachine();

} /* end UserApp1RunActiveState */



/*game in C
first edition will likely need to change to debug for board
This is going to be a sound timer game
User will be required to try to time the beat
Hit the button at the same time as the beat 
Led indicators on for the beat time
*/

/*version 1 of the code is buggy and can be found in the Games section of 
the GitHub folder on my laptop, i just copy pasta it into her for record purposes
*/

static void Game1(void)
{
  
} /* end UserApp1SM_Idle() */
     

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  //should increase in difficulty
    //speed increases slowly
    //first gives about 5 button presses until
    //start
    //sound turns off eventually
    //leds turn off eventually
    static int FirstTime = 1;
    if (FirstTime = 1) //so that id doesn't display each loop
    {
        LcdMessage(LINE1_START_ADDR, "Welcome 2 Conductor");
        LcdMessage(LINE2_START_ADDR, "Start     "); //need to test out the spaces after
    }
    LcdMessage(LINE2_END_ADDR - 3, "QUIT"); //Will continue to be here

    static int GameLevel = 0;   //difficulty will increase
    static int startTime = 0;   //start timeing for the beats
    static int Display = 0; //will be 1 if a average time should be shown to the user
                            //will be count down from 11 to 6 (5) button presses to start
                            //will then count from 6 to 1 when user is being timed
    int forgivness = 300 - (GameLevel * 25); //In ms The closeness the user has to be to the beat divided by two to pass it
                    //this is an import to adjust the difficulty
    static int interval = 500; //in ms //the time between beats
                    //adjust this line sometimes don't know when yet
    static int averageTime = 0; //should change on the real button presses the user has
                    //build a equation later on for this when Display = 1
                    //should be displayed to the user

    if (GameLevel > 0)  //functions will activate/disable depending on level
    {
        //NEED TO:
            //reset the startTime and and average time

        if (startTime == 0)//sets all the values to start
        {
            Display = 11; // begins the count down
            startTime = G_u32SystemTime1ms; //sets the start time
        }

        if ((Display > 1) && ((G_u32SystemTime1ms - startTime) % interval <= 6))//preform the function for 6 ms
        {                               //may need to adjust the parameteres of the if
            //buzzer sounds for 6 ms    //or something //maybe change for each level

            //LED maybe the same time
        }

        if (Display > 1 && Display < 7 && (WasButtonPressed(BUTTON0) || WasButtonPressed(BUTTON1) || WasButtonPressed(BUTTON2)))    //average acumulation
        {
            ButtonAcknowledge(BUTTON0);
            ButtonAcknowledge(BUTTON1);
            ButtonAcknowledge(BUTTON2);

            averageTime = ((G_u32SystemTime1ms - startTime) % interval - 3); //the time difference I think //need to adjust to make the average


        }


        if (GameLevel < 5) //LED     //will need to make adjustments on the activation times    //may change this
        {
            //LEDs flash on at the press time should last the duration of the forgivness of the level
        }

        

    } //end game run "function"

    if ((Display > 1) && (Display < 7)) //disoplays the current average time
    {
        //turns off after 3 seconds
    }

    else if (WasButtonPressed(BUTTON0)) //start game option
    {
        LcdMessage(LINE1_START_ADDR, "                   "); //coverse the previous message
        ButtonAcknowledge(BUTTON0);
        GameLevel = 1;
        FirstTime = 0; //incase the user pressed the button during welcome message
    }
    if (WasButtonPressed(BUTTON3)) //Quit option should show final score (level made)
    {
        UserApp1_pfStateMachine = ChooseGame; //when integrated with "RandomNumberGenertor" will work well
    }
    
    LCDMessage(LINE1_START_ADDR, " ");
} /* end UserApp1SM_Error() */




/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
