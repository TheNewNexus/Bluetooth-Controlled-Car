// CECS 447: Project 3 - A Bluetooth Controlled Robot Car
// BLT.c
// Purpose: This contains necessary functions to initialize UART1 for HC-05 Bluetooth module.
// Group: Robby Rimal, Jonathan Cerniaz, Joseph Guzman, Afzal Hakim
// Runs on TM4C123 
// this connection occurs in the USB debugging cable
// U1Rx (PB0)
// U1Tx (PB1)
// Ground connected ground in the USB cable

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "BLT.h"



//------------BLT_Init------------
// Initialize the UART1 for 38400 baud rate (assuming 16 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void BLT_Init(void){
	// Activate Clocks
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; // activate UART0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
	
	
	UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 17;                    // IBRD = int(16,000,000 / (16 * 57600)) = int(17.3611111)
  UART0_FBRD_R = 23;                     // FBRD = round(3611111 * 64) = 27
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= 0x301;                 // enable UART for both Rx and Tx

  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1,PA0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1,PA0
                                        // configure PA1,PA0 as UART0
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA1,PA0
	
  UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
	
	// Data Communication Mode, Buad Rate = 57600
  UART1_IBRD_R = 17;                    // IBRD = int(16,000,000 / (16 * 57600)) = int(17.3611111)
  UART1_FBRD_R = 23;                     // FBRD = round(3611111 * 64) = 27
	
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART1_CTL_R |= 0x301;                 // enable UART for both Rx and Tx
  
  GPIO_PORTB_AFSEL_R |= 0x03;           // enable alt funct on PB1,PB0
  GPIO_PORTB_DEN_R |= 0x03;             // enable digital I/O on PB1,PB0
                                        // configure PB1,PB0 as UART1
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTB_AMSEL_R &= ~0x03;          // disable analog functionality on PB1,PB0
}

//------------BLT_OutChar------------
// Output 8-bit to serial port UART1
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void BLT_OutChar(uint8_t data){
  while((UART1_FR_R&UART_FR_TXFF) != 0);
  UART1_DR_R = data;
}

//------------BLT_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void BLT_OutString(uint8_t *pt){
  while(*pt){
    BLT_OutChar(*pt);
    pt++;
  }
}

//------------BLT_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
unsigned char BLT_InChar(void){
  while((UART1_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART1_DR_R&0xFF));
}


// This function reads response from HC-05 Bluetooth module.
// this function brings out a null terminated C string.
void BLT_InString(uint8_t *bufPt) {
  uint8_t length=0;
	
  // The follwoing code is based on the fact that a reply from HC-05 always end with "\r\n"
	do {
    bufPt[length] = BLT_InChar();
    length++;
	}while (bufPt[length-1]!=LF);

  // remove CR&LF and add null terminator
  length -= 2;
  bufPt[length] = 0;
}
