/* 
 * File:   Temperature.c
 * Author: ieaun
 *
 * Created on 05 December 2018, 12:12
 */

#include <stdio.h>
#include <stdlib.h>
#include<pic.h>                        //include MCU head file     
#include <xc.h>
#include "Temperature.h"
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial

//Thermo
#define  uch unsigned char                   //                                          
# define DQ RA0                              //define 18B20 data PORT                    
# define DQ_DIR TRISA0                       //define 18B20 D PORT direct register       
# define DQ_HIGH() DQ_DIR =1                 //set data PORT INPUT                       
# define DQ_LOW() DQ = 0; DQ_DIR = 0         //set data PORT OUTPUT                      
 unsigned char  TLV=0 ;                      //temperature high byte                     
 unsigned char  THV=0;                       //temperature low byte                      
 unsigned char TZ=0;                         //temperature integer after convert         
 unsigned char TX=0;                         //temperature decimal  after convert        
 unsigned int wd;                            //temperature BCD code  after convert                                                                                              
unsigned char shi;                           //integer ten bit                           
unsigned char ge;                            //integer Entries bit                       
unsigned char shifen;                        //ten cent bit                              
unsigned char baifen;                        //hundred cent bit                          
unsigned char qianfen;                       //thousand cent bit                         
unsigned char wanfen;                        //myriad cent bit                           
unsigned char tablethermo[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 

uch read_byte(void);
void write_byte(uch val);
int TempValues[3];

//**************************************************Thermo***********************************************************                                                                                                               
 //-----------------------------------------------------------
//delay function              
void delayThermo(char x,char y) 
{
  char z;
  do{
      z=y;
      do{;}while(--z);
     }while(--x);
 }                                                                                
                                                                                                                        
//--------------------------------------------------                                                                    
//display function
void displayThermo()
{                          
 TempValues[0]=shi;
 delayThermo(10,70);                                                                           
 TempValues[1]=ge;
 delayThermo(10,70);                                                                           
 TempValues[2]=shifen;
 delayThermo(10,70);                                                                           
}

//------------------------------------------------
//system initialize function           
void initThermo()
{
  ADCON1=0X07;                                //set A PORT general data PORT   
  TRISA=0X00;                                 //set A PORT direct OUTPUT       
  TRISD=0X00;                                 //set D PORT direct OUTPUT       
}

//-----------------------------------------------
//reset DS18B20 function   
void reset(void)
{
  char presence=1;
  while(presence)
  { 
    DQ_LOW() ;                                //MAIN MCU PULL LOW                                                                       
    delayThermo(2,70);                              //delay 503us                                                                             
    DQ_HIGH();                                //release general line and wait for resistance pull high general line and keep 15~60us    
    delayThermo(2,8);                               //delay 70us                                                                              
    if(DQ==1) presence=1;                     // not receive responsion signal,continue reset                                           
    else presence=0;                          //receive responsion signal                                                               
    delayThermo(2,60);                              //delay 430us                                                                             
   }
  }

//-----------------------------------------------
//write 18b20 one byte function     
void write_byte(uch val)
{
 uch i;
 uch temp;
 for(i=8;i>0;i--)
 {
   temp=val&0x01;                             //shift the lowest bit                   
   DQ_LOW();                                                                           
   NOP();                                                                              
   NOP();                                                                              
   NOP();                                                                              
   NOP();                                                                              
   NOP();                                     //pull high to low,produce write time    
   if(temp==1)  DQ_HIGH();                    //if write 1,pull high                   
   delayThermo(2,7);                                //delay 63us                             
   DQ_HIGH();                                                                          
   NOP();                                                                              
   NOP();                                                                              
   val=val>>1;                                //right shift a bit                      
  }
}

//------------------------------------------------
//18b20 read a byte function  
uch read_byte(void)
{
 uch i;
 uch value=0;                                 //read temperature         
 static _Bool j;
 for(i=8;i>0;i--)
 {
   value>>=1; 
   DQ_LOW();
   NOP();
   NOP();
   NOP();
   NOP();
   NOP();
   NOP();                                    //6us              
   DQ_HIGH();                                // pull high       
   NOP();                                                       
   NOP();                                                       
   NOP();                                                       
   NOP();                                                       
   NOP();                                   //4us               
   j=DQ;                                                        
   if(j) value|=0x80;                                           
   delayThermo(2,7);                              //63us              
  }
  return(value);
}

//-------------------------------------------------
//start temperature convert function   
void get_temp()
{ 
int i;
DQ_HIGH();
reset();                              //reset,wait for  18b20 responsion                                                                                                               
write_byte(0XCC);                     //ignore ROM matching                                                                                                                            
write_byte(0X44);                     //send  temperature convert command                                                                                                              
for(i=20;i>0;i--)                                                                                                                                                                      
    {                                                                                                                                                                                  
                                                                                                                                                                                       
        displayThermo();                    //call some display function,insure the time of convert temperature                                                                              
    }                                                                                                                                                                                  
reset();                              //reset again,wait for 18b20 responsion                                                                                                          
write_byte(0XCC);                     //ignore ROM matching                                                                                                                            
write_byte(0XBE);                     //send read temperature command                                                                                                                  
TLV=read_byte();                      //read temperature low byte                                                                                                                      
THV=read_byte();                      //read temperature high byte                                                                                                                     
DQ_HIGH();                            //release general line                                                                                                                           
TZ=(TLV>>4)|((THV<<4)&(0X3f));            //temperature integer                                                                                                                            
TX=TLV<<4;                            //temperature decimal                                                                                                                            
if(TZ>100) TZ/100;                    //not display hundred bit                                                                                                                        
ge=TZ%10;                     //integer Entries bit                                                                                                                            
shi=TZ/10;                    //integer ten bit                                                                                                                                
wd=0;                                
if (TX & 0x80) wd=wd+5000;
if (TX & 0x40) wd=wd+2500;
if (TX & 0x20) wd=wd+1250;
if (TX & 0x10) wd=wd+625;                //hereinbefore four instructions are turn  decimal into BCD code                         
shifen=wd/1000;                          //ten cent bit                                                                           
baifen=(wd%1000)/100;                    //hundred cent bit                                                                       
qianfen=(wd%100)/10;                     //thousand cent bit                                                                      
wanfen=wd%10;                            //myriad cent bit                                                                        
NOP();                                                                                                                            
}                                                                                                                                 

//--------------------------------------------------
//main function    
void mainThermo(int *Tens_Temp,int *Ones_Temp,int *Decimals_Temp )
{   
       initThermo();                       //call system initialize function                                                                                                                                                                                                                                                                                                                    
       get_temp();           //call temperature convert function                                                                                                                                   
       displayThermo();                //call display function    
       unsigned char display_number[10] ={'0','1','2','3','4','5','6','7','8','9'}; //so lcd can display char values rather than integer
       *Tens_Temp= display_number[TempValues[0]]; 
       *Ones_Temp= display_number[TempValues[1]];
       *Decimals_Temp= display_number[TempValues[2]];
}                                                                                                                                                                                                  
   
                   