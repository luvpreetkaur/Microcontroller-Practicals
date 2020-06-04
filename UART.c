//Name: Luvpreet Kaur
//Roll no:3043338

#include<stdio.h>
#include "UART.h"


void UartInit(unsigned int baudrate)
{
	unsigned int FDiv;
	PINSEL0 |= 0x00000050;
	PCONP |= 1<<3;
	U0LCR = 0x83;
	U0FDR = 0x10;						// Line control register :DLAB=1 ; 8 bits ; 1 stop bit ; no parity
	FDiv = (18000000 / 16 ) / baudrate ; //
	U0DLM = FDiv /256;					//0x00;
	U0DLL = FDiv %256;					//0x97;
	U0LCR = 0x03;						// Line control register :DLAB=0 ; 8 bits ; 1 stop bit ; no parity
	U0TER = 0x80;
}

int UART_GetChar(void)
{
	while(!(U0LSR & 0x1));
return(U0RBR);
}

int UART_PutChar(unsigned char Ch)
{
 if (Ch == '\n')  {
    while (!(U0LSR & 0x20));
    U0THR = 0x0D;                          /* output CR */
}

  while(!(U0LSR & 0x20));
return( U0THR = Ch);
}


int fputc(int ch, FILE *f) {
  return (UART_PutChar(ch));
}

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
  
