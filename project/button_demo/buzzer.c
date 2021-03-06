#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "switches.h"
#include "frequency_note.h"

void buzzer_init(){
  timerAUpmode();              /* used to drive speaker*/
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;                /*enable output to speaker(P2.6)*/
}

void buzzer_set_period(short cycles){ /*buzzer clock = 2MHz. */
  CCR0 = cycles;
  CCR1 = cycles >> 1;           /*one half cycle */
}

void play_intro(){
  int intro[] = {C4,C4,C4,C4,D4,D4,D4,D4,E4,E4,E4,E4};
    for(int i=0; i<12; i++){
      buzzer_set_period(intro[i]);
  __delay_cycles(16000000/8);
    }
  buzzer_set_period(0);
}

void play_verse(){
  int verse[] = {F4,F4,F4,F4,G4,G4,G4,G4,A4,A4,A4,A4,C4,C4,C4,C4};
    for(int i=0; i<16; i++){
      buzzer_set_period(verse[i]);
      __delay_cycles(16000000/8);
    }
  buzzer_set_period(0);
}

void play_bridge(){
  int bridge[] = {Bb4,Bb4,Bb4,Bb4,C4,C4,C4,C4,D4,D4,D4,D4};
    for(int i=0; i<12; i++){
      buzzer_set_period(bridge[i]);
      __delay_cycles(16000000/8);
    }
  buzzer_set_period(0);
}
