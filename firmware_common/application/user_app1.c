/*Random Number Generator branch


/*!*********************************************************************************************************************
@file user_app1.c                                                                
@brief User's tasks / applications are written here.  This description
@ -77,23 +80,18 @@ Function Definitions

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserApp1Initialize(void)

@brief
Initializes the State Machine and its variables.

Should only be called once in main init section.
*/
//Put global veribals here
u32 u32TimePressFirst = 0; //Stores the
u32 u32numPressSecond = 0;

void UserApp1Initialize(void)
{
  
/* All discrete LEDs to off */
  //Turns the LEDs off just in case they were on for some reason
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(ORANGE);
  LedOff(RED);
  
  /*make a wave like feture on the board */
  
  if( 1 )
  {
    UserApp1_pfStateMachine = StartUp;//first state that is run
  }
  else
  {

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



/**********************************************************************************************************************
State Machine Function Definitions
Write the functions starting here put in order of operating
**********************************************************************************************************************/
/*-------------------------------------------------------------------------------------------------------------------*/
/* What does this state do? */

static void StartUp(void) //start up
{
  static u16 u16WaveHeight = 0;
  
  if (G_u32SystemTime1ms % 80 == 0)//change num this to change rate of wave

  LedOn(ORANGE); //Just for testing
  LCDMessage(LINE1_START_ADDR, "Press a Button to start");
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
    TimePressFirst = G_u32SystemTime1ms + 500;
    UserApp1_pfStateMachine = ChooseGame;
    ButtonAcknowledge(BUTTON2);
  }
} /* end UserApp1SM_Idle() */
     
  else if (WasButtonPressed(BUTTON3))
  {
    TimePressFirst = G_u32SystemTime1ms + 750;
    UserApp1_pfStateMachine = ChooseGame;
    ButtonAcknowledge(BUTTON3);
  }
}


static void ChooseGame(void)
{
  LCDMessage(LINE1_START_ADDR, "Select a Game");
  LCDMessage(LINE2_START_ADDR, "0");
  LCDMessage(LINE2_START_ADDR + 6, "1");
  LCDMessage(LINE2_START_ADDR + 13, "2");
  LCDMessage(LINE2_END_ADDR, "3");
  LedOn(GREEN);
  if (WasButtonPressed(BUTTON0))
  {
    TimePressFirst *= (G_u32SystemTime1ms % 100);
    UserApp1_pfStateMachine = Game1;
    ButtonAcknowledge(BUTTON0);
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
  LCDMessage(LINE1_START_ADDR, "Game1   ");
}

static void Game2(void)
{
  LCDMessage(LINE1_START_ADDR, "Game2   ");
}

static void Game3(void)
{
  LCDMessage(LINE1_START_ADDR, "Game3   ");
}
static void Game4(void)
{
  LCDMessage(LINE1_START_ADDR, "Game4   ");
}
/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */




/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/