/*
 * MC2.c
 *
 * Created: 8/23/2021 3:00:20 AM
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

int main(void)
{
	DDRA&=~(1<<0); //Set PA0 as input
	DDRA&=~(1<<1); //Set PA1 as input
	UART_init();   // initialize UART driver
	LCD_init();   // initialize LCD driver
	
	/* Replace with your application code */
	
  while (1)
   {
	LCD_clearScreen(); //Clear LCD
	LCD_displayStringRowColumn(0,0,"Waiting  for"); //Print ( Waiting for ) in LCD first line 
	LCD_displayStringRowColumn(1,0," Question"); //Print ( Question ) in LCD second line 
	
	//////////////////////////////////// Busy Loop ////////////
    if (UART_recieveByte()==Busy_Condition) //Wait until MC2 Choose between Busy or Hungry 
          { // User Choose Busy
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Are You Busy");
	LCD_displayStringRowColumn(1,0,"1.Yes 2.No");
         while ((!(PINA&(1<<0))) && (!(PINA&(1<<1)))){} //Wait until Any Key is Pressed 
			 
	         if (PINA&(1<<0) ) //If first key is pressed 
	                {
		UART_sendByte(Busy_Condition1); //Send to MC1 that key 1 is pressed 
		
                	}
					
	         else if(PINA&(1<<1)) //If second key is pressed 
	               {  
		UART_sendByte(Busy_Condition2); // Send to MC1 that key 2 is pressed 
		
	               }
	
	    } 
	
//////////////////////////////////// Hungry Loop ////////////
      else   //Wait until MC2 Choose between Busy or Hungry 
          {
	           LCD_clearScreen();
	           LCD_displayStringRowColumn(0,0,"Are You Hungry"); //Print On The Screen
	           LCD_displayStringRowColumn(1,0,"1.Yes 2.No");
			   
	            while ((!(PINA&(1<<0))) && (!(PINA&(1<<1)))){} //Wait until Any Key is Pressed 
	       if (PINA&(1<<0) ) //If first key is pressed 
	            {
					
		           UART_sendByte(Hungry_Condition1); //Send to MC1 that key 1 is pressed 
	         	} 
	       else if(PINA&(1<<1)) //If second key is pressed 
	            {
		        
			       UART_sendByte(Hungry_Condition2); //Send to MC1 that key 2 is pressed 
              	}
    }
}
		


}
