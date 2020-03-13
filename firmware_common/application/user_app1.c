//simple master for the games

//version: LABEL_THE_REPOSITORY

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
static void GenerateCards(void);        // fills the structures with random cards, to be run at begginning of each round
//--------------------------------------put--the--version--code--here----------------------------------------------------
//new initialized states:

void TestFunction2(void);// To be removed just an example of using a fuction from another file
void TestFunction3(void);// To be removed just an example of using a fuction from another file

struct xorwow_state;
struct character;
struct GameStates;

u32 GeneratedNumber(struct xorwow_state *state);

//Structures here
struct xorwow_state{  //stores the values for the Random Number Generator
  u32 a, b, c, d;
  u32 counter;
}seed;

// note: values can't be assigned to sturcture elements right away aka. cant just do int chips = 250; // an error will happen
//may have to be declared static so value won't change don't know at this point if it has to be, I'm pretty sure it doesn't have to since it is global
struct character{ // either human or bot the being has, gets initialized in Initialize state
  //could reduce the number of variables but for easy of read, I will keep many variabels for now
  int chips;  //chips the character has should be greater then -1
  u8 hand0; //first card in the character's hand, has integer value corresponting to a certain card
  u8 hand1; //first card in the character's hand, has integer value corresponting to a certain card

  u8 fold;  // is 1 if the player hasn't folded, is 0 if the player has folded
  u8 human; // is 1 if the player is human, is 2 for tigers, is 0 otherwise
      // helps determine if the ai should play the character

  //player name I could also add

};
// Player1 and Player2 must be global
static struct character Player1;
static struct character Player2;

struct GameStates{
  //don't need this line//u8 players_delt = 0; // helps in Generating the Cards state
  u8 max_players; //number of player in the game should be setable
  u8 river0;  //holds the first card placed in the river
  u8 river1;  
  u8 river2;
  u8 river3;
  u8 river4;  //holds the last card placed in the river
}GameState;

//-----------------------------------------------------------------------------------------------------------------------

//Put global veribals here
static int x = 1;       // is used in the main state

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
  seed.a = 523; //Stores the First button press to help genertate a "random number"
  seed.b = 212; //random number I grabbed
  seed.c = 1177;  //another random number I grabbed
  seed.d = 1279; //last random number I grabbed
  
  // to be incorperated later on in a start up menu or something
  GameState.max_players = 2; 
  static struct character Player1;
  static struct character Player2;
  Player1.chips = 250;  
  Player1.chips = 250;
  // end the menu add stuff
  
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
    seed.a = G_u32SystemTime1ms + 162;  //just some additional psudeorandomness
    UserApp1_pfStateMachine = MainState;
    ButtonAcknowledge(BUTTON0);
    
  }
  else if (WasButtonPressed(BUTTON1))
  {
    seed.b = G_u32SystemTime1ms + 2576; //could assign value to seed.b but causes the first GenNumber
    UserApp1_pfStateMachine = MainState;        //instance the same aka. GenNum returns value based on seed.a
    ButtonAcknowledge(BUTTON1);
    
  }
  else if (WasButtonPressed(BUTTON2))
  {
    seed.c = G_u32SystemTime1ms + 7826;
    UserApp1_pfStateMachine = MainState;
    ButtonAcknowledge(BUTTON2);
    
  }
     
  else if (WasButtonPressed(BUTTON3))
  {
    seed.d = G_u32SystemTime1ms + 8716; 
    UserApp1_pfStateMachine = MainState;
    ButtonAcknowledge(BUTTON3);
    
  }
}
//--------------------------------------put--the--version--code--here----------------------------------------------------
static void MainState(void)
{
  static u8 *deck[] = { // just be aware thi is not global (can only be used in this function)
            "2D", //index is 0
            "3D",
            "4D", //called by u8 *CardDisplay = deck[2];
            "5D",         //then LcdMessage(LINE2_START_ADDR, CardDisplay);
            "6D",
            "7D",
            "8D",
            "9D",
            "0D",
            "JD",
            "QD",
            "KD",
            "AD",
            
            "2C",
            "3C",
            "4C",
            "5C",
            "6C",
            "7C",
            "8C",
            "9C",
            "0C",
            "JC",
            "QC",
            "KC",
            "AC",
            
            "2S",
            "3S",
            "4S",
            "5S",
            "6S",
            "7S",
            "8S",
            "9S",
            "0S",
            "JS",
            "QS",
            "KS",
            "AS",
            
            "2H",
            "3H",
            "4H",
            "5H",
            "6H",
            "7H",
            "8H",
            "9H",
            "0H", //10 of hearts
            "JH",
            "QH",
            "KH",
            "AH"
      };
  LedOn(GREEN); //to indicate the MainState is being run
       // 0 = wait till input state
  if (x == 1)
  {
    UserApp1_pfStateMachine = GenerateCards;    // will populate the GameState.river and Player1.hand

    LcdMessage(LINE1_START_ADDR, "                    ");       // 20 chars long
    LcdMessage(LINE2_START_ADDR, "                    ");
    x = 2;
  }
  else if (x == 2)      // will happen after the GenerateCards state runs its stuff
  {
    LcdMessage(LINE2_START_ADDR, deck[Player1.hand0]);
    LcdMessage(LINE2_START_ADDR + 3, deck[Player1.hand1]);
    LcdMessage(LINE2_START_ADDR + 15, deck[Player2.hand0]);
    LcdMessage(LINE2_START_ADDR + 18, deck[Player2.hand1]);
    x = 3;      // will wait on 3 until button pressed then deal out river
  }
  if (x == 4)
  {
    LcdMessage(LINE1_START_ADDR, deck[GameState.river0]);
    LcdMessage(LINE1_START_ADDR + 3, deck[GameState.river1]);
    LcdMessage(LINE1_START_ADDR + 6, deck[GameState.river2]);
    x = 5;      //will wait on 5 til the button is pressed to deal next card
  }
  if (x == 6)
  {
    LcdMessage(LINE1_START_ADDR + 9, deck[GameState.river3]);
    x = 7;      //will wait on 5 til the button is pressed to deal next card
  }
  if (x == 8)
  {
    LcdMessage(LINE1_START_ADDR + 12, deck[GameState.river4]);
    x = 9;      //will wait on 5 til the button is pressed to deal next card
  }
    
  else if (WasButtonPressed(BUTTON0) || WasButtonPressed(BUTTON1) || WasButtonPressed(BUTTON2))
  {
    x++;
    ButtonAcknowledge(BUTTON0);
    ButtonAcknowledge(BUTTON1);
    ButtonAcknowledge(BUTTON2);
    ButtonAcknowledge(BUTTON3); // don't need this line but can't hurt so...
  }
  if (WasButtonPressed(BUTTON3))        // will restart the dealing
  {
    x = 1;
    ButtonAcknowledge(BUTTON3);
  }



}

