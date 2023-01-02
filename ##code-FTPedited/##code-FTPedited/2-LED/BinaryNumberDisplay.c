/*
Binary number display using build in LED
from 0000 to 1111

*/

#include  <lpc214x.h>				//Includes LPC2148 register definitions

#define LED1_ON() IO1SET=(1<<16)	//Macro Functions to turn ON LED
#define LED2_ON() IO1SET=(1<<17)
#define LED3_ON() IO1SET=(1<<18)
#define LED4_ON() IO1SET=(1<<19)

#define LED1_OFF() IO1CLR=(1<<16)	//Macro Functions to turn OFF LED
#define LED2_OFF() IO1CLR=(1<<17)
#define LED3_OFF() IO1CLR=(1<<18)
#define LED4_OFF() IO1CLR=(1<<19)

#define BUZZER_ON() IO0CLR=(1<<11)		 //Macro Functions to turn ON Buzzer
#define BUZZER_OFF() IO0SET=(1<<11)


void  Delay(unsigned char j)	   //This Function is used to cause delay between LED ON and OFF events
{  
 unsigned int  i;
 for(;j>0;j--)
 {
  for(i=0; i<60000; i++);
 } 
}
void binary_led()
{	 
	int i, temp, rem, count = 0;
	for(i=0;i<16;i++)
	{
		temp = i;
		count = 0;
		while (temp > 0) {
		 rem = temp%2;
		 temp = temp/2;
		 count = count + 1;
		 if (rem == 1) {
		 if (count == 1) LED4_ON();
		 if (count == 2) LED3_ON();
		 if(count == 3) LED2_ON();
		 if (count == 4) LED1_ON();
		}
		else
		{
		 if (count == 1) LED4_OFF();
		 if (count == 2) LED3_OFF();
		 if(count == 3) LED2_OFF();
		 if (count == 4) LED1_OFF();
		 }
		}
		Delay(250);
		BUZZER_ON();
	    Delay(10);	 //The count value is updated in the EINT3 ISR
	    BUZZER_OFF();								   		
	}
}   
                        

int  main(void)
{  
 PINSEL0 = 0x00000000;		// Enable GPIO on all pins
 PINSEL1 = 0x00000000;
 PINSEL2 = 0x00000000;

 IO1DIR = (1<<19) | (1<<18) | (1<<17) | (1<<16);		// Set P1.16, P1.17, P1.18, P1.19 as Output
 IO0DIR = (1<<11);
 binary_led();
 return(0);
}