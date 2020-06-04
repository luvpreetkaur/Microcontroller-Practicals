//Name: Luvpreet Kaur
//Roll no:304338

#include "LPC214x.h"
#include "UART.h"
#include "stdio.h"

#define EEPROM_Addr 0xA0		  	//device address
#define I2Cwrite	0x00
#define I2Cread		0x01

#define I2C_ENABLE 	1 << 6
#define I2C_START	1 << 5
#define I2C_STOP 	1 << 4
#define I2C_SI		1 << 3		  //I2C interrupt flag
#define I2C_AACK  	1 << 2		  //assert ACK flag

unsigned char write_array[10] = {0x04,0x2A,0x63,0x9D,0x10,0xB6,0x82,0x94,0x39,0xC5};
unsigned char read_array[10];


void I2CInit(void)
{
	PINSEL0 &= 0xFFFFFF0F;							//set the pins for i2c functions
	PINSEL0 |= 0x00000050;
	
	I2C0CONCLR  = I2C_ENABLE | I2C_START | I2C_STOP | I2C_SI | I2C_AACK;	//clear all the bits in CONTROL register
	
	//set I2C clock to work at 100Khz 
	I2C0SCLH = 0x4B ;							//set the high time of i2c clock; (15mhz / 100khz / 2)
	I2C0SCLL = 0x4B ;							//set the low time of i2c clock;
	
	I2C0CONSET = I2C_ENABLE ;					//enable the I2C Interface
}										


void I2CStart(void)
{
unsigned int status;	
I2C0CONCLR = (I2C_START | I2C_STOP | I2C_SI | I2C_AACK); 	// clear all the bits in CONCLR register	
I2C0CONSET = (I2C_ENABLE );					 		  		//Enable the I2C interface 
I2C0CONSET = (I2C_START);					  				//set the STA bit 
while(!((status=I2C0CONSET)& I2C_SI));						//wait till interrupt flag becomes set
}


void I2CStop(void)
{	
 I2C0CONSET = I2C_STOP;										//set STOP bit
 I2C0CONCLR = I2C_START | I2C_SI | I2C_AACK;				//clear all bits 
}


void I2Csend(unsigned char data)
{	   
	unsigned int status;
	I2C0DAT = data;
	I2C0CONCLR = I2C_START | I2C_STOP ;						// clear start bit for next operation 
	I2C0CONCLR = I2C_SI;									// clear interrupt flag
	while(!((status=I2C0CONSET)& I2C_SI));				   	//wait till interrupt flag becomes set
}

unsigned char I2Cget(unsigned int ack)
{
unsigned char data;
unsigned int status;

I2C0CONCLR = I2C_START | I2C_STOP;						
I2C0CONSET = I2C_AACK;								   	// send ack to continue further data transfer
I2C0CONCLR = I2C_SI;									// clear start bit for next operation
while(!((status=I2C0CONSET)& I2C_SI));					//wait till interrupt flag becomes set
data = I2C0DAT;
return data;
}


int main()
{
unsigned int i;
UartInit(9600);					  //initialize UART with 9600 baudrate
printf("\nI2C EEPROM\n\n");
I2CInit();						  //initialize I2C

 	/* Write Sequence */ 
printf("Writing Data.....\n");
I2CStart();
I2Csend(EEPROM_Addr | I2Cwrite);
I2Csend(0x13);		   				//Address higher byte
I2Csend(0x49);						//Address lower byte

for(i=0;i<10;i++)
	I2Csend(write_array[i]); 		//write the array to EEPROM
I2CStop();

	/* Read Sequence */
printf("\nReading.....\n\n");
I2CStart();
I2Csend(EEPROM_Addr | I2Cwrite);
I2Csend(0x13);						//Address higher byte
I2Csend(0x49);			 			//Address lower byte
I2CStart();
I2Csend(EEPROM_Addr | I2Cread);
for(i=0;i<10;i++)
	read_array[i] = I2Cget(i); 		//Read EEPROM
I2CStop();


for(i=0;i<10;i++)
	printf("write_array[%d] = 0x%02X\tread_array[%d] = 0x%02X\n", i, write_array[i], i, read_array[i]);		  //display write and read data


while(1);	 			 //stop here
return 0;
}
