/*
									Amrita Vishwa Vidyapeetham
									Amrita School of Computing, Coimbatore
									B.Tech Lab session– December 2022
									Fifth Semester
									Computer Science and Engineering
									19CSE303 Embedded Systems 
Questions
----------
Demonstrate UART and LCD interface using LPC2148 microcontroller.
a.	Display character in LCD, using UART (Tx) 
b.	Display character in LCD. Character received from your PC keyword and send to LCD using UART (RX). 


*/


#include  <lpc214x.h>	  //Includes LPC2148 register definitions
#define PLOCK 0x00000400 // for PLL
#define THRE (1<<5) // Transmit Holding Register Empty
#define RDR (1<<0) // Receiver Data Ready
#define MULVAL 15
#define DIVADDVAL 1
#define NEW_LINE 0xA // Character for new line .. analogus to '\n'
#define ENTER 0xD // Ascii code for Enter 

void initUART0(void);
void U0Write(char data);
char U0Read(void);
void initClocks(void);

void setupPLL0(void);
void feedSeq(void);
void connectPLL0(void);
#define DATA_PORT() IO0SET=(1<<16)		 //Function to select data port on LCD
#define READ_DATA() IO0SET=(1<<17)		 //Function to select read operation on LCD
#define EN_HI() IO0SET=(1<<18)			 //Function to Enable LCD


#define COMMAND_PORT() IO0CLR=(1<<16)	  //Function to select command port on LCD
#define WRITE_DATA() IO0CLR=(1<<17)		  //Function to select write operation on LCD
#define EN_LOW() IO0CLR=(1<<18)			  //Function to disable LCD


void Delay(unsigned char j)
{  
 unsigned int  i;
 for(;j>0;j--)
 {
  for(i=0; i<60000; i++);
 } 
}

void Delay_Small(unsigned char j)
{
 unsigned int  i;
 for(;j>0;j--)
 {
  for(i=0; i<1000; i++);
 } 
}
                               

unsigned char Busy_Wait()			   //This function checks the busy status of LCD
{
 unsigned int temp=0;
 EN_LOW();
 COMMAND_PORT();
 READ_DATA();
 
 IO0PIN&=0xFF87FFFF;	  
 IO0DIR&=0xFF87FFFF;
 IO0PIN|=0x00400000;
 
 do{
 EN_HI();
 EN_LOW();
 EN_HI();
 EN_LOW();
 temp=IO0PIN;
 }
 while((temp & 0x00400000)==0x00400000);
 EN_LOW();
 WRITE_DATA();
 IO0DIR&=0xFF80FFFF;
 IO0DIR|=0x007F0000;
 return (0);
}    


void LCD_Command(unsigned int data)			  //This function is used to send LCD commands
{
 unsigned int temp=0;
 EN_LOW();
 COMMAND_PORT();
 WRITE_DATA();
 
 temp=data;
 //IO0PIN&=0xFF87FFFF;
 IO0PIN&=0x00010000;
 IO0PIN|=(temp & 0xF0) << 15;

 EN_HI();
 EN_LOW();
 
 temp=data & 0x0F;
 //IO0PIN&=0xFF87FFFF;
 IO0PIN&=0x00010000;
 IO0PIN|=(temp) << 19;

 EN_HI();
 EN_LOW();
 //while(Busy_Wait());
 Delay(10);
} 


void LCD_Data(unsigned int data)		   //This function is used to send data to LCD
{
 unsigned int temp=0;
 EN_LOW();
 DATA_PORT();
 WRITE_DATA();
 
 temp=data;
 //IO0PIN&=0xFF87FFFF;
 IO0PIN&=0x00010000;
 IO0PIN|=(temp & 0xF0) << 15;

 EN_HI();
 EN_LOW();
 
 temp=data & 0x0F;
 
 //IO0PIN&=0xFF87FFFF;
 IO0PIN&=0x00870000;
 IO0PIN|=(temp) << 19;

 EN_HI();
 EN_LOW();
 Delay_Small(1);
}

