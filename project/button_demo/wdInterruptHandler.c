#include <msp430.h>
#include "state_machine.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"
#include "frequency_note.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){   /*250 interrupts/sec */
  static char blink_count = 0;
  if(++blink_count ==125){
     fast_count();
    blink_count =0;
  }
   fast_count();
   state_update_led();
  led_update();
}


