// CECS 447: Project  - Bluetooth Controlled Car
// File Name: LED.c
// Purpose: Initializes Port F, sets up PF4 as inputs for switch 1 with interrupts, and PF1-3 as outputs for LEDs.
// Group: Robby Rimal 
// 				Jonathan Cerniaz 
// 				Joseph Guzman
// 				Afzal Hakim
// Last Modified: 9/16/2024

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "LED.h"

//Initialization for Onboard LEDs (PF3-1) and SW1 (PF4)
void LEDSW_Init(void) {
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;        // (a) Activate clock for Port F
    while ((SYSCTL_RCGC2_R & SYSCTL_RCGC2_GPIOF) == 0) {} // Wait for clock to be ready

    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;           // Unlock PortF PF0 (if needed, but not used here)
    GPIO_PORTF_CR_R |= 0x1E;                     // Allow changes to PF4-1
    GPIO_PORTF_DIR_R |= 0x0E;                    // (b) Configure PF3-1 as outputs (LEDs)
    GPIO_PORTF_DIR_R &= ~0x10;                   // Configure PF4 as input (SW1)
    GPIO_PORTF_AFSEL_R &= ~0x1E;                 // Disable alternate function on PF4-1
    GPIO_PORTF_DEN_R |= 0x1E;                    // Enable digital I/O on PF4-1
    GPIO_PORTF_PCTL_R &= ~0x000FFFF0;            // Configure PF4-1 as GPIO
    GPIO_PORTF_AMSEL_R &= ~0x1E;                 // Disable analog functionality on PF4-1
    GPIO_PORTF_PUR_R |= 0x10;                    // Enable weak pull-up on PF4 (SW1)

    GPIO_PORTF_IS_R &= ~0x10;                    // (c) Configure PF4 for edge-sensitive interrupts
    GPIO_PORTF_IBE_R &= ~0x10;                   // PF4 is not both edges triggered
    GPIO_PORTF_IEV_R |= 0x10;                    // PF4 interrupt on rising edge event
    GPIO_PORTF_ICR_R = 0x10;                     // (d) Clear interrupt flags for PF4
    GPIO_PORTF_IM_R |= 0x10;                     // (e) Arm interrupt on PF4

		NVIC_PRI7_R = (NVIC_PRI7_R & ~0x00E00000) | 0x00200000; // Set interrupt priority 1 for Port F
    //NVIC_PRI7_R = (NVIC_PRI7_R&0xFF1FFFFF)|0x00200000; // (g) bits:23-21 for PORTF, set priority to 1
    NVIC_EN0_R |= NVIC_EN0_PORTF;                // (g) Enable interrupt 30 in NVIC (Port F)
}

