//Name: Luvpreet Kaur
//Roll no:3043338

/*
Pin Configuration
A		- 	P0.0
B		-	P0.1
C		-	P0.2
D		-	P0.3
E		-	P0.4
F		-	P0.5
G		-	P0.6
DOT		-	P0.7
SEG1	-	P0.8
SEG2	-	P0.9
*/		

#include "LPC1768_Includes.h" 

#define SEG_A  1<<0			   // SEGMENT 	A
#define SEG_B  1<<1			   // SEGMENT 	B
#define SEG_C  1<<2			   // SEGMENT 	C
#define SEG_D  1<<3			   // SEGMENT 	D
#define SEG_E  1<<4			   // SEGMENT 	E
#define SEG_F  1<<5			   // SEGMENT 	F
#define SEG_G  1<<6			   // SEGMENT 	G
#define SEG_DP 1<<7			   // SEGMENT 	DECIMAL POINT
#define SEG1   1<<8
#define SEG2   1<<9

#define ONE     0x06
#define TWO     0x5B
#define THREE   0x4F
#define FOUR    0x66
#define FIVE    0x6D
#define SIX     0x7D
#define SEVEN   0x07
#define EIGHT   0x7F
#define NINE    0x6F
#define ZERO    0x3F


void delay(unsigned int time)
{
unsigned int i,j;
	for(i = 0; i < time ;i++ )
	{
		for(j = 0; j < 5000 ; j++);
	}
}


int main(void)
{
unsigned char segData[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

unsigned char i = 15,j;
  
  PINSEL0  = 0;
  FIO0DIR = 0x3FF;	// set the direction of the pins as output
  FIO0SET = 0x3FF;	// set all the pins as high

 while(1)
	{
	for(i =0 ; i <= 9 ; i++ )
	{
		
			FIO0SET = SEG1;			   //select segment 1
			FIO0CLR = SEG2;

	
			FIO0CLR = segData[i];	// since the 7 seg display is common anode we have to clear the port pins to make SEGMENT ON
			delay(2000);					//display quotient or the tens place
			FIO0SET = segData[i];

		
		

	}
 }
return 0;
}
