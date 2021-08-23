/*
 * MC2.c
 *
 * Created: 8/23/2021 3:00:20 AM
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

int main(void)
{
	DDRA&=~(1<<0);
	DDRA&=~(1<<1); //make PA0 & PA1 as inputs
	UART_init(); // initialize UART driver
	LCD_init(); // initialize LCD driver
	/* Replace with your application code */
	
while (1)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Waiting  for");
	LCD_displayStringRowColumn(1,0," Question");
if (UART_recieveByte()==Busy_Condition)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Are You Busy");
	LCD_displayStringRowColumn(1,0,"1.Yes 2.No");
  while ((!(PINA&(1<<0))) && (!(PINA&(1<<1)))){}
	if (PINA&(1<<0) )
	{
		UART_sendByte(Busy_Condition1);
		
	}
	else if(PINA&(1<<1))
	{  
		UART_sendByte(Busy_Condition2);
		
	}
	
	}

else 
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Are You Hungry");
	LCD_displayStringRowColumn(1,0,"1.Yes 2.No");
	while ((!(PINA&(1<<0))) && (!(PINA&(1<<1)))){}
	if (PINA&(1<<0) )
	{
		UART_sendByte(Hungry_Condition1);
		
	}
	else if(PINA&(1<<1))
	{
		UART_sendByte(Hungry_Condition2);
		
	}
	
}
}
		


}
