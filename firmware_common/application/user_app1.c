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



static struct Character Player; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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
  
  Player.player_name[0] = "Player1";    // can't be placed in user_app1.h, thought that they should be ah whatever
  Player.player_name[1] = "Player2";
  Player.player_name[2] = "Player3";
  Player.player_name[3] = "Player4";
  Player.player_name[4] = "Player5";

  Player.chips[0] = 250;    // can't be placed in user_app1.h, thought that they should be ah whatever
  Player.chips[1] = 250;
  Player.chips[2] = 250;
  Player.chips[3] = 250;
  Player.chips[4] = 250;
  
  GameState.player_turn = 0;

  GameState.round = 0;

  GameState.highest_bet = 0;

  
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
  static u8 SU_prologue = 1;  // don't need to reset it back to 0 since this state just runs once
  if (SU_prologue == 1)
  {
    LcdMessage(LINE1_START_ADDR, " Number of Players? ");
    LcdMessage(LINE2_START_ADDR, "2     3     4      5");
    SU_prologue = 0;
  }
  if (WasButtonPressed(BUTTON0))
  {
    seed.d = G_u32SystemTime1ms + 54982; // may or may not need to assign each to seed.d
    UserApp1_pfStateMachine = BrainState;
    GameState.max_players = 2;
    GameState.player_start = seed.d % 2;  // will start the game off with a random player
    ButtonAcknowledge(BUTTON0);
    
  }
  else if (WasButtonPressed(BUTTON1))
  {
    seed.d = G_u32SystemTime1ms + 93507;
    UserApp1_pfStateMachine = BrainState;
    GameState.max_players = 3;
    GameState.player_start = seed.d % 3;  // will start the game off with a random player
    ButtonAcknowledge(BUTTON1);
    
  }
  else if (WasButtonPressed(BUTTON2))
  {
    seed.d = G_u32SystemTime1ms + 79145;
    UserApp1_pfStateMachine = BrainState;
    GameState.max_players = 4;
    GameState.player_start = seed.d % 4;  // will start the game off with a random player
    ButtonAcknowledge(BUTTON2);
    
  }
     
  else if (WasButtonPressed(BUTTON3))
  {
    seed.d = G_u32SystemTime1ms + 30686;
    UserApp1_pfStateMachine = BrainState;
    GameState.max_players = 5;
    GameState.player_start = seed.d % 5;  // will start the game off with a random player
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
  static int BS_prologue = 1;     // note prologue values need to be static in order to work properly 
  if (BS_prologue == 1) // should run at the beginning of each hand
  {
    UserApp1_pfStateMachine = GenerateCards;  // will populate the deck with cards
    GameState.player_turn = GameState.player_start;
    GameState.round = 0;

    BS_prologue = 2;
  }
  else if (BS_prologue == 2) // called at the beginning (aka. end) of each player's turn
  {
    // checks the game stuff, if everyone has folded, someone out of chips, gives rebuy option to lost player
    // if game ends BS_prologue = 3 and run end hand stuff
    // if everything checks out then:
    if (GameState.player_start == (GameState.player_turn + 1) % GameState.max_players)  // minus 1 since I changed increased the value of player_start by 1 at the beginning of the hand
    {
        GameState.round++;
    }
    if (GameState.round <= 4)
    {
      GameState.player_start = (GameState.player_start + 1) % GameState.max_players;
      UserApp1_pfStateMachine = PlayerTurn;
    }
    else
    {
      LedOn(WHITE);
      BS_prologue = 1;
    }
  }

  //epilogue:
    //  BS_prologue = 1
}