static void GenerateCards(void)
{
    static u8 deck[52];        // not to be confused with deck in the MainState
                        // cards avaible in the deck, will be reset at the last loop of generate cards
                        // 0/Null means card not used yet, 1 means card has already been delt this round
    LedOn(YELLOW);  //just to help indicate the current state
    LedOff(GREEN);
    static u8 GCRun = 0; //should be 0 if first run of state, increments for each card delt
    if (GCRun == 0) // will generate the river then increment GCRun
    {
      GameState.river0 = GeneratedNumber(&seed) % 52;
      deck[GameState.river0] = 1; // make it zero  
      GCRun = 1;  //should now become = 1
    }   //ends initialization of state
    
    if  (GCRun == 1)
    {
      GameState.river1 = GeneratedNumber(&seed) % 52;
      if (deck[GameState.river1] != 1)
      {
        deck[GameState.river1] = 1;    // "removes" card for deck
        GCRun = 2;
      }
    }
    if  (GCRun == 2)
    {
      GameState.river2 = GeneratedNumber(&seed) % 52;
      if (deck[GameState.river2] != 1)
      {
        deck[GameState.river2] = 1;    // "removes" card for deck
        GCRun = 3;
      }
    }
    if  (GCRun == 3)
    {
      GameState.river3 = GeneratedNumber(&seed) % 52;
      if (deck[GameState.river3] != 1)
      {
        deck[GameState.river3] = 1;    // "removes" card for deck
        GCRun = 4;
      }
    }
    if  (GCRun == 4)
    {
      GameState.river4 = GeneratedNumber(&seed) % 52;
      if (deck[GameState.river4] != 1)
      {
        deck[GameState.river4] = 1;    // "removes" card for deck
        GCRun = 5;
      }
    }
    // river has been assigned to the GameState river varibles
    
    // player1
    if  (GCRun == 5)    // don't know how to do it for a certain selected number of players just doing 2 players for now
    {
      Player1.hand0 = GeneratedNumber(&seed) % 52;
      if (deck[Player1.hand0] != 1)
      {
        deck[Player1.hand0] = 1;    // "removes" card for deck
        GCRun = 6;
      }
    }
    if  (GCRun == 6)    // don't know how to do it for a certain selected number of players just doing 2 players for now
    {
      Player1.hand1 = GeneratedNumber(&seed) % 52;
      if (deck[Player1.hand1] != 1)
      {
        deck[Player1.hand1] = 1;    // "removes" card for deck
        GCRun = 7;
      }
    }
    // player2
    if  (GCRun == 7)    // don't know how to do it for a certain selected number of players just doing 2 players for now
    {
      Player2.hand0 = GeneratedNumber(&seed) % 52;
      if (deck[Player2.hand0] != 1)
      {
        deck[Player2.hand0] = 1;    // "removes" card for deck
        GCRun = 8;
      }
    }
    if  (GCRun == 8)    // don't know how to do it for a certain selected number of players just doing 2 players for now
    {
      Player2.hand1 = GeneratedNumber(&seed) % 52;
      if (deck[Player2.hand1] != 1)     
      {
        deck[Player2.hand1] = 1;    // "removes" card for deck
        GCRun = 9;
      }
    }
    if (GCRun == 9)     // end of state epilogue
    {
      GCRun = 0;
      // "adds" the cards back to the deck
      deck[GameState.river0] = 0;
      deck[GameState.river1] = 0;
      deck[GameState.river2] = 0;
      deck[GameState.river3] = 0;
      deck[GameState.river4] = 0;
        
      deck[Player1.hand0] = 0; 
      deck[Player1.hand1] = 0;
      deck[Player2.hand0] = 0; 
      deck[Player2.hand1] = 0;
      UserApp1_pfStateMachine = MainState;
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