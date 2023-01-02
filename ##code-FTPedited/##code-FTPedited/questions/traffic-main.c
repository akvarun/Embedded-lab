
#include  <lpc214x.h>					 //Includes LPC2148 register definitions

#define LED1_ON() IO1SET=(1<<16)	//Macro Functions to turn ON LED
#define LED2_ON() IO1SET=(1<<17)
#define LED3_ON() IO1SET=(1<<18)
#define LED4_ON() IO1SET=(1<<19)

#define LED1_OFF() IO1CLR=(1<<16)	//Macro Functions to turn OFF LED
#define LED2_OFF() IO1CLR=(1<<17)
#define LED3_OFF() IO1CLR=(1<<18)
#define LED4_OFF() IO1CLR=(1<<19)

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
 char pass[4] = "aaaa";
 char inputpass[4] = "aaaa";
 int t,i;

 PINSEL0 = 0x00000000;		// Enable GPIO on all pins
 PINSEL1 = 0x00000000;
 PINSEL2 = 0x00000000;	

 IO1DIR = (1<<19) | (1<<18) | (1<<17) | (1<<16);
 
 t = 0; 

 for(i=0;i<4;i++){
 	if(pass[i]!=inputpass[i]){
 	t=1;
 	break;
	}
 }
 	
 if(t==0){		 
	LED1_ON();
 }else{
	LED1_ON();
	LED2_ON();
	LED3_ON();
	LED4_ON();
	BUZZER_ON();
	IO0DIR = (1<<11) ;  // Set P0.11 as Output	to control buzzer
 }


 	
 
}



