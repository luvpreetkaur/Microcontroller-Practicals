//Name: Luvpreet Kaur
//Roll no:3043338

 			  #include "LPC1768_Includes.h"



void delay(unsigned int time)

{

unsigned int i,j;

for(i=0;i<time;i++)

	for(j=0;j<20000;j++);

}





int main()

{

unsigned int period = 100000,i;



PINSEL3 = 0x00020000;				//Configure pin P1.24 as PWM1.5

PCONP = 1<<6;			  			//Enable the PWM peripheral



PWM1CTCR = 0x00000000;			   	//Select Timer mode

PWM1PR = 0x00;						//set the prescalar

PWM1MCR =  0x00000002;				//Reset timer on match with PWM1MR0 register



PWM1MR0 =  period;					//set the period

PWM1PCR =  0x00002000;				//Enable PWM1.5 in single edge mode 

PWM1TCR =  0x00000009;			   	//Enable PWM and TC



while(1)

{

	for(i=10;i>0;i--)

	{

		PWM1MR5 = i*period/10;		 //Change Duty Cycle

		PWM1LER = 0x00000020;

	 	delay(1000);

	}

}

return 0;

}

