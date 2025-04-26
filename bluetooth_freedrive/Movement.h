// Movement.h
// Runs on TM4C123
// This header file contains all the movement functions for the car.
// Group 7
#include <stdint.h>
#include "tm4c123gh6pm.h"

#define DIRECTION (*((volatile unsigned long*)0x4002403C)) // Mask for PE0-3

// Directions for movement
#define FORWARD			0x0F  // 0000 1111 (4 bits active, both motors forward)
#define BACKWARD		0x0A  // 0000 1010 (2 bits active for direction, both motors backward)
#define PIVOT_R  		0x0B  // 0000 1110 (3 bits active, left forward, right backward)
#define PIVOT_L 		0x0E  // 0000 1011 (3 bits active, left backward, right forward)


// Global variables
extern volatile unsigned long CURRENT_SPEED_R;
extern volatile unsigned long CURRENT_SPEED_L;
/*
    The following movements are necessary for
    the car to move in the desired directions:
    - Figure Eight
    - Circle
    - Square
    - Zigzag
*/
// control PE0-3 for direction
void Direction_Init(void);

void speed_up(void);
void slow_down(void);

// Basic movement functions
void move_forward(void);
void move_backward(void);
void pivot_90_right(void);
void pivot_90_left(void);
void pivot_45_right(void);
void pivot_45_left(void);
void wide_right(void);
void wide_left(void);
void stop(void);

// Special movement functions
void figure_eight(void);
void circle(void);
void square(void);
void zigzag(void);

// Delay functions
void SysTick_Init(void);
void SysTick_Wait(uint32_t delay);
void Delay(uint32_t time_ms);
//void Delay(unsigned long milliseconds);
void Delay_half(void);
