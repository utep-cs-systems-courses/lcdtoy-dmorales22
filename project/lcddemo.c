#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"

int main()
{
  configureClocks();
  lcd_init();
  buzzer_init();
  led_init();
  switch_init();

  enableWDTInterrupts();
  or_sr(0x18);
}
