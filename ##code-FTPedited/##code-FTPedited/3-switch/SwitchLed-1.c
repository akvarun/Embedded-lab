
// to control one switch and one led

#include <lpc214x.h>   

#define SwitchPinNumber 15	 // build in switch connected with p0.15
#define LedPinNumber    16

/* start the main program */
int main() 
{
    unsigned int  switchStatus;
	

    PINSEL0 = 0x000000; //Configure the PORT1 Pins as GPIO;
	PINSEL1 = 0x000000; //Configure the PORT1 Pins as GPIO;
	PINSEL2 = 0x000000; //Configure the PORT1 Pins as GPIO;
    
    IODIR0 = (0<<SwitchPinNumber); // LED pin as output and Switch Pin as input 
	
	IODIR1=(1<<LedPinNumber);

  while(1)
    {

     /* Turn On all the leds and wait for one second */ 
       switchStatus = (IOPIN0>>SwitchPinNumber) & 0x01 ;  // Read the switch status- shift right side by 15 bit and perform and operation
	   // this will shift 15th bit to right and position in 1st bit location. AND will check status in 1st bit location either 1 or 0.
       
       if(switchStatus == 1)                 //Turn ON/OFF LEDs depending on switch status
       {  
         IOPIN1 = (1<<LedPinNumber);
       }
       else
       {
         IOPIN1 = (0<<LedPinNumber);
       }      
    }
}
