//simple master for the games

//version: LABEL_THE_REPOSITORY
#include <stdio.h>
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
//--------------------------------------put--the--version--code--here----------------------------------------------------
//new initialized states:

void TestFunction2(void);// To be removed just an example of using a fuction from another file
void TestFunction3(void);// To be removed just an example of using a fuction from another file

struct xorwow_state;

u32 GeneratedNumber(struct xorwow_state *state);



//-----------------------------------------------------------------------------------------------------------------------

//Put global veribals here

//Structures here
struct xorwow_state{  //stores the values for the Random Number Generator
  u8 a, b, c, d;
  u8 counter;
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
  
  TestFunction2();// To be removed just an example of using a fuction from another file
  TestFunction3();// To be removed just an example of using a fuction from another file

  //initializes the seeds so that they have some values will be reassigned later
  seed.a = 78; //Stores the First button press to help genertate a "random number"
  seed.b = 212; //random number I grabbed
  seed.c = 125;  //another random number I grabbed
  seed.d = 12; //last random number I grabbed
  
  
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
    seed.a = G_u32SystemTime1ms % 256; //cuz max u8 size is 256
    UserApp1_pfStateMachine = MainState;
    ButtonAcknowledge(BUTTON0);
    
  }
  else if (WasButtonPressed(BUTTON1))
  {
    seed.b = G_u32SystemTime1ms % 256; //cuz max u8 size is 256
    UserApp1_pfStateMachine = MainState;
    ButtonAcknowledge(BUTTON1);
    
  }
  else if (WasButtonPressed(BUTTON2))
  {
    seed.c = G_u32SystemTime1ms % 256; //cuz max u8 size is 256
    UserApp1_pfStateMachine = MainState;
    ButtonAcknowledge(BUTTON2);
    
  }
     
  else if (WasButtonPressed(BUTTON3))
  {
    seed.d = G_u32SystemTime1ms % 256; //cuz max u8 size is 256
    UserApp1_pfStateMachine = MainState;
    ButtonAcknowledge(BUTTON3);
    
  }
}
//--------------------------------------put--the--version--code--here----------------------------------------------------
static void MainState(void)
{
  LedOn(GREEN); //to indicate the MainState is being run
  static int x = 0;
  if (x == 0)
  {
    
    LcdMessage(LINE1_START_ADDR, "                    ");
    LcdMessage(LINE2_START_ADDR, "                    ");
    u8 GenNum = GeneratedNumber(&seed);
   
    LcdMessage(LINE1_START_ADDR, &GenNum); //may need to do some formatting for this
    LcdMessage(LINE2_START_ADDR, &seed.a); //may need to do some formatting for this
    x = 1;
  }



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


//------------------------------------Functions---------------------------------------------------------------------------

//code adapeted from the XorShift method of psuedorandom number genertation (PRNG)
u32 GeneratedNumber(struct xorwow_state *state)
{
	/* Algorithm "xorwow" from p. 5 of Marsaglia, "Xorshift RNGs" */
	u32 t = state->d;

	u32 const s = state->a;
	state->d = state->c;
	state->c = state->b;
	state->b = s;

	t ^= t >> 2;
	t ^= t << 1;
	t ^= s ^ (s << 4);
	state->a = t;

	state->counter += 362437;
	return t + state->counter;
}