/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */
#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"


/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  buzzer_init();
  led_init();
  switch_init();
  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);

  enableWDTInterrupts();
  or_sr(0x18);
}
