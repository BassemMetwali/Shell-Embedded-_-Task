/*
 * Task.c
 *
 * Created: 8/23/2021 2:57:10 AM
 * Author : bassem
 */  

#include "uart.h"
#include "lcd.h"
#include <util/delay.h>
// Conditions For Keys when pressed
#define Busy_Condition 0X10 // When Key pressed for Busy Loop
#define Hungry_Condition 0X11 //When key Pressed for Hungry Loop
#define Busy_Condition1 0X12 //Yes ,Iam Busy
#define Busy_Condition2 0X14 //No, Iam Not
#define Hungry_Condition1 0X13//Yes ,Iam Hungry
#define Hungry_Condition2 0X15 //No, Iam Not
#define F_CPU 16000000UL 
int main(void)
{
	DDRA&=~(1<<0); //Set PA0 as input
	DDRA&=~(1<<1); //Set PA1 as input
	UART_init();   // initialize UART driver
	LCD_init();   // initialize LCD driver
	
	/* Replace with your application code */
	
		LCD_displayStringRowColumn(0,0,"Choose question:"); //Print ( Choose Question ) in LCD first line 
		LCD_displayStringRowColumn(1,0,"1.Busy 2.Hungry");  //Print ( 1.Busy 2.Hungry ) in LCD second line 
		while (1) 
		{
			LCD_clearScreen(); // Clear LCD
		LCD_displayStringRowColumn(0,0,"Choose question:"); //Print ( Choose Question ) in LCD first line
		LCD_displayStringRowColumn(1,0,"1.Busy 2.Hungry");  //Print ( 1.Busy 2.Hungry ) in LCD second line
			while ((!(PINA&(1<<0))) && (!(PINA&(1<<1)))){} //Wait until Any Key is Pressed by (Yes / No) 
		        if (PINA & (1<<0))  // Busy Loop 
		          {
			         UART_sendByte(Busy_Condition); //Send to MC2 that User Choose Busy
			         _delay_ms(500); 
			         LCD_clearScreen();
			         LCD_displayStringRowColumn(0,0,"Asked if Busy");
				     LCD_displayStringRowColumn(1,0,"Waiting Answer"); 
				
				if (UART_recieveByte() == Busy_Condition1) //Wait Until User Choose if he is Busy or Not 
				  {  //User Pressed yes he is Busy
					  LCD_clearScreen(); 
					  LCD_displayStringRowColumn(0,0,"Yes I am");
					  _delay_ms(2000);
				  }
				else 
			    { //User Pressed No he is not Busy
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"No I am Not");
					_delay_ms(2000);
				}		
	 	}
		else  //Hungry Loop 
		  {
			UART_sendByte(Hungry_Condition); //Send to MC2 that User Choose Busy
			_delay_ms(500);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Asked if Hungry");
			LCD_displayStringRowColumn(1,0,"Waiting Answer");
			
			if (UART_recieveByte() == Hungry_Condition1) //Wait Until User Choose if he is Hungry or Not 
			{   //User Pressed Yes he is Hungry
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Yes I am");
				_delay_ms(2000);
			}
			else
			{ //User Pressed No he is not Hungry
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"No I am Not");
				_delay_ms(2000);
			}
		}
}
}

