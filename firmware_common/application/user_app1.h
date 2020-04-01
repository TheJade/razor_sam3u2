/*!*********************************************************************************************************************
@file user_app1.h                                                                
@brief Header file for user_app1

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
1. Follow the instructions at the top of user_app1.c
2. Use ctrl-h to find and replace all instances of "user_app1" with "yournewtaskname"
3. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
4. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
5. Add #include yournewtaskname.h" to configuration.h
6. Add/update any special configurations required in configuration.h (e.g. peripheral assignment and setup values)
7. Delete this text (between the dashed lines)
----------------------------------------------------------------------------------------------------------------------

**********************************************************************************************************************/

#ifndef __USER_APP1_H
#define __USER_APP1_H

/**********************************************************************************************************************
Structure Definitions
**********************************************************************************************************************/
static struct xorwow_state{  //stores the values for the Random Number Generator
  u32 a, b, c, d;               // needs to be static or causes many errors
  u32 counter;
}seed;

struct Character{ // 
  //could reduce the number of variables but for easy of read, I will keep many variabels for now
  int chips[5];  //one index for each player
  int hand[10];  //2 indexes for each player 0 and 1 get assined to player1
  int fold[5];  // is 1 if the player hasn't folded, is 0 if the player has folded
  int bet[5];   // the current bet of the player
  u8 *player_name[5];   // will store all an array of all the player's names (obviously)
};    // index of an array of values signifies each player's stuff
                //aka. index 0 and 1 for hands is for player 1, index 2 and 3 are for player 2

static struct GameState{    // needs to be static or causes many errors
  u8 max_players; //number of player in the game should be setable
  int round;  // the amount of the river to display on a player's turn, will change at the end of each round
  int player_start; // describes the player to start the betting of the round, may not need this value
  int player_turn; // who's turn the game is currently on        // = 0 means player1's turn
  int river[5];  //holds the cards in the river, will always be size of 5
  int pot;      // I'm pretty sure it needs to be an int
  int highest_bet;  // is the value of the highest bet so far in the round
}GameState;

/**********************************************************************************************************************
Function Declarations
**********************************************************************************************************************/
int round_start_seed(void);
u32 GeneratedNumber(struct xorwow_state *state);

/*------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/
void UserApp1Initialize(void);
void UserApp1RunActiveState(void);


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
State Machine Declarations
***********************************************************************************************************************/
static void UserApp1SM_Idle(void);    
static void UserApp1SM_Error(void);  
static void StartUp(void);  // includes num of player select       
static void BrainState(void);   // important state will go through this state a lot // called from Startup, calls Playerturn
static void GenerateCards(void);    // will populate the GameState structure
static void PlayerTurn(void);   // can go straight back to BrainState or call Bet
static void Bet(void);  // is called from PlayerTurn can go back to PlayerTurn or straight to BrainState
static void Info(void); // displays info about the game, like players still in, pot, number of chips etc.


/**********************************************************************************************************************
Constants / Definitions
**********************************************************************************************************************/

static u8 *deck[] = { // it is global   // index will be called and displayed, acts like a dictionary
            "2D", //index is 0
            "3D",
            "4D", //called by u8 *CardDisplay = deck[2];
            "5D",         //then LcdMessage(LINE2_START_ADDR, deck[index_to_display]);
            "6D",
            "7D",
            "8D",
            "9D",
            "0D",       // 8 (10 of diamonds)
            "JD",
            "QD",
            "KD",
            "AD",
            
            "2C",       // index 13
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
            
            "2S",       // 26
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
            "KS",       // 37
            "AS",       // 38
            
            "2H",       // 39
            "3H",       // 40
            "4H",       // 41
            "5H",       // 42
            "6H",       // 43
            "7H",
            "8H",       // 45
            "9H",
            "0H", //10 of hearts
            "JH",
            "QH",
            "KH",       // 50
            "AH"        // 51
      };

#endif /* __USER_APP1_H */

/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
