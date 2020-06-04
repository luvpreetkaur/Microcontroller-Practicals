#include <p18f4550.h>
#include "i2c.h"
#include "lcd.h"

void reset_time()       // resets the time-keeping register
{
    i2c_start();
    i2c_write(RTC_ADD);
    i2c_write(0x00);    // sec
    i2c_write(0x00);    // min
    i2c_write(0x00);    // hrs
    i2c_write(0x01);    // day
    i2c_write(0x01);    // date
    i2c_write(0x01);    // month
    i2c_write(0x01);    // year
   // i2c_write(0x90);    // wave
//    i2c_write(0);
    i2c_stop();
    return;
}

unsigned char get_time(unsigned char address)     // Gets time
{
    unsigned char data;
    i2c_start();
    i2c_write(RTC_ADD);
    i2c_write(address);
    i2c_restart();
    i2c_write(RTC_ADD | 0x01);
    SSPCON2bits.ACKDT=1;
    data=i2c_read();
    i2c_stop();
    return (data);
}

void set_time(unsigned char address, unsigned char x)     // sets time
{
    i2c_start();
    i2c_write(RTC_ADD);
    i2c_write(address);
    i2c_write(x);
    i2c_stop();
    return;
}
