#include <msp430.h>
#include "led.h"
#include "switches.h"

unsigned char red_led_state = 0, green_led_state = 0;
unsigned char leds_changed = 0;

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
}

void led_update(int red_state, int green_state){
  char ledFlags = 0; 

  ledFlags |= green_state ? LED_GREEN : 0;
  ledFlags |= red_state ? LED_RED : 0;

  P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
  P1OUT |= ledFlags;         // set bits for on leds

}