                           Experiment god knows which

#include <P18f4550.h>
void timer_Init(void)
{
    T0CON=0X07;
    TMR0H=0XED;
    TMR0L=0XB0;
}
void Interrupt_Init(void)
{
    RCONbits.IPEN=1;
    INTCON=0XE0;
    INTCON2bits.TMR0IP=0;
}
void interrupt low_priority timerinterrupt(void)
{
    if(TMR0IF==1)
    {
        TMR0ON=0;
        TMR0IF=0;
        TMR0H=0XED;
        TMR0L=0XB0;
        LATB=~LATB;
        TMR0ON=1;
    }
}
    
void main(void)
{
    TRISB=0x00;
    LATB=0XFF;
    Interrupt_Init();
    timer_Init();
    TMR0ON=1;
    while(1);


}