void LCD_Init()
{
 LCD_Command(0x02);		
 LCD_Command(0x28);
 LCD_Command(0x0C);
 LCD_Command(0x06);
}


void LCD_String(unsigned char *data)
{
 while(*data)
 {
  LCD_Data(*data);
  data++;
 } 
}  

unsigned char str[32]="                                ";
int i=0;
int main(void)
{
	PINSEL0 = 0x00000000;		// Enable GPIO on all pins
	PINSEL1 = 0x00000000;
	PINSEL2 = 0x00000000;

	Delay(20);
	IO0DIR = (1<<22) | (1<<21) | (1<<20) | (1<<19) | (1<<18) | (1<<17) | (1<<16);		// Set P0.16, P0.17, P0.18, P0.19, P0.20, P0.21, P0.22 as Output
	initClocks(); // Set CCLK=60Mhz and PCLK=60Mhz 
	initUART0();
	
	while(1)		
	{
		char c = U0Read(); // Read Data from Rx
		if( c == ENTER ) // Check if user pressed Enter key
		{
			U0Write(c); // Send New Line ASCII code change line
			break;
		}
		else
		{
			str[i]=c;
			i++;
			U0Write(c); // Write it to Tx to send  it back
		}
	}
	LCD_Init();
	LCD_Command(0x01);
	Delay(20);

	LCD_Command(0x80);
	LCD_String(&str[0]);
	LCD_Command(0xC0);
	LCD_String(&str[16]);
	
	return 0;
}

void initUART0(void)
{
	PINSEL0 = 0x5;  /* Select TxD for P0.0 and RxD for P0.1 */
	U0LCR = 3 | (1<<7) ; /* 8 bits, no Parity, 1 Stop bit | DLAB set to 1  */
	U0DLL = 110;
	U0DLM = 1;   
	U0FDR = (MULVAL<<4) | DIVADDVAL; /* MULVAL=15(bits - 7:4) , DIVADDVAL=0(bits - 3:0)  */
	U0LCR &= 0x0F; // Set DLAB=0 to lock MULVAL and DIVADDVAL
	//BaudRate is now ~9600 and we are ready for UART communication!
}

void U0Write(char data)
{
	while ( !(U0LSR & THRE ) ); // wait till the THR is empty
	// now we can write to the Tx FIFO
	U0THR = data;
}

char U0Read(void)
{
	while( !(U0LSR & RDR ) ); // wait till any data arrives into Rx FIFO
	return U0RBR;
}

void initClocks(void)
{
	setupPLL0();
	feedSeq(); //sequence for locking PLL to desired freq.
	connectPLL0();
	feedSeq(); //sequence for connecting the PLL as system clock

	//SysClock is now ticking @ 60Mhz!
	   
	VPBDIV = 0x01; // PCLK is same as CCLK i.e 60Mhz

	//Using PLL settings as shown in : http://www.ocfreaks.com/lpc214x-pll-tutorial-for-cpu-and-peripheral-clock/
	//PLL0 Now configured!
}


//---------PLL Related Functions :---------------

void setupPLL0(void)
{
	//Note : Assuming 12Mhz Xtal is connected to LPC2148.

	PLL0CON = 0x01; // PPLE=1 & PPLC=0 so it will be enabled
					// but not connected after FEED sequence
	PLL0CFG = 0x24; // set the multipler to 5 (i.e actually 4)
					// i.e 12x5 = 60 Mhz (M - 1 = 4)!!!
					// Set P=2 since we want FCCO in range!!!
					// So , Assign PSEL =01 in PLL0CFG as per the table.
}

void feedSeq(void)
{
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
}

void connectPLL0(void)
{
	// check whether PLL has locked on to the desired freq by reading the lock bit
	// in the PPL0STAT register

	while( !( PLL0STAT & PLOCK ));

	// now enable(again) and connect
	PLL0CON = 0x03;
}
