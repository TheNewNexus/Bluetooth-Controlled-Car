// CECS 447: Project 3 - A Bluetooth Controlled Robot Car
// BltControlledCar.c
// Purpose:	This file contains the main function for the car to move in different patterns.
// Group: Robby Rimal, Jonathan Cerniaz, Joseph Guzman, Afzal Hakim
// Runs on TM4C123
// Moves using PWM to control the speed of the motors and the direction of the car.
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

#define START_SPEED 8000

bool isMode1 = true;
bool isMode2 = false;
unsigned char control_symbol;

void mode1(void);

int main(void)
{
	SysTick_Init();
	BLT_Init();						 // Initialize Bluetooth module
	Direction_Init();				 // MOTOR Init
	LED_Init();						 // Initilize for the three onboard LED
	PWM_Init();
	PWM_Duty(START_SPEED, START_SPEED);
	LED = DARK;
	while (1)
	{
		while (isMode1)
		{
			mode1();
		}
	}
}

void mode1(void)
{
	// set Green LED for mode1
	LED = GREEN;
	
	char control_symbol = BLT_InChar(); // Read command from Bluetooth
	
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
