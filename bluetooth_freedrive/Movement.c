#include "Movement.h"
#include "tm4c123gh6pm.h"
#include "PWM.h"

#define FAST 8500
#define NORMAL 5500 // About 0.5 Meters/sec
#define SLOW 2500
#define STOP 1

#define SYSCLK 16000000               // 16 MHz system clock
#define ONE_MS_RELOAD (SYSCLK / 1000) // Reload value for 1 millisecond

// Define global variables
volatile unsigned long CURRENT_SPEED_R = NORMAL;
volatile unsigned long CURRENT_SPEED_L = NORMAL;

// Subroutine to initialize port E pins PE0-3 for output
// PE0-3 control direction of motor
// Inputs: None
// Outputs: None
void Direction_Init(void)
{
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE; // activate E clock
    while ((SYSCTL_RCGC2_R & SYSCTL_RCGC2_GPIOE) != SYSCTL_RCGC2_GPIOE)
    {
    } // wait for clk

    GPIO_PORTE_AMSEL_R &= ~0x0F;      // disable analog function
    GPIO_PORTE_PCTL_R &= ~0x0000FFFF; // GPIO clear bit PCTL
    GPIO_PORTE_DIR_R |= 0x0F;         // PE0-3 output
    GPIO_PORTE_AFSEL_R &= ~0x0F;      // no alternate function
    GPIO_PORTE_DEN_R |= 0x0F;         // enable digital pins PE0-3
}

// Car moves forward
void move_forward(void)
{
    DIRECTION = FORWARD;
    PWM_Duty(CURRENT_SPEED_L, CURRENT_SPEED_R);
    PWM0_ENABLE_R |= 0x00000003; // enable both wheels
}

// Car moves backward
void move_backward(void)
{
    DIRECTION = BACKWARD;
    PWM_Duty(CURRENT_SPEED_L, CURRENT_SPEED_R);
    PWM0_ENABLE_R |= 0x00000003; // enable both wheels
}

// Car speeds up
void speed_up(void)
{
    if (CURRENT_SPEED_L == SLOW && CURRENT_SPEED_L == CURRENT_SPEED_R)
    {
        CURRENT_SPEED_L = NORMAL;
        CURRENT_SPEED_R = NORMAL;
			PWM_Duty(CURRENT_SPEED_L, CURRENT_SPEED_R);
    }
    else if (CURRENT_SPEED_L == NORMAL && CURRENT_SPEED_L == CURRENT_SPEED_R)
    {
        CURRENT_SPEED_L = FAST;
        CURRENT_SPEED_R = FAST;
			PWM_Duty(CURRENT_SPEED_L, CURRENT_SPEED_R);
    }
		
    
}

// Car slows down
void slow_down(void)
{
    if (CURRENT_SPEED_L == FAST && CURRENT_SPEED_L == CURRENT_SPEED_R)
    {
        CURRENT_SPEED_L = NORMAL;
        CURRENT_SPEED_R = NORMAL;
			PWM_Duty(CURRENT_SPEED_L, CURRENT_SPEED_R);
    }
    else if (CURRENT_SPEED_L == NORMAL && CURRENT_SPEED_L == CURRENT_SPEED_R)
    {
        CURRENT_SPEED_L = SLOW;
        CURRENT_SPEED_R = SLOW;
			PWM_Duty(CURRENT_SPEED_L, CURRENT_SPEED_R);
    }
    
}

// Car stops
void stop(void)
{
    PWM_Duty(STOP, STOP);
    PWM0_ENABLE_R &= ~0x00000003; // stop both wheels
    Delay(100);
}

void pivot_90_right(void)
{
    DIRECTION = PIVOT_R;
    PWM_Duty(NORMAL, NORMAL);
    PWM0_ENABLE_R |= 0x00000003; // enable both wheels
    Delay(300);                  // Adjust the delay duration
}

