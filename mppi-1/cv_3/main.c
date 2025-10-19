#include <msp430.h>

/*==============================================================================
    CLOCK CONFIGURATION OVERVIEW (MSP430 Basic Clock System+)

    ┌─────────────────────────────────────────────────────┐
    │   MCLK (Main Clock) Source Configurations           │
    ├────────┬───────────────────┬───────────┬────────────┤
    │ Step   │ Source (SELMx)    │ Divider   │ Frequency  │
    ├────────┼───────────────────┼───────────┼────────────┤
    │ 1      │ DCO               │ ÷1        │ ~1 MHz     │
    │ 2      │ DCO               │ ÷2        │ ~500 kHz   │
    │ 3      │ LFXT1 (Crystal)   │ ÷1        │ ~32.768 kHz│
    │ 4      │ VLO (Internal)    │ ÷1        │ ~12 kHz    │
    └────────┴───────────────────┴───────────┴────────────┘

    Registers used:
      - BCSCTL1 / DCOCTL : DCO calibration and control
      - BCSCTL2 : Clock source selection (SELMx) and dividers (DIVMx)
      - BCSCTL3 : Oscillator source select (LFXT1Sx)
      - IFG1, OFIFG : Oscillator fault flags
==============================================================================*/


short int i;

void blink(char n, unsigned int cycles);
void delay(unsigned int j);

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop the watchdog timer
    P1DIR |= 0x41;              // Set pins P1.0 and P1.6 as outputs
    P1OUT = 0x01;               // Set P1.0 = HIGH, P1.6 and others LOW

    // Calibration of the DCO oscillator to 1 MHz and enabling it
    BCSCTL1 = CALBC1_1MHZ;      // Load DCO calibration constant (1 MHz)
    DCOCTL  = CALDCO_1MHZ;      // Load DCO fine-tuning constant
    __bic_SR_register(SCG0);    // Enable the DCO (clear SCG0 bit)
                                // Intrinsic function - modifies the status register

    // Test startup of crystal-controlled oscillator LFXT1OSC
    __bic_SR_register(OSCOFF);  // Ensure LFXT1 is ON (for safety)
    do {
        IFG1 &= ~OFIFG;         // Clear oscillator fault flag
        __delay_cycles(50);     // Wait a short time
    } while (IFG1 & OFIFG);     // Wait until LFXT1 starts and stabilizes

    while (1) {

        // FIRST configuration: DCO -> MCLK
        BCSCTL3 &= ~(LFXT1S1 | LFXT1S0);  // Select LFXT1 instead of VLO
        BCSCTL2 &= ~(SELM1 | SELM0);      // Select DCOCLK as MCLK source (SELMx = 00)
        BCSCTL2 &= ~(DIVM1 | DIVM0);      // MCLK divider = 1:1 (no division)

        blink(5, 60000);   // Blink LEDs alternately
        delay(60000);      // Keep LED state steady for a moment
        delay(60000);

        // SECOND configuration: (DCO / 2) -> MCLK
        // Divide the main clock frequency by 2
        BCSCTL2 |= DIVM0;          // Set divider bit 0 = 1
        BCSCTL2 &= ~DIVM1;         // Clear divider bit 1 = 0 (DIVMx = 01 => divide by 2)

        // Blinking will now be slower because CPU frequency is halved
        blink(5, 30000);
        delay(30000);
        delay(30000);

        // THIRD configuration: LFXT1 -> MCLK
        __bic_SR_register(OSCOFF); // Ensure crystal oscillator is ON
        do {
            IFG1 &= ~OFIFG;
            __delay_cycles(50);    // Wait for crystal oscillator to stabilize
        } while (IFG1 & OFIFG);    // Wait until LFXT1 ready

        BCSCTL3 &= ~(LFXT1S1 | LFXT1S0); // Select LFXT1 oscillator
        BCSCTL2 |= (SELM1 | SELM0);      // Set SELMx = 11 → LFXT1CLK → MCLK
        BCSCTL2 &= ~(DIVM1 | DIVM0);     // MCLK divider 1:1

        blink(5, 1966);
        delay(1966);
        delay(1966);

        // FOURTH configuration: VLO -> MCLK
        // Set LFXT1Sx bits to 10 to use internal VLO as source
        BCSCTL3 |= LFXT1S1;
        BCSCTL3 &= ~LFXT1S0;

        blink(5, 720);
        delay(720);
        delay(720);

        P1OUT = 0x00;   // Turn OFF both LEDs
        delay(720);     // Short pause (to show that code reached this point)
        delay(720);

        P1OUT = 0x01;   // Turn ON green LED (P1.0)
    }
}

void blink(char n, unsigned int cycles)
{
    for (i = 0; i < n; i++) {
        delay(cycles);
        P1OUT ^= 0x41;

        delay(cycles);
        P1OUT ^= 0x41;
    }
}

void delay(unsigned int j)
{
    do {
        j--;
        asm(" nop");
    } while (j != 0);
}
