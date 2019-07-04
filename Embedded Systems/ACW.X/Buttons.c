/* 
 * File:   Buttons.c
 * Author: ieaun
 *
 * Created on 05 December 2018, 12:11
 */

#include <stdio.h>
#include <stdlib.h>
#include<pic.h>              //include MCU head file
#include <xc.h>
#include "Buttons.h"

#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial 

void scan(); 

int  result;
unsigned char display_number_button[10] ={'0','1', '2', '3', '4', '5', '6', '7', '8','9'};
int ActiveSet_Buttons=0; //if 1= Time, if 2=Date, if 3=Temp, if 4=Trigger Temp, else = no entry

int NoPressed = 99;

_Bool busy;                         //busy flag  

void keymatrix();
void  delayKey();              //delay function declare
void  initkey();               //I/O PORT initialize function declare
void  scan();               //key scan function declare
void  display_key(int x);       //display function declare

//hardware request:SW S4 ON ,S6 ON,S5 5-6 bits ON,the others OFF
//---------------------------------------------------
                             //main program  
void keymatrix(int *ButtonPressed_,int *ActiveSet)
{
 // while(1)                   //circle work                        
 //   {                                                             
      initkey();                //call initialize subprogram         
      scan();                //call key scan subprogram           
      display_key(result);       //call result display subprogram   
      
      *ButtonPressed_= NoPressed;
      *ActiveSet=ActiveSet_Buttons;
      NoPressed=99;
 //   }
 }
 
//---------------------------------------------------
//initialize function
 void initkey() 
 {
  ADCON1=0X07;                // set A PORT general I/O PORT                  
  TRISA=0X0f;                 //A PORT low 4 bits INPUT,high 4 bits OUTPUT    
  TRISC=0XF0;                 //C PORT high 4 bits INPUT,low 4 bits OUTPUT    
//  TRISD=0X00;                 //set D PORT OUTPUT                             
 // PORTA=0XFF;                                                                 
//  PORTD=0XFF;                 //clear all display                             
 }

//---------------------------------------------------
//key scan program
void scan()
{
 PORTC=0XF7;                 //C3 OUTPUT low,the other 3 bits OUTPUT high                      
 asm("nop");                 //delay                                                           
 result=PORTC;               //read C PORT                                                     
 result=result&0xf0;         //clear low 4 bits                                                
 if(result!=0xf0)            //judge if high 4 bits all 1(all 1 is no key press)               
   {                                                                                           
     result=result|0x07;     //no,add low 4 bits 0x07 as key scan result                       
   }                                                                                           
 else                        //yes,change low 4 bits OUTPUT, judge if a key press again        
   {                                                                                           
   PORTC=0XFb;               //C2 OUTPUT low,the other 3 bits OUTPUT high                      
   asm("nop");               //delay                                                           
   result=PORTC;             //read C PORT                                                     
   result=result&0xf0;       //clear low 4 bits                                                
   if(result!=0xf0)          //judge if high 4 bits all 1(all 1 is no key press)               
     {                                                                                         
     result=result|0x0b;     //no,add low 4 bits 0x0b as key scan result                       
     }                                                                                         
   else                      //yes,change low 4 bits OUTPUT, judge if a key press again        
       {                                                                                       
       PORTC=0XFd;           //C1 OUTPUT low,the other 3 bits OUTPUT high                      
       asm("nop");           //delay                                                           
       result=PORTC;         //read C PORT                                                     
       result=result&0xf0;   //clear low 4 bits                                                
       if(result!=0xf0)      //judge if high 4 bits all 1(all 1 is no key press)               
        {                                                                                      
        result=result|0x0d;  //no,add low 4 bits 0x0d as key scan result                       
        }                                                                                      
       else                  //yes,change low 4 bits OUTPUT, judge if a key press again        
          {                                                                                    
          PORTC=0XFe;        //C0 OUTPUT low,the other 3 bits OUTPUT high                      
          asm("nop");        //delay                                                           
          result=PORTC;      //read C PORT                                                     
          result=result&0xf0;//clear low 4 bits                                                
          if(result!=0xf0)   //judge if high 4 bits all 1(all 1 is no key press)               
            {                                                                                  
             result=result|0x0e;//no,add low 4 bits 0x0e as key scan result                    
            }                                                                                  
          else               //yes,all key scan end,no key press,set no key press flag         
            {                                                                                  
             result=0xff;    //key scan result 0xff as no key press flag                       
            }   
          }      
      }
   }
 }

//----------------------------------------------------------
//display program

void display_key(int x)
  {
   switch(result)                 
      {
       case 0x7d:
                 NoPressed=7;break;  //K24   7
       case 0x7b: 
                 NoPressed=8;break;   //K23   8
       case 0x77:
                 NoPressed=9;break;    //K22  9
       case 0xbd:
                 NoPressed=4;;break;    //K20   4
       case 0xbb:
                 NoPressed=5;break;     //K19   5
       case 0xb7:
                 NoPressed=6;break;   //K18    6
       case 0xdd:
                 NoPressed=1;break;    //K16   1
       case 0xdb:
                 NoPressed=2;break;   //K15     2
       case 0xd7:
                 NoPressed=3;break;    //K14    3
       case 0xeb:
                 NoPressed=0;break;     //K11     0
       case 0xe7:
                 NoPressed=55; break;    //K10  //Silencer
       case 0xed:
                 break;      //K12
       case 0x7e:
                 ;break;      //K25  
       case 0xbe:
                 ActiveSet_Buttons=3;NoPressed=98; break;  //K21     Trigger temp  
       case 0xde:
                 ActiveSet_Buttons=2;NoPressed=98;break;   //K13   Date
       case 0xee:
                 ActiveSet_Buttons=1;NoPressed=98; break;   //K17       Time   
       case 0xff:
                 NoPressed=99;break;      //no key press
   }
}

//------------------------------------------------------------------
//delay program
//void  delayKey()              //delay program 
//    {
//    int i;                 //define integer variable
//     for(i=0x100;i--;)
//     {;}     //delay
//    }