static void PlayerTurn(void)
{
  // prologue needs:  
                //  display "Player1's turn press a button" // so that other players don't see the Player1's cards
                //  round_start_seed(); // to assign the random values to the
  LedOn(ORANGE);
  static int PT_prologue = 1;
  if (PT_prologue == 1) //displays the player's turn
  {
    // maybe should check if folded here
    LcdMessage(LINE1_START_ADDR + 3, Player.player_name[GameState.player_turn]);  // will display the current player's turn ex. Player1's
    LcdMessage(LINE1_START_ADDR + 10, "'s Turn   ");
    LcdMessage(LINE1_START_ADDR, "   ");  // need to do the odd formating cuz when assigning values to the player_name
                                              //extra charecters get added to the tail for some reason, so we cover em up
    LcdMessage(LINE2_START_ADDR, "  Press Any Button  ");                           
    PT_prologue = 2;
  }

  else if (PT_prologue == 2)  // adds more randomness to the seeds, should be called for each person's turn
  {
    int temp1 = round_start_seed();  // returns 0 if no button press, else returns 1,2,3, or 4
    if (temp1 != 0)
    {
      LcdMessage(LINE1_START_ADDR, "                    ");
      LcdMessage(LINE2_START_ADDR, "                    ");
      LcdMessage(LINE1_START_ADDR, deck[Player.hand[2 * GameState.player_turn]]);      // 20 chars long, clears the dipslay
      LcdMessage(LINE1_START_ADDR + 3, deck[Player.hand[2 * GameState.player_turn + 1]]);
      LcdMessage(LINE1_START_ADDR + 5, ":");
    
      // current river display is just for testing
      LcdMessage(LINE1_START_ADDR + 6, "              ");
      if (GameState.round >= 2) // displays just the first 3 cards of the river
      {
        LcdMessage(LINE1_START_ADDR + 18, deck[GameState.river[0]]);
        LcdMessage(LINE1_START_ADDR + 15, deck[GameState.river[1]]);
        LcdMessage(LINE1_START_ADDR + 17, " "); // covers up some odd characters
        LcdMessage(LINE1_START_ADDR + 12, deck[GameState.river[2]]);
        LcdMessage(LINE1_START_ADDR + 14, " ");
      }
      if (GameState.round >= 3)
      {
        LcdMessage(LINE1_START_ADDR + 9, deck[GameState.river[3]]);
        LcdMessage(LINE1_START_ADDR + 11, " ");
      }
      if (GameState.round >= 4) // displays all 5 cards in the river
      {
        LcdMessage(LINE1_START_ADDR + 6, deck[GameState.river[4]]);
        LcdMessage(LINE1_START_ADDR + 8, " ");
      }
      LcdMessage(LINE2_START_ADDR, "Check Bet  Fold Info"); // info will be displayed
      if (Player.bet[GameState.player_turn] < GameState.highest_bet)
      {
        LcdMessage(LINE2_START_ADDR, "Call ");  // replaces "Check" option with "Call" option
      }
      PT_prologue = 3;
    }
  }

  else if (PT_prologue == 3)  // w8 for user input
  {
    int temp2 = round_start_seed(); // returns 0 if no button press, else returns 1,2,3, or 4
    if (temp2 == 1) //check the round
    {
      // user checks, need to check agaist current bet on the table
      UserApp1_pfStateMachine = BrainState; // testing
      GameState.player_turn = (GameState.player_turn + 1) % GameState.max_players;              // testing
      LedOff(ORANGE);// testing
      PT_prologue = 1;                         // testing
    }
    else if (temp2 == 2)
    {
      // goes to the Bet menu state
      UserApp1_pfStateMachine = Bet;
      LedOff(ORANGE);
      PT_prologue = 1;  // NEED TO FIND A FIX FOR THIS
    }
    else if (temp2 == 3)
    {
      // folds then checks if people still in the round
      UserApp1_pfStateMachine = BrainState; // testing
      GameState.player_turn = (GameState.player_turn + 1) % GameState.max_players;              // testing
      LedOff(ORANGE);// testing
      PT_prologue = 1;// testing
    }
    else if (temp2 == 4)
    {
      // goes to the Info menu state, just dipalys info about the other user's chips and current pot, folded or not
      UserApp1_pfStateMachine = BrainState; // testing
      GameState.player_turn = (GameState.player_turn + 1) % GameState.max_players;              // testing
      LedOff(ORANGE);// testing
      PT_prologue = 1;// testing
    }
    //PT_prologue = 4;
  }
  else if (PT_prologue == 4)
  {
    // w8 for user input
  }
  //eplilogue:
    // set river back to 0
    // set PT_prologue to back to 1 at end of round
}
//-----------------------------------------------------------------------------------------------------------------------





