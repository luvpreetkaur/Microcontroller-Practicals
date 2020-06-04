#include<P18F4550.h>
#include<stdio.h>

void delay(int x)
{
    int i,j;
    for(i=0;i<x;i++)
        for(j=0;j<500;j++);
}

void sendcmd(unsigned char cmd)
{

    PORTCbits.RC0=0;
    delay(10);
    PORTCbits.RC1=1;
    delay(10);
    PORTB=cmd;
    delay(10);
    PORTCbits.RC1=0;
    delay(10);
}

void sendata(char data)
{
    PORTCbits.RC0=1;
    delay(10);
    PORTCbits.RC1=1;
    delay(10);
    PORTB=data;
    delay(10);
    PORTCbits.RC1=0;
    delay(10);

}

void initLCD()
{
    TRISB=0;
    TRISCbits.RC0=0;
    TRISCbits.RC1=0;
    sendcmd(0x38);
    delay(10);
    sendcmd(0x01);
    delay(10);
    sendcmd(0x0C);
    delay(10);
    sendcmd(0X06);
    delay(10);
}

void displaystring(char *string)
{
    while(*string)
    {
        sendata(*string);
        *string++;
        delay(10);
    }
}

short readADC()
{
    ADCON0=0b00011100;
    ADON=1;
    GODONE=1;
    while(GODONE==1)
        return ADRES;
}
void initADC()
{
    TRISEbits.RE2=1;
    
    ADCON1=0b00000111;
    ADCON2=0b10101110;
}

void display(short ADCval)
{
    char i,text[];
    short temp;
    temp=ADCval;
    ADCval=(5500/1024)*temp;
   /* for(i=3;i>=0;i--)
    {
        text[i]=(ADCval%10)+'0';
        ADCval=ADCval/10;
    }
    text[4]='m';
    text[5]='V';*/
    sprintf(text,"%04dmv",ADCval);
    for(i=0;i<6;i++)
    {
        sendata(text[i]);
        delay(10);
    }
    sendcmd(0xC0);
    for(i=0;i<10;i++)
    {
        if((temp&0x200)==0x200)
            sendata('1');
        else
            sendata('0');
    }
    temp<<=1;
}

void main()
{
    short chr;
    initADC();
    initLCD();
    while(1)
    {
        sendcmd(0x80);
        displaystring("Analog_inp:");
        chr=readADC();
        display(chr);
    }
}
