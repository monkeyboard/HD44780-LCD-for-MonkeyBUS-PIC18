#include "lcd.h"

void LCD_PulseEnable(void)
{
	// NOTE: Enable pulse width greatly depending on the different LCD module.

	LCD_EN=1;					// Set enable high
	Delay1KTCYx(10);			// Delay1KTCYx(10)=0.83ms 

	LCD_EN=0;					// Set enable low
	Delay1KTCYx(10);			// Delay1KTCYx(10)=0.83ms
}

void LCD_PrintStr(char *str)
{
	while (*str !=0)
	{
		LCD_WriteByte(DATA, *str);
		str++;
	}
}

void LCD_Init(void)
{
	LCD_Init_Pin();

	Delay10KTCYx(24);			// Delay 20ms for LCD to power up
	LCD_RS =0;					// Set command mode

	LATC =0b00110000;			// Function Set

	LCD_PulseEnable();
	Delay10KTCYx(6);			// Delay 5ms	
	
	LCD_PulseEnable();			
	Delay1KTCYx(3);				// Delay 250us

	LCD_PulseEnable();			
	Delay1KTCYx(3);				// Delay 250us

	LATC = 0b100000;			// Set 4 bit interface
	LCD_PulseEnable();			
	Delay1KTCYx(3);				// Delay 250us

	LCD_WriteByte(COMMAND, 0x28);	// 4 bit mode, 2 lines, 5 x 8 character
	LCD_WriteByte(COMMAND, 0x0c);	// DB3=1, DB2=D, DB1=C, DB0=B, D=Display On, C=Cursor Off, B=Blink Off
	LCD_WriteByte(COMMAND, 0x06);	// Entry Mode set DB2=1, DB1=I/D, DB0=S,I/D=Increment, S=Shift Off  
	LCD_WriteByte(COMMAND, 0x01);	// Clear Display
	//LCD_BL=1;
}

void LCD_WriteByte(unsigned char reg, unsigned char data)
{
	//LATC &=0b100;							// setting PORTC latch to 0
	LATC=0;
	LCD_RS=reg;						// configure LCD RS as command / data
	LCD_EN=0;						// setting LCD enable pin low
	LATC |= (data & 0b11110000);	// data high nibble			
	LCD_PulseEnable();				
 
	//LATC &=0b100;							// setting PORTC latch to 0
	LATC=0;
	LCD_RS=reg;						// configure LCD RS as command / data
	LCD_EN=0;						// setting LCD enable pin low
	LATC |= (data << 4);			// data low nibble moved to PORTC high nibble
	LCD_PulseEnable();

}
	