void pivot_90_left(void)
{
    DIRECTION = PIVOT_L;
    PWM_Duty(NORMAL, NORMAL);
    PWM0_ENABLE_R |= 0x00000003; // enable both wheels
    Delay(300);                  // Adjust the delay duration
}

void pivot_45_right(void)
{
    DIRECTION = PIVOT_R;
    PWM_Duty(NORMAL, NORMAL);
    PWM0_ENABLE_R |= 0x00000003; // enable both wheels
    Delay(175);                  // Adjust the delay duration
}

void pivot_45_left(void)
{
    DIRECTION = PIVOT_L;
    PWM_Duty(NORMAL, NORMAL);
    PWM0_ENABLE_R |= 0x00000003; // enable both wheels
    Delay(175);                  // Adjust the delay duration
}

// Car pivots wide to the right
void wide_right(void)
{
    PWM0_ENABLE_R |= 0x00000003; // enable both wheels
		PWM_Duty(FAST, NORMAL);
}

// Car pivots wide to the left
void wide_left(void)
{		
    PWM0_ENABLE_R |= 0x00000003; // enable both wheels
		PWM_Duty(NORMAL, FAST);
}

void figure_eight(void)
{
    // Start with a 90-degree pivot right to begin the first loop
    pivot_90_right();
    stop();

    // Wide left turn for the first loop
		DIRECTION = FORWARD;
    wide_left();
		
    Delay(3800);
    stop();

    // Small pivot right to bring the car back to center
    pivot_45_left();
    stop();

    // Wide right turn for the second loop
		DIRECTION = FORWARD;
    wide_right();
    Delay(3800);

    // Pivot left to finish the figure 8
    pivot_45_left();
    stop();
}

void circle(void)
{
		
    pivot_90_right();
    stop();

    // wide left turn to create a circular motion
		DIRECTION = FORWARD;
    wide_left();
    Delay(3800);
    pivot_90_left();
    stop();
}

void square(void)
{
    for (int i = 0; i < 4; i++)
    {
        move_forward();
        Delay(1000);
        stop();

        pivot_90_right();
        stop();
    }
    stop();
}

void zigzag(void)
{
    for (int i = 0; i < 2; i++)
    {

        // zig
        pivot_45_right();
        stop();
        move_forward();
        Delay(750); // Forward Duration
        stop();

        // zag
        pivot_90_left();
        Delay(85);
        stop();
        move_forward();
        Delay(750);
        stop();

        pivot_45_right();
        Delay(50);
    }
    // zig
    pivot_45_right();
    Delay(50);
    stop();
    move_forward();
    Delay(750); // Forward Duration
    pivot_45_left();
    stop();
}

void SysTick_Init(void)
{
    // Disable SysTick during setup
    NVIC_ST_CTRL_R = 0;
    // Set the reload register to its maximum value
    NVIC_ST_RELOAD_R = ONE_MS_RELOAD - 1; // For 1ms delay
    // Reset the current value register
    NVIC_ST_CURRENT_R = 0;
    // Enable SysTick with core clock
    NVIC_ST_CTRL_R = 0x05; // Enable SysTick with system clock, no interrupts
}

void SysTick_Wait(uint32_t delay)
{
    // Wait for the delay in milliseconds
    while (delay > 0)
    {
        // Load the reload value for 1ms
        NVIC_ST_RELOAD_R = ONE_MS_RELOAD - 1;
        // Clear the current register
        NVIC_ST_CURRENT_R = 0;
        // Wait until the COUNT flag is set
        while ((NVIC_ST_CTRL_R & 0x00010000) == 0)
        {
        }
        // Decrement the delay
        delay--;
    }
}

void Delay(uint32_t time_ms)
{
    // Call SysTick_Wait for the given number of milliseconds
    SysTick_Wait(time_ms);
}

void Delay_half(void)
{
    unsigned long volatile time;
    time = 727240 * 500 / (91 * 2); // 0.125sec
    while (time)
    {
        time--;
    }
}
