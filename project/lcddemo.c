#include <msp430.h>
#include "timerLib/libTimer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"

int main() //Runs all the essential method to run all the device's components 
{
  configureClocks();
  lcd_init();
  buzzer_init();
  led_init();
  switch_init();

  enableWDTInterrupts();
  or_sr(0x18);
}
