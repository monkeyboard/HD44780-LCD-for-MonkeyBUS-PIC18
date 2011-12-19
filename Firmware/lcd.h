#include "HardwareProfile.h"
#include "delays.h"

#define	COMMAND		0
#define DATA		1
#define LCD_RS		LATCbits.LATC1
#define LCD_BL		LATCbits.LATC2
#define LCD_EN		LATCbits.LATC3


#define LCD_Init_Pin()	LATC=0;TRISC &= 0; 			// watch this part if you want to use some other PORTC pins for input.		

void LCD_WriteByte(unsigned char reg, unsigned char data);
void LCD_PrintStr(char *str);
void LCD_PulseEnable(void);
void LCD_Init(void);
