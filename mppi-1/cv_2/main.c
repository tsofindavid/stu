#include <msp430.h>

void onesk(unsigned int i);

void main(void) {
  WDTCTL = WDTPW + WDTHOLD; // Stop the watchdog timer
  P1DIR |= 0x41;            // Set pins P1.0 and P1.6 as output
  P1DIR &= 0xF7;            // Set pin P1.3 as input

  unsigned int j = 0;
  for (;;) {
    P1OUT = 0x00;

    while (P1IN & BIT3)
      P1OUT = 0x40; // turn on red LED, if green is on it turns off
    onesk(1000);    // next test runs only after 4ms

    while (~P1IN & BIT3)
      onesk(1000);

    while (P1IN & BIT3)
      P1OUT = 0x01; // red LED off, green LED on
    onesk(1000);

    while (~P1IN & BIT3)
      onesk(1000);

    while (P1IN & BIT3)
      ;
    onesk(1000);

    while (~P1IN & BIT3)
      ;
    P1OUT = 0x00; // both LEDs off

    while (P1IN & BIT3)
      ;

    for (j = 0; j < 5; j++) {
      P1OUT = 0x01;
      onesk(50000);

      P1OUT = 0x40;
      onesk(50000);
    }
    while (~P1IN & BIT3)
      ;
    onesk(1000);
  }

  while (P1IN & BIT3)
    ;
  P1OUT = 0x40;
  onesk(1000);
  while (~P1IN & BIT3)
    ;
  onesk(1000);
}

void onesk(unsigned int i) {
  do {
    i--;
    asm(" nop");
  } while (i != 0);
}
