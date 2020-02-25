//simple master for the games

//version: UIForTexasHoldem

//user will be givin 2 "random" cards then be asked to: check, bet, fold
//  check will cause no bet and the player turn is over
//  bet will have a submenu/suboptions, containing buttons of less, more, all in
//  fold will continue the round but player is out
/*example of UI
  H = hearts
  C = clubs
  D = dimonds
  S = spades

  Q = quit to save the game (feature to add)
CPU Turn:
    ______________________
    |Pot:380        AC 2H|                 
    |   CPU1: Checks     |                    
    ______________________
    O      O       O     O
    ______________________
    |7H 8S|      7S AC 2H|                 
    |   CPU1: Bets 20    |                    
    ______________________
    O      O       O     O
    ______________________
    |7H 8S|      7S AC 2H|    //may reconsider this one             
    |   CPU2: Matches    |    //matches is an odd word
    ______________________
    O      O       O     O
    ______________________
    |7H 8S|8D 9H 7S AC 2H|                 
    |   CPU2: Folds      |                    
    ______________________
    O      O       O     O
Player Turn:
    ______________________
    |7H 8S|              |                 
    |Check  Bet   Fold  Q|                    
    ______________________
    O      O       O     O
    ______________________
    |7H 8S|      7S AC 2H|                 
    |Check  Bet   Fold  Q|                    
    ______________________
    O      O       O     O
    ______________________
    |7H 8S|   9H 7S AC 2H|                 
    |Match  Bet   Fold  Q|                    
    ______________________
    O      O       O     O
    ______________________
    |7H 8S|JD 9H 7S AC 2H|                 
    |Check  Bet   Fold  Q|                    
    ______________________
    O      O       O     O
BetSubmenu:
    I think the top one looks better with the whole back word
    ______________________
    |Chips: 5089 Bet: 350|    //adds 10 to the bet for each up
    |Up  Down  Enter Back|    //if hold goes up quickly           
    ______________________
    O      O       O     O
    ______________________
    |Pot: 5320   Bet: 350|    //I don't know if we need the Pot    
    |Up  Down  Enter    B|    //should show the pot somewhere else              
    ______________________
    O      O       O     O

End of round (show hands):

    ______________________
    |   JD 9H 7S AC 2H   |  //river at top           
    |7H 8S| 6H 5H | 4S KS|  //hands at bottom, player hand on far right              
    ______________________
    O      O       O     O
    ______________________
    |   JD 9H 7S AC 2H   |  //river at top //animate it   
    |      |7H 8S|       |  //winner hand more to middle            
    ______________________
    O      O       O     O
    ______________________
    |   Player 1 Wins    |             
    |     Pot: 5320      |                    
    ______________________
    O      O       O     O




*/

#include "configuration.h"

//Global variable definitions with scope across entire project.
//All Global variable names shall start with "G_<type>UserApp1"

volatile u32 G_u32UserApp1Flags;                          /*!< @brief Global state flags */
//A variable should be declared volatile whenever its value could change unexpectedly. aka. interrupts

/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */ //used often
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */
extern volatile u32 G_u32ApplicationFlags;                /*!< @brief From main.c */

static fnCode_type UserApp1_pfStateMachine;               /*!< @brief The state machine function pointer */
//static u32 UserApp1_u32Timeout;                           /*!< @brief Timeout counter used across states */

//states initialized
static void Startup(void);
static void MainState(void);

struct xorwow_state;
//--------------------------------------put--the--version--code--here----------------------------------------------------
//new initialized states:

void TestFunction2(void);// To be removed just an example of using a fuction from another file
void TestFunction3(void);// To be removed just an example of using a fuction from another file

//-----------------------------------------------------------------------------------------------------------------------

//Structures here
struct xorwow_state{  //stores the values for the Random Number Generator
  u32 a, b, c, d;
  u32 counter;
}seed;

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
  LcdMessage(LINE1_START_ADDR, "Basic Menu Start    ");
  LcdMessage(LINE2_START_ADDR, "Press any button    ");
  seed.a = 580938204;
  seed.b = 325414048;
  seed.c = 486034763;
  seed.d = 346141525;


  
  TestFunction2();// To be removed just an example of using a fuction from another file
  TestFunction3();// To be removed just an example of using a fuction from another file
  
  
  if( 1 )
  {
    UserApp1_pfStateMachine = Startup; //first state = Startup
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_pfStateMachine = UserApp1SM_Error;
  }
} /* end UserApp1Initialize() */


void UserApp1RunActiveState(void)//runs the state that  UserApp1_pfStateMachine(); points to
{
  UserApp1_pfStateMachine();
} /* end UserApp1RunActiveState */


static void Startup(void) //basic menu system to generate the seed (at this point the seed is not that complicated)
{

  if (WasButtonPressed(BUTTON0))
  {
    seed.a = G_u32SystemTime1ms;
    UserApp1_pfStateMachine = MainState;
    ButtonAcknowledge(BUTTON0);
    
  }
  else if (WasButtonPressed(BUTTON1))
  {
    seed.b = G_u32SystemTime1ms + 250;
    UserApp1_pfStateMachine = MainState;
    ButtonAcknowledge(BUTTON1);
    
  }
  else if (WasButtonPressed(BUTTON2))
  {
    seed.c = G_u32SystemTime1ms + 500;
    UserApp1_pfStateMachine = MainState;
    ButtonAcknowledge(BUTTON2);
    
  }
     
  else if (WasButtonPressed(BUTTON3))
  {
    seed.d = G_u32SystemTime1ms + 750;
    UserApp1_pfStateMachine = MainState;
    ButtonAcknowledge(BUTTON3);
    
  }
}
//--------------------------------------put--the--version--code--here----------------------------------------------------
static void MainState(void)
{
  LedOn(GREEN); //to indicate the MainState is being run
  
}
//-----------------------------------------------------------------------------------------------------------------------


static void UserApp1SM_Error(void)          
{
  //i think this happens if it takes longer then 1ms, unsure if it is
  LcdMessage(LINE1_START_ADDR, "     ERROR     ");
  LedOff(LCD_RED);
  LedOff(LCD_BLUE);
  LedOff(LCD_GREEN);
  LedOn(LCD_RED);
} /* end UserApp1SM_Error() */

