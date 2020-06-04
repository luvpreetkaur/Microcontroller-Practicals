#include<P18F4550.h>

void initint()
{
    RCONbits.IPEN=1;
    INTCON=0b11100000;
    INTCON2bits.TMR0IP=0;
}

void inittimer0()
{
    T0CON=0b00000111;
    TMR0H=0xED;
    TMR0L=0xB0;
}

void interrupt low_priority interrupt tmr()
{
    if(TMR0IF==1)
    {
        TMR0ON=0;
        TMR0IF=0;
        TMR0H=0xED;
        TMR0H=0xB0;
        PORTB=~PORTB;
        TMR0ON=1;
     }
}
void main()
{
    TRISB=0;
    PORTB=0xFF;
    inittimer0();
    initint();
    TMR0ON=1;
    while(1);
}

