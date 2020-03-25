#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "state_machine.h"
#include "buzzer.h"
#include "frequency_note.h"

char switch_state_down1,switch_state_down2,switch_state_down3,switch_state_down4;
char switch_state_changed;

static char
switch_update_interrupt_sense(){
  char p2val = P2IN;

  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void
switch_init(){
  P2REN |= SWITCHES;
  P2IE = SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  led_update();
}

void switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();
  switch_state_down1 = (p2val & SW1) ? 0 : 1;
  switch_state_down2 = (p2val & SW2) ? 0 : 1;
  switch_state_down3 = (p2val & SW3) ? 0 : 1;
  switch_state_down4 = (p2val & SW4) ? 0 : 1;
  switch_state_changed = 1;

  if(switch_state_down1){
    play_intro();
  }
  if(switch_state_down2){
    play_verse();
  }
  if(switch_state_down3){
    play_bridge();
  }
  if(switch_state_down4){
    slow_count();
    state_update_led();
  }
  led_update();
}

