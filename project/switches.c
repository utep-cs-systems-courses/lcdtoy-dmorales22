#include <msp430.h>
#include "switches.h"
#include "led.h"

char B_SW1_switch_state_down;
char SW1_switch_state_down;
char SW2_switch_state_down;
char SW3_switch_state_down;
char SW4_switch_state_down;

char B_SW1_switch_state_changed;
char SW1_switch_state_changed;
char SW2_switch_state_changed;
char SW3_switch_state_changed;
char SW4_switch_state_changed;

static char 
switch_update_interrupt_sense_top()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

static char
switch_update_interrupt_sense_bottom()
{
  char p1val = P1IN;
  /* update switch interrupt to detect changes from current buttons */
  P1IES |= (p1val & B_SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~B_SWITCHES);	/* if switch down, sense up */
  return p1val;
}
void 
switch_init()			/* setup switch */
{  
  P1REN |= B_SWITCHES;		/* enables resistors for switches */
  P1IE = B_SWITCHES;		/* enable interrupts from switches */
  P1OUT |= B_SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~B_SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense_bottom();
  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE = SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense_top();
  
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense_top();
  SW1_switch_state_down = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  SW2_switch_state_down = (p2val & SW2) ? 0 : 1; /* 0 when SW2 is up */
  SW3_switch_state_down = (p2val & SW3) ? 0 : 1; /* 0 when SW3 is up */
  SW4_switch_state_down = (p2val & SW4) ? 0 : 1; /* 0 when SW4 is up */
  
  SW1_switch_state_changed = SW1 ? 1: 1;
  SW2_switch_state_changed = SW2 ? 1: 1;
  SW3_switch_state_changed = SW3 ? 1: 1;
  SW4_switch_state_changed = SW4 ? 1: 1;
  
  char p1val = switch_update_interrupt_sense_bottom();
  B_SW1_switch_state_down = (p1val & B_SW1) ? 0 : 1; /* 0 when SW1 is up */
  B_SW1_switch_state_changed = B_SW1 ? 1: 1;
  
}