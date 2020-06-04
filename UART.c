#include<P18F4550.h>

void serialen()
{
    SPBRG=77;
    TXSTA=0x20;
    RCSTA=0x90;
}

char receive()
{
    while(PIR1bits.RCIF==0);
    return RCREG;
}

void transmit(char z)
{
    TXREG=z;
    while(PIR1bits.TXIF==0);
}

void main()
{
    char z;
    TRISCbits.RC6=0;
    TRISCbits.RC7=1;
    serialen();
    while(1)
    {
        z=receive();
        z++;
        transmit(z);
    }
}
