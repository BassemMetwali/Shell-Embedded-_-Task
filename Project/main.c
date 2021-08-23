/*
 * Task.c
 *
 * Created: 8/23/2021 2:57:10 AM
 * Author : bassem
 */ 


#include "uart.h"
#include "lcd.h"
#include <util/delay.h>
#define Busy_Condition 0X10
#define Hungry_Condition 0X11
#define Busy_Condition1 0X12
#define Busy_Condition2 0X14
#define Hungry_Condition1 0X13
#define Hungry_Condition2 0X15
#define F_CPU 16000000UL 
int main(void)
{
	DDRA&=~(1<<0)&~(1<<1); //make PA0 & PA1 as inputs
	UART_init(); // initialize UART driver
	LCD_init(); // initialize LCD driver
    /* Replace with your application code */
    
		LCD_displayStringRowColumn(0,0,"Choose question:");
		LCD_displayStringRowColumn(1,0,"1.Busy 2.Hungry");
		while (1)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Choose question:");
			LCD_displayStringRowColumn(1,0,"1.Busy 2.Hungry");
			while ((!(PINA&(1<<0))) && (!(PINA&(1<<1)))){}
		if (PINA & (1<<0)) //Busy
		{
			UART_sendByte(Busy_Condition);
			_delay_ms(500);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Asked if Busy");
				LCD_displayStringRowColumn(1,0,"Waiting Answer"); 
				
				if (UART_recieveByte() == Busy_Condition1)
				{ LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Yes I am");
					_delay_ms(2000);
				}
					else 
					{ 
						LCD_clearScreen();
						LCD_displayStringRowColumn(0,0,"No I am Not");
						_delay_ms(2000);
					}		
		}
		else  //Hungry
		{
			UART_sendByte(Hungry_Condition);
			_delay_ms(500);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Asked if Hungry");
			LCD_displayStringRowColumn(1,0,"Waiting Answer");
			
			if (UART_recieveByte() == Hungry_Condition1)
			{ LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Yes I am");
				_delay_ms(2000);
			}
			else
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"No I am Not");
				_delay_ms(2000);
			}
		}
}
}

