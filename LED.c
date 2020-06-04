
#include<PIC18F4550.h>

void delay()
{
  int d=90000;
  while(d!=0)
    {
      d--;
    }
}
void main()
{
    int i, key;
    TRISB=0x00;
    TRISDbits.TRISD0=1;
    TRISDbits.TRISD1=1;
    TRISDbits.TRISD2=0;
    TRISAbits.TRISA4=0;
    while (1)
    {
        if(PORTDbits.RD0==0) key=0;
        if(PORTDbits.RD1==0) key=1;
        if(key==0)
        {
            PORTAbits.RA4=1;
            PORTDbits.RD2=0;
            for(i=0;i<8;i++)
            {
                PORTB=1<<i;
                delay();
                delay();
            }
        }
        if(key==1)
        {
           PORTAbits.RA4=0;
           PORTDbits.RD2=1;
           for(i=0;i<8;i++)
            {
                PORTB=128>>i;
                delay();
                delay();
            }
        }
    }
}