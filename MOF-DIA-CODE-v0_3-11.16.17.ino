/*
         Dial-Up
      Møffenzeef Mødular
        Røss Fish 2017
  http://moffenzeefmodular.com
         CC-BY-NC-SA

  Based on "Audio Sample Player"
      By: David Johnson-Davies
  http://www.technoblogy.com/show?QBB
          CC BY 4.0
*/

#include <avr/pgmspace.h>

unsigned int Acc[] {0, 0, 0, 0};
unsigned int Note = 0;
unsigned int Note1 = 0;
unsigned int Note2 = 0;
unsigned int Note3 = 0;

int potRaw = 0;
int pitch = 0;
int modulate = 0;
int modulator = 0;
int countCrapula = 0;

void setup() {
  // Enable 64 MHz PLL and use as source for Timer1
  PLLCSR = 1 << PCKE | 1 << PLLE;

  // Set up Timer/Counter1 for PWM output
  TIMSK = 0;                              // Timer interrupts OFF
  TCCR1 = 1 << PWM1A | 2 << COM1A0 | 1 << CS10; // PWM A, clear on match, 1:1 prescale

  // Set up Timer/Counter0 for 8kHz interrupt to output samples.
  TCCR0A = 3 << WGM00;                    // Fast PWM
  TCCR0B = 1 << WGM02 | 2 << CS00;        // 1/8 prescale
  TIMSK = 1 << OCIE0A;                    // Enable compare match

  pinMode(1, OUTPUT);
  analogReference(DEFAULT); 
}

void loop() {
  potRaw = analogRead(A3);
  Note =  map(potRaw, 0, 1023, 1, 32);
  Note1 = map(potRaw, 0, 1023, 1, 32); 
  Note2 = map(potRaw, 0, 1023, 1, 32);  
  OCR0A = map(potRaw, 0, 1015, 80, 20);
  }

// Sample interrupt
ISR(TIMER0_COMPA_vect) {
  Acc[0] = Acc[0] + Note;
  Acc[1] = Acc[1] + Note1;
  Acc[2] = Acc[2] + Note2;
  OCR1A = (Acc[0] * Acc [1]) ^ Acc[2] >> 8 & 0x80; //
}
