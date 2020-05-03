#include <msp430.h>
#include "switches.h"
#include "stateMachines.h" 

char blink_max;
/* Switch on P1 (S2) */

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & B_SWITCHES) {	      /* did a button cause this interrupt? */
    P1IFG &= ~B_SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if (++blink_count == blink_max) {
    state_advance();
    blink_count = 0;
  }
}
