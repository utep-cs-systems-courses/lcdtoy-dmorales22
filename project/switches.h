#ifndef switches_included
#define switches_included

#define B_SW1 BIT3
#define B_SWITCHES B_SW1

#define SW1 BIT0 /* p2.0 */
#define SW2 BIT1 /* p2.1 */
#define SW3 BIT2 /* p2.2 */
#define SW4 BIT3 /* p2.3 */
#define SWITCHES (SW1 | SW2 | SW3 | SW4)

void switch_init();
void switch_interrupt_handler();

extern char B_SW1_switch_state_down; 
extern char SW1_switch_state_down; /* effectively boolean */
extern char SW2_switch_state_down;
extern char SW3_switch_state_down;
extern char SW4_switch_state_down;

extern char B_SW1_switch_state_changed; 
extern char SW1_switch_state_changed; /* effectively boolean */
extern char SW2_switch_state_changed;
extern char SW3_switch_state_changed;
extern char SW4_switch_state_changed;
#endif // included