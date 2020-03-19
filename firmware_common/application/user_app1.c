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

  seed.a = 17973488;  //used Google to randomly generate these numbers
  seed.b = 2699511989;
  seed.c = 1640752756;
  seed.d = 4215073069;
  
  if( 1 )
  {
    UserApp1_pfStateMachine = StartUp; //first state = Startup
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


static void StartUp(void) //basic menu system to generate the seed (at this point the seed is not that complicated)
{
  // needs to pick how many players will play too, right now make for 2 or 3 players 
  static u8 SU_prologue = 1;
  if (SU_prologue == 1)
  {
    LcdMessage(LINE1_START_ADDR, " Number of Players? ");
    LcdMessage(LINE2_START_ADDR, "2     3     4      5");
    SU_prologue = 0;
  }
  if (WasButtonPressed(BUTTON0))
  {
    seed.a = G_u32SystemTime1ms + 54982; //
    UserApp1_pfStateMachine = BrainState;
    GameState.max_players = 2;
    ButtonAcknowledge(BUTTON0);
    
  }
  else if (WasButtonPressed(BUTTON1))
  {
    seed.b = G_u32SystemTime1ms + 93507;
    UserApp1_pfStateMachine = BrainState;
    GameState.max_players = 3;
    ButtonAcknowledge(BUTTON1);
    
  }
  else if (WasButtonPressed(BUTTON2))
  {
    seed.c = G_u32SystemTime1ms + 79145;
    UserApp1_pfStateMachine = BrainState;
    GameState.max_players = 4;
    ButtonAcknowledge(BUTTON2);
    
  }
     
  else if (WasButtonPressed(BUTTON3))
  {
    seed.d = G_u32SystemTime1ms + 30686;
    UserApp1_pfStateMachine = BrainState;
    GameState.max_players = 5;
    ButtonAcknowledge(BUTTON3);
    
  }
  // no epilogue needed since not coming back to this State
}
//--------------------------------------put--the--version--code--here----------------------------------------------------
static void BrainState(void)
{
  // needs to check if the game is over (all but 1 player folds, player chips = 0)
    // needs to call generate cards at the begininning of a round
    // needs to call PlayerTurn
  LedOn(GREEN); //to indicate the BrainState is being run
  static int BS_prologue = 1;     // note prologue values need to be static in order to work properly     !!!
  if (BS_prologue == 1)
  {
    // don't know what needs to be in here to start
    BS_prologue = 0;
  }

  //epilogue:
    //  BS_prologue = 1
}

static void PlayerTurn(void)
{
  // prologue needs:  
                //  display "Player1's turn press a button" // so that other players don't see the Player1's cards
                //  round_start_seed(); // to assign the random values to the
}
//-----------------------------------------------------------------------------------------------------------------------
static void GenerateCards(void)
{
    static u8 remove_from_deck[52];       
                        // cards avaible in the deck, will be reset at the last loop of generate cards
                        // 0/Null means card not used yet, 1 means card has already been delt this round
    LedOn(YELLOW);  //just to help indicate the current state
    LedOff(GREEN);
    static u8 GCRun = 0; //should be 0 if first run of state, increments for each card delt
    if (GCRun == 0) // will generate the river then increment GCRun
    {
      GameState.river0 = GeneratedNumber(&seed) % 52;
      remove_from_deck[GameState.river0] = 1; // make it zero  
      GCRun = 1;  //should now become = 1
    }   //ends initialization of state
    
    if  (GCRun == 1)
    {
      GameState.river1 = GeneratedNumber(&seed) % 52;
      if (remove_from_deck[GameState.river1] != 1)
      {
        remove_from_deck[GameState.river1] = 1;    // "removes" card for deck
        GCRun = 2;
      }
    }
    if  (GCRun == 2)
    {
      GameState.river2 = GeneratedNumber(&seed) % 52;
      if (remove_from_deck[GameState.river2] != 1)
      {
        remove_from_deck[GameState.river2] = 1;    // "removes" card for deck
        GCRun = 3;
      }
    }
    if  (GCRun == 3)
    {
      GameState.river3 = GeneratedNumber(&seed) % 52;
      if (remove_from_deck[GameState.river3] != 1)
      {
        remove_from_deck[GameState.river3] = 1;    // "removes" card for deck
        GCRun = 4;
      }
    }
    if  (GCRun == 4)
    {
      GameState.river4 = GeneratedNumber(&seed) % 52;
      if (remove_from_deck[GameState.river4] != 1)
      {
        remove_from_deck[GameState.river4] = 1;    // "removes" card for deck
        GCRun = 5;
      }
    }
    // river has been assigned to the GameState river varibles
    
    // player1
    if  (GCRun == 5)    // don't know how to do it for a certain selected number of players just doing 2 players for now
    {
      Player1.hand0 = GeneratedNumber(&seed) % 52;
      if (remove_from_deck[Player1.hand0] != 1)
      {
        remove_from_deck[Player1.hand0] = 1;    // "removes" card for deck
        GCRun = 6;
      }
    }
    if  (GCRun == 6)    // don't know how to do it for a certain selected number of players just doing 2 players for now
    {
      Player1.hand1 = GeneratedNumber(&seed) % 52;
      if (remove_from_deck[Player1.hand1] != 1)
      {
        remove_from_deck[Player1.hand1] = 1;    // "removes" card for deck
        GCRun = 7;
      }
    }
    // player2
    if  (GCRun == 7)    // don't know how to do it for a certain selected number of players just doing 2 players for now
    {
      Player2.hand0 = GeneratedNumber(&seed) % 52;
      if (remove_from_deck[Player2.hand0] != 1)
      {
        remove_from_deck[Player2.hand0] = 1;    // "removes" card for deck
        GCRun = 8;
      }
    }
    if  (GCRun == 8)    // don't know how to do it for a certain selected number of players just doing 2 players for now
    {
      Player2.hand1 = GeneratedNumber(&seed) % 52;
      if (remove_from_deck[Player2.hand1] != 1)     
      {
        remove_from_deck[Player2.hand1] = 1;    // "removes" card for deck
        GCRun = 9;
      }
    }
    if (GCRun == 9)     // end of state epilogue
    {
      GCRun = 0;
      // "adds" the cards back to the deck
      remove_from_deck[GameState.river0] = 0;
      remove_from_deck[GameState.river1] = 0;
      remove_from_deck[GameState.river2] = 0;
      remove_from_deck[GameState.river3] = 0;
      remove_from_deck[GameState.river4] = 0;
        
      remove_from_deck[Player1.hand0] = 0; 
      remove_from_deck[Player1.hand1] = 0;
      remove_from_deck[Player2.hand0] = 0; 
      remove_from_deck[Player2.hand1] = 0;
      UserApp1_pfStateMachine = MainState;
    }
}
//----------------------------------------------------------------------------------------------------------------

static void UserApp1SM_Error(void)          
{
  //i think this happens if it takes longer then 1ms, unsure if it is
  LcdMessage(LINE1_START_ADDR, "     ERROR     ");
  LedOff(LCD_RED);
  LedOff(LCD_BLUE);
  LedOff(LCD_GREEN);
  LedOn(LCD_RED);
} /* end UserApp1SM_Error() */


/*******************************************************************************************************
Functions
*******************************************************************************************************/
void round_start_seed(void) // will adjust the seed value, happens at the beginning of each persons turn
{
  if (WasButtonPressed(BUTTON0))
  {
    seed.a = seed.a - G_u32SystemTime1ms;
    ButtonAcknowledge(BUTTON0);
    
  }
  else if (WasButtonPressed(BUTTON1))
  {
    seed.b = seed.b - G_u32SystemTime1ms;
    ButtonAcknowledge(BUTTON1);
    
  }
  else if (WasButtonPressed(BUTTON2))
  {
    seed.c = seed.c - G_u32SystemTime1ms;
    ButtonAcknowledge(BUTTON2);
    
  }
     
  else if (WasButtonPressed(BUTTON3))
  {
    seed.d = seed.d - G_u32SystemTime1ms;
    ButtonAcknowledge(BUTTON3);
    
  }
}
u32 GeneratedNumber(struct xorwow_state *state)
{
	/* Algorithm "xorwow" from p. 5 of Marsaglia, "Xorshift RNGs" Wikipedia */
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