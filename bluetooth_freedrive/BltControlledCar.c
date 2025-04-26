// CECS 447: Project 3 - A Bluetooth Controlled Robot Car
// BltControlledCar.c
// Purpose:	This file contains the main function for the car to move in different patterns.
// Group: Robby Rimal, Jonathan Cerniaz, Joseph Guzman, Afzal Hakim
// U1Rx (PB0)
// U1Tx (PB1)
#include "tm4c123gh6pm.h"
#include "PWM.h"
#include "stdbool.h"
#include "LED.h"
#include "BLT.h"
#include "Movement.h"

// Define LEDs
#define DARK 0x00
#define RED 0x02
#define BLUE 0x04
#define GREEN 0x08

#define START_SPEED 5500

bool isMode1 = true;
bool isMode2 = false;
unsigned char control_symbol;

extern void EnableInterrupts(void);
extern void WaitForInterrupt(void);
extern void DisableInterrupts(void);

void mode1(void);
void mode2(void);

int main(void)
{
	DisableInterrupts();
	SysTick_Init();
	BLT_Init();		  // Initialize Bluetooth module
	Direction_Init(); // MOTOR Init
	LEDSW_Init();	  // Initilize for the three onboard LED
	PWM_Init();
	PWM_Duty(START_SPEED, START_SPEED); // initialize to normal speed

	// starting with mode1
	LED = GREEN;
	EnableInterrupts();

	while (1)
	{
		control_symbol = BLT_InChar(); // Read command from Bluetooth
		UART0_OutChar(control_symbol);
		UART0_OutChar(CR);
		UART0_OutChar(LF);

		if (isMode1)
		{
			mode1();
		}
		else if (isMode2)
		{
			mode2();
		}
	}
}

// Mode 1
// Control the car to move in different patterns
void mode1(void)
{
	switch (control_symbol)
	{
	case '8':
		figure_eight();
		break;

	case 'c' | 'C':
		circle();
		break;

	case 's' | 'S':
		square();
		break;

	case 'z' | 'Z':
		zigzag();
		break;

	default:
		break;
	}
}

// mode 2
// Free drive mode
// Control the car to move forward, backward, left, right, stop, speed up, and slow down
void mode2(void)
{
	switch (control_symbol)
	{
	case 'F' | 'f':
		move_forward();
		break;

	case 'B' | 'b':
		move_backward();
		break;

	case 'L' | 'l':
		wide_left();
		break;

	case 'R' | 'r':
		wide_right();
		break;

	case 'S' | 's':
		stop();
		break;

	case 'U' | 'u':
		speed_up();
		break;

	case 'D' | 'd':
		slow_down();
		break;

	default:
		break;
	}
}

// Switch 1 interrupt handler
// Switch between mode1 and mode2
void GPIOPortF_Handler(void)
{
	Delay(20);				 // 20ms debounce
	GPIO_PORTF_ICR_R |= SW1; // Clear interrupt flag
	if (isMode1)
	{
		isMode1 = false;
		isMode2 = true;
		LED = BLUE;
	}
	else
	{
		isMode1 = true;
		LED = GREEN;
		isMode2 = false;
		
	}
}
