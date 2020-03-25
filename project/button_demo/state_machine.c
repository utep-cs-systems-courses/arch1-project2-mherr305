#include <msp430.h>
#include "state_machine.h"
#include "led.h"

static enum {off=0, dim=1,bright=2} ledConf;
static char count =0;

void slow_count(){
  ledConf = (ledConf+1)%3;
}

void fast_count(){
  count = (count+1)&3;
}

void state_update_led(){
  char new_red_on,new_green_on;
  switch(ledConf){
  case off:
    new_red_on =0;
    new_green_on=1;
    break;
  case bright:
    new_red_on =1;
    new_green_on=0;
    break;
  case dim:
    new_red_on = (count<1);
    new_green_on= (count<1);
    break;
  }
  if(red_on != new_red_on){
    red_on=new_red_on;
    led_changed=1;
  }
  if(green_on != new_green_on){
    green_on=new_green_on;
    led_changed=1;
 }
  led_update();
}
