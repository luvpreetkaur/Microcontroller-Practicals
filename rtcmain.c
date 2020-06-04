#include<stdio.h>
#include"i2c.h"
#include"lcd.h"

unsigned char string[20];

void main(void)
{
 unsigned int * reg_data ;
 unsigned char reg_addr=0;

 
 InitLCD();
 ClearDisplay();
 SetLineNumber(1);
 sprintf(string,"Hello World");
 LCDDisplayStr(&string);
 init_i2c();

if(write_data(0x00,0x00))
{
    SetLineNumber(2);
    LCDDisplayStr("write data fail");
    while(1);
}

 while(1)
{
     SetLineNumber(2);
     sprintf(string,"time:");
     LCDDisplayStr(&string);
	//read seconds
	reg_addr=2;
 	if(!read_register(reg_addr,&reg_data))
	{
	   sprintf(string,"%x",reg_data);
           LCDDisplayStr(&string);
	}
	reg_addr=1;
	if(!read_register(reg_addr,&reg_data))
	{
	  printf(": %x",reg_data);
	}
	reg_addr=0;
	if(!read_register(reg_addr,&reg_data))
	{
	   printf(": %x",reg_data);
	}
	delay(1);
}
  while(1);
}