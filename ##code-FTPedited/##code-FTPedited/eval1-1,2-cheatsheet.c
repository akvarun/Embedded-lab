#include  <lpc214x.h>					 //Includes LPC2148 register definitions


// BUZZER

#define BUZZER_ON() IO0CLR=(1<<11)		 //Macro Functions to turn ON Buzzer
#define BUZZER_OFF() IO0SET=(1<<11)		 //Macro Functions to turn OFF Buzzer

void  Delay(unsigned char j)

int main(void){
    PINSEL0 = 0x00000000;		// Enable GPIO on all pins

    IO0DIR = (1<<11) ;  // Set P0.11 as Output	to control buzzer


    //use while loop, if condition, anything
    
    //function calls
    //BUZZER_ON();
    //DELAY(20);        //time span when you can hear the buzzer on completely
    //BUZZER_OF();
    //DELAY(10):        //time gap to switch the buzzer off, so that you can hear the next buzzer
}

// LED

#define LED1_ON() IO1SET=(1<<16)	//Macro Functions to turn ON LED
#define LED2_ON() IO1SET=(1<<17)
#define LED3_ON() IO1SET=(1<<18)
#define LED4_ON() IO1SET=(1<<19)

#define LED1_OFF() IO1CLR=(1<<16)	//Macro Functions to turn OFF LED
#define LED2_OFF() IO1CLR=(1<<17)
#define LED3_OFF() IO1CLR=(1<<18)
#define LED4_OFF() IO1CLR=(1<<19)


void  Delay(unsigned char j)	   //This Function is used to cause delay between LED ON and OFF events

int main(void){
    PINSEL0 = 0x00000000;		// Enable GPIO on all pins
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;
     
    IO1DIR = (1<<19) | (1<<18) | (1<<17) | (1<<16);		// Set P1.16, P1.17, P1.18, P1.19 as Output


    //use while loop, if condition, anything
    
    //function calls
    // LED1_ON();
    // Delay(100);
    // LED1_OFF();
    // Delay(50);

    // check out- main-out and main-test

}


// Summary

// BUZZER - pin 11
//          first half so IO1
//          CLR is on
//          SET is off
//          PINSEL0
//          IO1DIR => to set particular pin as output


// LED - pin 16,17,18,19
//      second half so IO2
//      SET is on
//      CLR is off
//      PINSEL0,1,2
//      IO2DIR => use | (or)