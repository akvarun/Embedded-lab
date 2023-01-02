			 
#include  <lpc214x.h>					 //Includes LPC2148 register definitions

// Using the 11th pin of port0 as buzzer 

#define BUZZER_ON() IO0CLR=(1<<11)		 //Macro Functions to turn ON Buzzer
#define BUZZER_OFF() IO0SET=(1<<11)		 //Macro Functions to turn OFF Buzzer



void  Delay(unsigned char j)	   //This Function is used to cause delay between LED ON and OFF events
{  
 unsigned int  i;
 for(;j>0;j--)
 {
  for(i=0; i<60000; i++);
 } 
}
                               
 
int  main(void)
{  
 PINSEL0 = 0x00000000;		// Enable GPIO on all pins

 IO0DIR = (1<<11) ;  // Set P0.11 as Output	to control buzzer
 	
 while(1)	
 { 
  BUZZER_ON();
  Delay(20);	 //The count value is updated in the EINT3 ISR
  BUZZER_OFF();
  Delay(10);
 }
}
