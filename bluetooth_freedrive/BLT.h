// CECS 447: Project 3 - A Bluetooth Controlled Robot Car
// BLT.h
// Purpose: 
// Group: Robby Rimal, Jonathan Cerniaz, Joseph Guzman, Afzal Hakim
// Runs on TM4C123 or LM4F120
// this connection occurs in the USB debugging cable
// U1Rx (PB0)
// U1Tx (PB1)
// Ground connected ground in the USB cable

#include <stdint.h>

// standard ASCII symbols
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define SP   0x20

//------------BLT_Init------------
// Initialize the UART1 for 115200 baud rate (assuming 80 MHz clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void BLT_Init(void);

//------------BLT_OutChar------------
// Output 8-bit to serial port UART1
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void BLT_OutChar(uint8_t data);

//------------BLT_OutString------------
// Output String (NULL termination) to UART1
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void BLT_OutString(uint8_t *pt);

//------------BLT_InChar------------
// Wait for new serial port input from UART1
// Input: none
// Output: ASCII code for key typed
unsigned char BLT_InChar(void);

//------------BLT_InString------------
// Gets reply from HC-05 Bluetooth module through UART1
void BLT_InString(uint8_t *bufPt);

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART0_OutChar(uint8_t data);
