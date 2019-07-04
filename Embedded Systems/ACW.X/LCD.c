/* 
 * File:   LCD.c
 * Author: ieaun
 *
 * Created on 05 December 2018, 12:11
 *///Tip:Please open RA4 pull UP, will S10'S NO.4 in the "on"   ,Jump J14 all connect,

#include <stdio.h>
#include <stdlib.h>
#include<pic.h>                        //include MCU head file     
#include <xc.h>
#include "LCD.h"
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial

//LCD
#define  rs  RA5                    //COMMNAD/DATA SELECT            
#define  rw  RA4                    //READ/WRITE SELECT              
#define  e   RA3                    //ENABLE SIGNAL                  
#define  psb RA2                    //PARALLEL/SERIAL SELECT£¨H/L£©  
#define  rst RA0                    //RESET SIGNAL                   
#define  nop()  asm("nop")          //nop func

void delay();
void send_i(unsigned char x);
void wr_zb();
void clear_p();

unsigned int lcd_x;                //X address    
unsigned int lcd_y;                //Y address  
_Bool busy;                         //busy flag  

//Trouble Variables 

void lcd_init()
{
  TRISA=0X00;                       //A port as output         
  TRISD=0X00;                       //d port as output         
  ADCON1=0X06;                      //A port as ordinary i/o   
    
  rst=0;                         //reset LCD
  delay();                        
  rst=1;                         //LCD normal work.
  nop();        
  psb=1;                         //8 bit as parrallel.
  send_i(0x30);                  //basic operation instruction
  send_i(0x01);                  //off display  
  send_i(0x06);                  //set the cursor's moving direction.
  send_i(0x0c);                  //on display,off cursor,off blink
  
  clear_p();
  wr_zb();  
}

//-------------------------------------------
//INDIVIDUAL NUMBERS.
void han_Number(int DisplayPos,int NumberSelected)
{
  send_i(DisplayPos);                     //set display position
  send_d(NumberSelected);
}

//Display an array of text for date/time/trig temp/temp
void han_Display(int DisplayPos,const unsigned char *Data)
{
  send_i(DisplayPos);                     //set display position
  qushu(0x5,Data);        //get data from table
}
//display setting.
void wr_zb()
{
  send_i(lcd_y);
  send_i(lcd_x);
}

//-------------------------------------------
//clear screen
void clear_p()
{
  send_i(0x1);                   //clear all
  send_i(0x34);                  //extend.
  send_i(0x30);                  //basic
}

//-------------------------------------------
//display the next.
void send_d(unsigned char x)
{
   chk_busy();                  //check busy.
   rs=1;                        //data not commnad.  
   rw=0;                        //write not read.    
   PORTD=x;                     //data to bus.       
   e=1;                         //enable.            
   nop();
   nop();
   nop();                       
   e=0;                         //disable.
}

//--------------------------------------------
//send command.
void send_i(unsigned char x)
{
   chk_busy();                   //check lcd if busy. 
   rs=0;                         //data not commnad.  
   rw=0;                         //write not read.    
   PORTD=x;                      //data to bus.       
   e=1;                          //enable.            
   nop();
   nop();
   nop();
   e=0;                         //disable.
}

//-------------------------------------------
//check lcd busy.
void chk_busy()
{  
   busy=1;                      //set busy signal                   
   TRISD=0XFF;                  //change the bus to input.          
   rs=0;                        //command not data.                 
   rw=1;                        //read not write.                   
   while(busy)                  
      {
         nop();
         nop();
         nop();
         e=1;                   //enable.
         nop();
         nop();
         nop();
         if(!RD7) busy=0;       //
         nop();
         nop();
         nop();
         e=0;                   //DISABLE.
      }
   e=0;                         //DISABLE.
   TRISD=0X00;                  //bus as output.
 }

void qushu(int counts,const unsigned char *ps)
{
  int i;                         //define loop count.
  for(i=counts;i>0;i--)          //
     {  
        send_d(*ps);             //
        delay();                 //
        ps++;                    //get next.
     }
}

//-------------------------------------------
//delay
void delay()
{
    int i;
    for(i=0;i<5000;i++)
       {;}
}


                                              

