// SetupBLT.c
// Purpose: This is an example program to setup HC-05 Bluetooth module with an added user interface.
// Group: Robby Rimal, Jonathan Cerniaz, Joseph Guzman, Afzal Hakim
// Runs on TM4C123
// UART0 is used for the TM4C123 to communicate with PC serial terminal,
// UART1 is used for the TM4C123 to cummunicate with HC-05 Bluetooth module
// U1Rx (PB0) connects to HC-05 TXD pin
// U1Tx (PB1) connects to HC-05 RXD pin
// HC-05 VCC connects to vbus pin on TM4C123
// HC-05 EN connects to +3.3v
// HC-05 GND connects to GND

#include "tm4c123gh6pm.h"
#include "UART0.h"
#include "BLT.h"
#include <stdint.h> // for data type alias
#include <string.h>
#include <stdlib.h>

// main function for programming BT device with no UI
int main(void)
{
  uint8_t String[30];
  for (int i = 0; i < 30; i++)
  {
    String[i] = 0;
  }
  uint8_t UserInput[30]; // user input variable
  uint8_t i;
  UART0_Init();
  BLT_Init();

  // create a starting menu for the user
  UART0_OutString((uint8_t *)">>> Welcome to Serial Terminal. <<<");
  UART0_NextLine();
  UART0_OutString((uint8_t *)">>> This is the setup program for HC-05 Bluetooth module. <<<");
  UART0_NextLine();
  UART0_OutString((uint8_t *)">>> You are at 'AT' Command Mode. <<<");
  UART0_NextLine();
  UART0_OutString((uint8_t *)">>> Type 'AT' and followed with a command. <<<");
  UART0_NextLine();
  UART0_OutString((uint8_t *)">>> Example: AT+NAME=Your Name <<<");
  UART0_NextLine();

  while (1)
  {

    // get AT command from user
    UART0_OutString((uint8_t *)"> ");
    UART0_InString(UserInput, 30);
    UART0_NextLine(); // Move to the next line after input

    // Send command to HC-05
    BLT_OutString(UserInput);
    BLT_OutString((uint8_t *)"\r\n");
    while ((UART1_FR_R & UART_FR_BUSY) != 0)
    {
    };

    // Display response from HC-05
    BLT_InString(String); // get the 1st thing before OK
    UART0_OutString(String);
    UART0_NextLine();

    // Clear the string buffer
    for (i = 0; i < 30; i++)
    {
      String[i] = 0;
    }
    if (UserInput[strlen((char *)UserInput) - 1] == '?')
    {
      BLT_InString(String);
      //UART0_OutChar(SP);
      UART0_OutString(String);
      UART0_NextLine();
    }
  }
}