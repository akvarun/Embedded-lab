
// to control two switch and one led

#include <lpc214x.h>   

#define SwitchPinNumber 15
#define SwitchPinNumber1 13
#define LedPinNumber    16

/* start the main program */
int main() 
{
    unsigned int  switchStatus;
	unsigned int  switchStatus1;

    PINSEL0 = 0x000000; //Configure the PORT1 Pins as GPIO;
	PINSEL1 = 0x000000; //Configure the PORT1 Pins as GPIO;
	PINSEL2 = 0x000000; //Configure the PORT1 Pins as GPIO;
    
    IODIR0 = (0<<SwitchPinNumber); // LED pin as output and Switch Pin as input 
	IODIR0 = (0<<SwitchPinNumber1);
	IODIR1=(1<<LedPinNumber);

  while(1)
    {

     /* Turn On all the leds and wait for one second */ 
       switchStatus = (IOPIN0>>SwitchPinNumber) & 0x01 ;  // Read the switch status
	   switchStatus1 = (IOPIN0>>SwitchPinNumber1) & 0x01 ;
       
       if(switchStatus1 == 1)                 //Turn ON/OFF LEDs depending on switch status
       {  
         IOPIN1 = (1<<LedPinNumber);
       }
       else
       {
         IOPIN1 = (0<<LedPinNumber);
       }      
    }
}
