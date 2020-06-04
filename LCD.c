ROLL NO. 304375

#include <p18f4550.h>
#include "lcd.h"

#define LCD_EN LATCbits.LC1
#define LCD_RS LATCbits.LC0
#define LCDPORT LATB          //We can use PORTB instead of LATB


void delay(unsigned int time)
{
 unsigned int i, j;

    for(i=0; i<time; i++)
    {
            for(j=0;j<100;j++);
    }
}


void SendInstruction(unsigned char command)
{
    //set RS pin low
     LCD_RS = 0;                        // RS low for COMMAND
     delay(10);
    //Set EN pin HIgh
     LCD_EN = 1;                        // EN High
     delay(10);
    //Set Data on pins
     LCDPORT = command; 		// Send COMMAND
     delay(10);
    //set EN pin Low
     LCD_EN = 0;                        // EN Low; COMMAND sampled by LCD on falling edge
     delay(10);
}

void SendData(unsigned char lcddata)
{

    //set RS pin low
     LCD_RS = 1;                        // RS HIGH for DATA
     delay(10);
    //Set EN pin HIgh
     LCD_EN = 1;        		// EN High
     delay(10);
    //Set Data on pins
     LCDPORT = lcddata; 		// Send DATA
     delay(10);
    //set EN pin Low
     LCD_EN = 0;                	// EN Low; DATA sampled by LCD on falling edge
     delay(10);
}

void SetLineNumber(unsigned char linenum)
{
    if(linenum == 1)
    {
      SendInstruction( SETDDRAMADDR | 0x00 );		// set ddram address as 0x00
    }
    else
    {
      SendInstruction( SETDDRAMADDR | 0x40 );		// set ddram address as 0x40
    }
}

void SetAddress(unsigned char memory, unsigned char address )
{
    address &= 0x7F;

    if(memory == DDRAM)
    {
      SendInstruction( SETDDRAMADDR | address );
    }
    else
    {
      SendInstruction( SETCGRAMADDR | address );
    }
}

void BlinkDisplay(void)
{
    SendInstruction( DISPONOFFCTRL );
    delay(5000);
    SendInstruction( DISPONOFFCTRL | DISPLAY_ON | CURSOR | BLINKCHAR_ON );
    delay(9000);
}

void ShiftDisplay(unsigned char direction, unsigned char clicks)
{
unsigned int i;

    if(direction == RIGHTSHIFT)
    {
      for(i = 0; i < clicks ; i++)
      {
       SendInstruction( DISPCURSHIFT | SHIFTRIGHT );
      }
    }
    else
    {
      for(i = 0; i < clicks ; i++)
      {
       SendInstruction( DISPCURSHIFT );
      }
    }
}

void ClearDisplay(void)
{
  SendInstruction(CLEARDISPLAY);
}


void InitLCD(void)
{
    TRISB = 0x00; //set data port as output
    TRISCbits.RC0 = 0; //EN pin
    TRISCbits.RC1 = 0; // RS pin

    //initialise the lcd : function set command : 8 bit interface : 5ms wait
    SendInstruction( FUNCTIONSET | FS_DATALENGTH );
    delay(5);
    //initialise the lcd : function set command : 8 bit interface : 100us wait
    SendInstruction( FUNCTIONSET | FS_DATALENGTH );
    delay(1);
    //initialise the lcd : function set command : 8 bit interface : set interface , line numbers and font size
    SendInstruction( FUNCTIONSET | FS_DATALENGTH | FS_LINES2 );  // set interface 8 bit, no of lines =2 and character font 5x7
    //display off
    SendInstruction(DISPONOFFCTRL);
    //clear display
    SendInstruction(CLEARDISPLAY);
    //entry mode set : increment / decrement
    SendInstruction(ENTRYMODESET | ENTRYMODESET_INC);	//set as increment of address
    //display on : set cursor and blinking
    SendInstruction(DISPONOFFCTRL | DISPLAY_ON | CURSOR );	// display on and cursor blinking on
}
/********************************************************************************************************************/

unsigned char DISP_STR[]={'2','x','1','6','C','h','a','r','a','c','t','e','r','L','C','D'};
unsigned char *String =" Micro-PIC Board";

void main(void)
{
 int i;

 InitLCD();
 ClearDisplay();
 SetLineNumber(1);
 for(i=0;i<16;i++)                      //Display "2x16CharacterLCD"
 {
  SendData(DISP_STR[i]);
 }
 SetLineNumber(2);
 while(*String)                         //Display " Micro-PIC Board"
 {
  SendData(*String);
  String++;
 }

 while(1)                               //Blink Display forever
    BlinkDisplay();
}
