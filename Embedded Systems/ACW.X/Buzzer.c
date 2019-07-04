/* 
 * File:   Buzzer.c
 * Author: ieaun
 *
 * Created on 05 December 2018, 21:31
 */

#include <stdio.h>
#include <stdlib.h>
#include<pic.h>              //include MCU head file
#include <xc.h>
#include "Buzzer.h"

#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial 
//Buzzer
#define  buz  RE1                              //define voice control I/O   

/*
 * 
 */
//**************************************************BUZZER***********************************************************
//hardware request:SW S10 the third bit set ON,the others set OFF  
//
//THE configure of MCU,watchdog OFF,electrify delay OPEN,power down check OFF,                                  
//LOW power programme OFF,encrypt,4M crystal HS surge.  
//------------------------------------------------------                                                        
//delay function                                                                                                
void sounddelay0(unsigned char delay_count)                                                                     
{                                                                                                               
  unsigned char i;                            //define circle variable                                          
  for(i=delay_count;i>0;i--);                 //frequency choose delay time                                     
}                                                                                                               
                                                                                                                
//------------------------------------------------------                                                        
//voice function                                                                                                
void sound200ms()                                                                                               
{                                                                                                                
  unsigned char fre_repeat,s_max,s_min,i,j;                                                                     
                                                                                                                
//the same frequency repeat times,the highest frequency,the lowest frequency,circle variable i,j                
  fre_repeat=4;                              // the same frequency circle four times                            
  s_max=0x93;                                //voice highest frequency                                          
  s_min=0x47;                                //voice lowest frequency                                           
  for(i=s_max-s_min;i>0;i--)                 //OUTPUT voice inside highest frequency and lowest frequency       
     {                                                                                                          
         for(j=fre_repeat;j>0;j--)           //every voice circle four times                                    
            {                                                                                                   
                buz=1;                       //OUTPUT voice                                                     
                sounddelay0(s_min+i);        //delay some time                                                  
                buz=0;                       //close voice                                                      
                sounddelay0(s_min+i);        //delay some time                                                  
             }                                                                                                  
      }                                                                                                         
}                                                                                                                  
                                                                                                                
//-------------------------------------------------------                                                       
//main function                                                                                                 
void BuzzerActivate()                                                                                                     
{                                                                                                               
   TRISE=0;                                  //set E PORT OUTPUT                                                
   sound200ms();                             //call voice function  
   TRISE=1;    
}      
