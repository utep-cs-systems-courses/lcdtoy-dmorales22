#include <msp430.h>
#include "timerLib/libTimer.h"
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "p1_interrupt_handler.h"
#include "lcdutils.h"
#include "lcddraw.h"

static enum {START, STATE1, STATE2, STATE3, STATE4} current_state = START;

void state_menu()
{

  if(B_SW1_switch_state_down){
    current_state = START;
  }

  if(SW1_switch_state_down) { //If switch 1 on the board is pressed then it changes state to STATE1. 
    current_state = STATE1;
  }

  if(SW2_switch_state_down) { //If switch 2 on the board is pressed then it changes state to STATE2. 
    current_state = STATE2;
  }
  
  if(SW3_switch_state_down) { //If switch 3 on the board is pressed then it changes state to STATE3. 
    current_state = STATE3;
  }

  if(SW4_switch_state_down) { //If switch 4 on the board, then the CPU is off. The CPU turns back on when the button is no longer being pressed.
    or_sr(0x8);	              //< GIE (enable interrupts) 
    while(SW4_switch_state_down) {
      or_sr(0x10);	      //< CPU OFF 
    }
    or_sr(0x18); //CPU on
  }
}
void flasher_light()		//Uses switch cases to alternate green and red.
{
  static char state = 0;

  switch (state) {
  case 0:
    led_update(1,0); 
    state = 1;
    break;
  case 1:
    led_update(0,1);
    state = 0;
    break;
  }
}

void state_advance()		/* changes the devices functions with states using switch cases*/
{  
  blink_max = 50; 
  switch (current_state) {
  case START: //START state has no lights on and buzzer is silent(to reduce headaches).
    led_update(0,0);
    buzzer_set_period(0);

    u_char width = screenWidth, height = screenHeight;
    clearScreen(COLOR_BLUE);
    drawString8x12(30,100, "hello", COLOR_GREEN, COLOR_RED); //Prints hello world in 8x12 font.
    drawString8x12(30, 80, "world", COLOR_GREEN, COLOR_RED);
    drawString8x12(30, 60, "uwu", COLOR_GREEN, COLOR_RED);

    state_menu(); //Every case will run the state_menu so you can change states.
    break;

  case STATE1: //STATE1 sets buzzer to a frequency and red light on.
    blink_max = 35; //Changes speed of rectangle rendering.
    led_update(0,1); //Only red light on
    buzzer_set_period(2000);
    clearScreen(COLOR_GREEN); //Clears screen, make screen green. 
    drawRect(50,100,COLOR_BLUE, 30, 20); //Renders a rectangle
    drawRect(40,80,COLOR_RED,20, 10);
    state_menu();
    break;

  case STATE2: //STATE2 sets buzzer to a frequency and green light on, just clears screen red.
    clearScreen(COLOR_RED); 
    led_update(1,0);
    buzzer_set_period(1000);
    state_menu();
    break;

  case STATE3:
    blink_max = 30; //Sets the blink_max value for blinking lights, and changes rendering speed. 
    buzzer_set_period(500);
    flasher_light(); //Runs method to allow for blinking lights

    clearScreen(COLOR_BLUE);
    drawShape1(40,70,COLOR_RED); //Renders custom shape.
    drawShape1(20,70,COLOR_GREEN);
    drawShape1(10,70,COLOR_YELLOW);
    drawShape1(5,70,COLOR_WHITE);
    state_menu();
    break;
  }
}