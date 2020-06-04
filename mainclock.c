#include <p18f4550.h>
#include<stdio.h>
#include "lcd.h"
#include "DS1307rtc.h"
#include "rtcclock.h"
#include"i2c.h"

void disp_frame();

unsigned char str[16];

void main()
{
    unsigned char sec,min,hrs,unit,ten;
    i2c_init();
    InitLCD();
    ClearDisplay();
    disp_frame();

//    ROUTINE TO SET TIME.
//    Uncomment The following lines to set time to the RTC
//      reset_time();               // reset the time-keeping register to avoid collusion
    set_time(0x00,0x45);            // seconds
    set_time(0x01,0x57);            // Miniutes
    set_time(0x02,0x66);            // Hours along with 12hour and AM/PM selection bit.
//    set_time(0x03,0x06);          // Day
//    set_time(0x04,0x27);          // Date
//    set_time(0x05,0x07);          // Month
//    set_time(0x06,0x12);          // Year
// ********************************

    while(1)
    {
        sec = get_time(0);
        min = get_time(1);
        hrs = get_time(2)&0x0F;
        sprintf(str,"time:%02x:%02x:%02x",hrs,min,sec);
        SetLineNumber(2);
        LCDDisplayStr(str);
    }
}

void disp_frame()               // To display the basic frame that does not change.
{
    SetLineNumber(1);
    LCDDisplayStr("DS1307 RTC");
}

