// CECS 447: Project 3 - Bluetooth Controlled Car
// File Name: LED.h
// Purpose: Defines Port F interrupt enable bit and declares for initializing LEDs and switches.
// Group: Robby Rimal 
// 				Jonathan Cerniaz 
// 				Joseph Guzman
// 				Afzal Hakim
// Last Modified: 10/4/2024


////////// Constants //////////
// Color LED(s) PortF
// dark --- 0
// red R-- 0x02
// blue --B 0x04
// green -G- 0x08
// yellow RG- 0x0A
// white RGB 0x0E
// pink R-B 0x06
// Cran -GB 0x0C

#define NVIC_EN0_PORTF 0x40000000
#define LED (*((volatile unsigned long *)0x40025038))  // use onboard three LEDs: PF321

void LED_Init(void);