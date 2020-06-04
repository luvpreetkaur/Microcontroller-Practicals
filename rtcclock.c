#include <p18f4550.h>
#include "lcd.h"
#include "rtcclock.h"
#include "DS1307rtc.h"

unsigned int units,tens;        // Global var.

void display(void)
{
    time(get_time(2),get_time(1),get_time(0));
 //   date(get_time(4),get_time(5),get_time(6));
 //   day(get_time(3));
    return;
}

void time(unsigned char hours,unsigned char minutes,unsigned char seconds)
{
    decode(hours);      // sepatates the variable into highr and lower nibble
    if(tens>3)      // To set AM or PM
    {
        if((tens == 6)|(tens == 7))
        {
            SendInstruction(0xCF);
            SendData('P');
            SendData('M');
            tens=tens&1;
        }
        else if((tens == 4)|(tens == 5))
        {
            SendInstruction(0xCF);
            SendData('A');
            SendData('M');
            tens=tens&1;
        }
    }
    else
    {
        SendInstruction(0xCF);
        SendData(' ');
        SendData(' ');
    }
    SendInstruction(0xC6);
    SendData(tens+48);      // Add 48 to display ASCII value of number
    SendData(units+48);

    SendInstruction(0xC9);
    decode(minutes);        // sepatates the variable into highr and lower nibble
    SendData(tens+48);
    SendData(units+48);

    SendInstruction(0xCC);
    decode(seconds);        // sepatates the variable into highr and lower nibble
    SendData(tens+48);
    SendData(units+48);

}

void date(unsigned int date, unsigned int month,unsigned int year)
{
    //SendInstruction(0x9A);
    decode(date);       // sepatates the variable into highr and lower nibble
    SendData(tens+48);
    SendData(units+48);

    //SendInstruction(0x9D);
    decode(month);      // sepatates the variable into highr and lower nibble
    SendData(tens+48);
    SendData(units+48);

    //SendInstruction(0xA2);
    decode(year);       // sepatates the variable into highr and lower nibble
    SendData(tens+48);
    SendData(units+48);
}

void day(unsigned int disp)
{
    //SendInstruction(0xD9);
    //SendInstruction(0xDA);
    switch(disp)
    {
	case 1:LCDDisplayStr("Sunday");
               break;
	case 2:LCDDisplayStr("Monday");
               break;
	case 3:LCDDisplayStr("Tuesday");
               break;
	case 4:LCDDisplayStr("Wednesday");
               break;
	case 5:LCDDisplayStr("Thursday");
               break;
	case 6:LCDDisplayStr("Friday");
               break;
	case 7:LCDDisplayStr("Saturday");
               break;
    }
}

void decode(unsigned char val)       // Function sepatates the variable into highr and lower nibble
{
    tens=val>>4;
    units=val&0x0F;
    return;
}
