
#include<P18F4550.h>

void delay(int x)
{
    int i,j;
    for(i=0;i<x;i++)
        for(j=0;j<200;j++);
}
char a[]={'A','0','1','2','B','3','4','5','C','6','7','8','D','9','#','*'};
void sendcmd(char cmd)
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
    sendcmd(0x38);
    delay(10);
    sendcmd(0x01);
    delay(10);
    sendcmd(0x0C);
    delay(10);
    sendcmd(0X06);
    delay(10);
}

void setline(char x)
{
    if(x==1)
    {
        sendcmd(0x80);
        delay(10);
    }
    if(x==2)
    {
        sendcmd(0xC0);
        delay(10);
    }

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

 char knowkey(char col ,char row)
    {
        int i;
        for(i=0;i<4;i++)
        {
            if((row&0x01)!=0x01)
            
                return (a[i+(col)]);
            else
                row>>=1;
        }
    }

char getkey()
{
    char row,val;
    while(1)
    {
    PORTD=0xFF;
    PORTDbits.RD0=0;
    delay(1);
    row=PORTD;
    row>>=4;
    if((row&0x0F)!=0x0F)
    {
        val=knowkey(0,row);
        PORTDbits.RD0=1;
        return val;
    }
    PORTDbits.RD1=0;
    delay(1);
    row=PORTD;
    row>>=4;
    if((row&0x0F)!=0x0F)
    {
        val=knowkey(4,row);
        PORTDbits.RD1=1;
        return val;
    }
    PORTDbits.RD2=0;
    delay(1);
    row=PORTD;
    row>>=4;
    if((row&0x0F)!=0x0F)
    {
        val=knowkey(8,row);
        PORTDbits.RD2=1;
        return val;
    }
    PORTDbits.RD3=0;
    delay(1);
    row=PORTD;
    row>>=4;
    if((row&0x0F)!=0x0F)
    {
        val=knowkey(12,row);
        PORTDbits.RD3=1;
        return val;
    }
    }
}
void main()
{
    char key;
    TRISB=0;
    TRISC=0;
    TRISD=0xF0;
    initLCD();
    setline(1);
    displaystring("Press key");
    while(1)
    {
        setline(2);
        displaystring("Pressed key= ");
        key=getkey();
        sendata(key);
   }

}