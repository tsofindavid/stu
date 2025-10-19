;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file

;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer

;-------------------------------------------------------------------------------
; Quiz here
;-------------------------------------------------------------------------------

;1) LED diode D1 (green) is connected to pin P1.0
;   LED diode D2 (red) is connected to pin P1.6
;2) The green LED was blinking, the red one was off
;3) The directive .text points to address 0xC000
;   The directive .reset points to address 0xFFFE
;4) The program starts at address 0xC000
;5) When the value in the register reached zero and the instruction "xor.b   #001h,&P1OUT" was executed, LED D1 changed its state
;6) The LED D1 changes its state after each program run

;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------

SetupP1	bis.b   #001h,&P1DIR			; P1.0 nastaveny ako vystup

SetupP2	bis.b   #040h,&P1DIR			; P1.6 nastaveny ako vystup
		xor.b   #040h,&P1OUT

Mainloop	xor.b   #001h,&P1OUT			; softverovy prepinac P1.0
			xor.b   #040h,&P1OUT			; softverovy prepinac P1.6

Wait		mov.w   #65000,R15
L1			dec.w   R15
			jnz     L1

			mov.w   #65000,R15
L2     		dec.w   R15
			jnz     L2

			jmp     Mainloop		; ak R15 > 0, opakujeme cyklus


;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack

;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