static void Bet(void)
{
  LedOn(BLUE);
  static int B_prologue = 1;
  if (B_prologue == 1)
  {
    Player.bet[GameState.player_turn] = GameState.highest_bet; // sets the bet to the call bet amount
    B_prologue = 2;
  }
  else if (B_prologue == 2)  // to be called after every button press of this state unless exiting this state
  {
    u8 currentChips[4];
    currentChips[0] = Player.chips[GameState.player_turn] % 10000 / 1000 + 48;  
    currentChips[1] = Player.chips[GameState.player_turn] % 1000 / 100 + 48;
    currentChips[2] = Player.chips[GameState.player_turn] % 100 / 10 + 48;
    currentChips[3] = Player.chips[GameState.player_turn] % 10 + 48;
    LcdMessage(LINE1_START_ADDR + 7, currentChips);
    LcdMessage(LINE1_START_ADDR, "Chips: ");
    LcdMessage(LINE1_START_ADDR + 11, " ");
    
    u8 currentBet[4];
    currentBet[0] = Player.bet[GameState.player_turn] % 10000 / 1000 + 48;  
    currentBet[1] = Player.bet[GameState.player_turn] % 1000 / 100 + 48;
    currentBet[2] = Player.bet[GameState.player_turn] % 100 / 10 + 48;
    currentBet[3] = Player.bet[GameState.player_turn] % 10 + 48;
    LcdMessage(LINE1_START_ADDR + 16, currentBet);
    LcdMessage(LINE1_START_ADDR + 12, "Bet: ");
    LcdMessage(LINE2_START_ADDR, "Up  Down  Enter Back");
    B_prologue = 3;
  }
  else if (B_prologue == 3)
  {
    int temp3 = round_start_seed(); // returns 0 if no button press, else returns 1,2,3, or 4 // could probalby just be temp not temp3
    if (temp3 == 1)
    {
      // bet Up
              // can't go above the player's max current chips
              // adds to Player.bet by 5 
      Player.bet[GameState.player_turn] = Player.bet[GameState.player_turn] + 5;
      if (Player.chips[GameState.player_turn] < Player.bet[GameState.player_turn])
      {
        // could create a display message to notify the user that they can't bet any more
        Player.bet[GameState.player_turn] = Player.bet[GameState.player_turn] - 5;
      }
      B_prologue = 2;
    }
    else if (temp3 == 2)
    {
      // down bet
            // can't go below the call highest_bet number aka. the amount the player has to at least match
            // subtracts from Player.bet by 5
      Player.bet[GameState.player_turn] = Player.bet[GameState.player_turn] - 5;
      if (GameState.highest_bet > Player.bet[GameState.player_turn])
      {
        // could create a display message to notify the user that they can't bet any more
        Player.bet[GameState.player_turn] = Player.bet[GameState.player_turn] + 5;
      }
      B_prologue = 2;
    }
    else if (temp3 == 3)
    {
      // enter and confirm the amount
              // needs to add the bet value to the pot 
              // exits the state and returns to BrainState
      GameState.highest_bet = Player.bet[GameState.player_turn];
      GameState.pot = GameState.pot + Player.bet[GameState.player_turn];
      Player.chips[GameState.player_turn] = Player.chips[GameState.player_turn] - Player.bet[GameState.player_turn];
      UserApp1_pfStateMachine = BrainState;
      B_prologue = 1;

    }
    else if (temp3 == 4)
    {
      // goes back to PlayerTurnState
      UserApp1_pfStateMachine = PlayerTurn;
      B_prologue = 1;
    }
  }


  LedOff(BLUE);
}



static void Info(void)        // state called by main menu and just displays some info
{
  LedOn(BLUE);
  int Info_substate = 1;
  if ()
}



static void GenerateCards(void) // state is done being coded
{
  static u8 drawn_from_deck[52];       
                        // cards avaible in the deck, will be reset at the last loop of generate cards
                        // 0/Null means card not used yet, 1 means card has already been delt this round
  LedOn(YELLOW);  //just to help indicate the current state
  LedOff(GREEN);
  // going to try and use a for loop, hopefully it doesn't put too much strain on the processor
      // can break up into a couple interations to help the processor manage
  
  GameState.river[0] = GeneratedNumber(&seed) % 52;
  
  for (int i = 0; i < 5;) // to generate the river, will only increment i if card not already drawn
  {
    GameState.river[i] = GeneratedNumber(&seed) % 52;
    if (drawn_from_deck[GameState.river[i]] != 1)
    {
      drawn_from_deck[GameState.river[i]] = 1;
      i++;
    }
  }
  for (int j = 0; j < (2 * GameState.max_players);) // generate the cards for the player's hands
  {
    Player.hand[j] = GeneratedNumber(&seed) % 52;
    if (drawn_from_deck[Player.hand[j]] != 1)
    {
      drawn_from_deck[Player.hand[j]] = 1;
      j++;
    }
  }
  for (int k = 0; k < 5; k++) // resets the drawn_from_deck back to all zeros
  {
    drawn_from_deck[GameState.river[k]] = 0;
  }
  for (int l = 0; l < (2 * GameState.max_players); l++)
  {
    drawn_from_deck[Player.hand[l]] = 0;
  }
  LedOff(YELLOW);
  UserApp1_pfStateMachine = BrainState;
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
int round_start_seed(void) // will adjust the seed value, happens at the beginning of each persons turn
{
  if (WasButtonPressed(BUTTON0))
  {
    seed.a = seed.a - G_u32SystemTime1ms;
    ButtonAcknowledge(BUTTON0);
    return 1;
  }
  else if (WasButtonPressed(BUTTON1))
  {
    seed.b = seed.b - G_u32SystemTime1ms;
    ButtonAcknowledge(BUTTON1);
    return 2;
  }
  else if (WasButtonPressed(BUTTON2))
  {
    seed.c = seed.c - G_u32SystemTime1ms;
    ButtonAcknowledge(BUTTON2);
    return 3;
  }
     
  else if (WasButtonPressed(BUTTON3))
  {
    seed.d = seed.d - G_u32SystemTime1ms;
    ButtonAcknowledge(BUTTON3);
    return 4;
  }
  else
  {
    return 0;
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

	state->counter += 3624; // not too sure about a good size for the counter value
	return t + state->counter;
}