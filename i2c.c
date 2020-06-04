#include <p18f4550.h>
#include"i2c.h"

void i2c_interface_init()
{
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
   
}

void i2c_interface_deinit()
{
    SSPCON1bits.SSPEN = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
}

void i2c_init(void)
{
    i2c_interface_init();
    SSPADD = 126;  //set i2c clock
    SSPCON1= 0b00001000; //set i2c master
    SSPSTATbits.SMP = 1;  //select mode...standard selected
   // ADCON1 = 0x0F;
    SSPCON1bits.SSPEN = 1;
}

void i2c_start(void)    // Initiate a Start sequence
{
    PIR1bits.SSPIF=0;
    SSPCON2bits.SEN=1;
    while(PIR1bits.SSPIF == 0);
}

void i2c_restart(void)  // Initiate a Restart sequence
{
    PIR1bits.SSPIF=0;
    SSPCON2bits.RSEN=1;
    while(PIR1bits.SSPIF==0);
}

void i2c_device(void)   // device specification
{
    PIR1bits.SSPIF=0;
    SSPBUF=RTC_ADD;
    while(PIR1bits.SSPIF==0);
    while(SSPCON2bits.ACKSTAT==1);
}


void i2c_write(unsigned int data)      // Write data to slave.
{
    PIR1bits.SSPIF=0;
    SSPBUF=data;
    while(PIR1bits.SSPIF==0);
}

void i2c_stop(void)     //Initiate a Stop sequence.
{
    PIR1bits.SSPIF=0;
    SSPCON2bits.PEN=1;
    while(PIR1bits.SSPIF==0);
}

unsigned char i2c_read(void)     //Read data from I2C bus.
{
    unsigned char data;
    PIR1bits.SSPIF=0;
    SSPCON2bits.RCEN=1;

    while(PIR1bits.SSPIF==0);
    data=SSPBUF;
    PIR1bits.SSPIF=0;
    SSPCON2bits.ACKEN=1;
    while(PIR1bits.SSPIF==0);
    return data;
}

