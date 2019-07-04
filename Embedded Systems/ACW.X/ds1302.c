//experiment purpose: familiar how to use clock chip DS1302       
//first set time and date:second(08),minute(58),hour(05),day(13),month(01),year(55)   
//six LED display time and date,default display time,differentiate hour and min,min and second with decimal dot 
//when press RB1 not relax,display switch to date.     
//hardware request: SW S9,S5,S6 all ON,S1 the seventh bit ON,the other bits OFF,the other SWS OFF.

#include<pic.h>                        //include MCU head file     
#include <xc.h>
#include "ds1302.h"
#include "MainHead.h"
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial
    

#define i_o   RB4                      //1302I_O           
#define sclk  RB0                      //1302 clock        
#define rst   RB5                      //1302 enable bit   

void  ds_delay();

 unsigned char time_rx;
//  unsigned char time_rx;// @ 0x30;        //define receive reg.
//  static volatile _Bool time_rx7   @ (unsigned)&time_rx*8+7;   //receive reg highest.
//static volatile bit temp0     @ (unsigned)&temp*8+0;

//void port_init();                      //port initilize subroutine.
//void ds1302_init();                    //DS1302 initilize subroutine.
//void set_time();                       //set time subroutine.
//void get_time();                       //get time subroutine.
//void display();                        //display subroutine.
void Insert(int ArrayPos,char Number_To_insert);
void time_write_1(unsigned char time_tx);    //write one byte subroutine.
unsigned char  time_read_1();          //read one byte subroutine.
void ds_delay();                          //delay subroutine.
//define the time: sec,min,hour,day,month,week,year,control word.
char tableds[]={0x00,0x02,0x03,0x10,0x12,0x02,0x18,0x00};
//define the read time and date save table.
char tableds1[7];
//define the display code for display 0-9
const char tableds2[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 
char EasyWayTable[61]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,
                     0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x20,
                     0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x30,
                     0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x40,
                     0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x50,
                     0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x60};
unsigned char display_number_Clock[10] ={'0','1','2','3','4','5','6','7','8','9'};
char Time[6];
char Date[6];
int Time_Date;  //if 0 then time if 1 then date


//----------------------------------------------
//main routine.
void ClockMain(char *Hour1_Temp,char *Hour2_Temp,char *Min1_Temp,char *Min2_Temp,char *Sec1_Temp,char *Sec2_Temp)
  {
   // while(1)
     //   {
          Time_Date=0;
          get_time();                 
          ds_display(); 
          *Hour1_Temp=Time[0];
          *Hour2_Temp=Time[1];
          *Min1_Temp=Time[2];
          *Min2_Temp=Time[3];
          *Sec1_Temp=Time[4];
          *Sec2_Temp=Time[5];     
      //  }
  }

void DateMain(char *Year1_Temp,char *Year2_Temp,char *Month1_Temp,char *Month2_Temp,char *Day1_Temp,char *Day2_Temp)
{
 Time_Date=1;
 get_time(); 
 ds_display();
    *Year1_Temp= Date[0];
    *Year2_Temp= Date[1];
    *Month1_Temp=Date[2];
    *Month2_Temp=Date[3];
    *Day1_Temp =Date[4];
    *Day2_Temp =Date[5]; 
 
}

//---------------------------------------------
//DS1302 initilize.
void ds1302_init()
  {
   sclk=0;                            //pull low clock
   rst =0;                            //reset DS1302
   rst=1;                             //enable DS1302
   time_write_1(0x8e);                //send control command
   time_write_1(0);                   //enable write DS1302
   rst=0;                             //reset
  }

//---------------------------------------------
//set time.
void set_time(int Hour,int Min,int Day_st,int Month_st,int Year_st)
  {
   int i;                             //define the loop counter.
   rst=1;                             //enable DS1302
   time_write_1(0xbe);                //
   
   // set time value to Hour and min
   tableds[1]=EasyWayTable[Min];
   tableds[2]=EasyWayTable[Hour];
   tableds[3]=EasyWayTable[Day_st];
   tableds[4]=EasyWayTable[Month_st];
   tableds[6]=EasyWayTable[Year_st];
   
   for(i=0;i<8;i++)                   //continue to write 8 bytes.
     {
       time_write_1(tableds[i]);        //write one byte
     }
   rst=0;                             //reset
   }

//---------------------------------------------
//get time.
void get_time()
 {
   int i;                             //set loop counter.
   rst=1;                             //enable DS1302
   time_write_1(0xbf);                //
   for(i=0;i<7;i++)                   //continue to read 7 bytes.
     {
        tableds1[i]=time_read_1();      //
     }
    rst=0;                            //reset DS1302
 }

//--------------------------------------------
//write one byte
void time_write_1(unsigned char time_tx)
 {
    int j;                            //set the loop counter.
    for(j=0;j<8;j++)                  //continue to write 8bit
      {
        i_o=0;                        //
        sclk=0;                       //pull low clk
        if(time_tx&0x01)              //judge the send bit is 0 or 1.
          {
            i_o=1;                    //is 1
          }
        time_tx=time_tx>>1;           //rotate right 1 bit.
        sclk=1;                       //pull high clk
       }
      sclk=0;                         //finished 1 byte,pull low clk
  }

//---------------------------------------------
//read one byte.
unsigned char time_read_1()
 {

    time_rx = 0;
   int j;                            //set the loop counter.  
   unsigned char bitmask = 0x01;
   TRISB4=1;                         //continue to write 8bit 
   for(j=0;j<8;j++)                  
      {
        sclk=0;                       //pull low clk                   
       // time_rx=time_rx>>1;           //judge the send bit is 0 or 1. 
        
        if(i_o)time_rx = time_rx | (bitmask << j);//put the received bit into the reg's highest.
        
     //   time_rx=time_rx i_o;                
       sclk=1;                       //pull high clk                 
      }                                                              
    TRISB4=0;                        //finished 1 byte,pull low clk  
    sclk=0;                          
    return(time_rx);                 
  }

//--------------------------------------------
//pin define func
void port_init()
  {
    TRISA=0x00;                     //a port all output
    TRISD=0X00;                     //d port all output
    ADCON1=0X06;                    //a port all i/o
    TRISB=0X02;                     //rb1 input, others output               //open b port internal pull high.
    PORTA=0XFF;               
    PORTD=0XFF;                     //clear all display
   }

//-------------------------------------------
//display
void ds_display()
   {
     int i;                         //define table variable.
     if(Time_Date==1)                     //judge rb1.
       {
          tableds1[0]=tableds1[3];     
          tableds1[1]=tableds1[4];
          tableds1[2]=tableds1[6];
       }
     i=tableds1[0]&0x0f;             //sec's low.
 //    PORTD=tableds2[i];              //send to port d.
 //    PORTA=0x1f;                   //light on sec's low.
     Insert(5,i);
 //    Time[5]=display_number_Clock[i];
     ds_delay();                      //delay some times.
     i=tableds1[0]&0xf0;             //sec's high
     i=i>>4;                       //rotate right for 4 bits.
//     PORTD=tableds2[i];              //send to port d.    
 //    PORTA=0x2f;                   //light on sec's high.
     Insert(4,i);
//     Time[4]=display_number_Clock[i];
     ds_delay();                      //delay some times.  
     
     i=tableds1[1]&0x0f;             //min's low.                 
//     PORTD=tableds2[i]&0x7f;         //send to port d.            
//     PORTA=0x37;                   //light on min's low. 
     Insert(3,i);
 //    Time[3]=display_number_Clock[i];
     ds_delay();                      //delay some times.          
     i=tableds1[1]&0xf0;             //min's high                 
     i=i>>4;                       //rotate right for 4 bits.   
//     PORTD=tableds2[i];              //send to port d.            
//     PORTA=0x3b;                   //light on min's high. 
     Insert(2,i);
//     Time[2]=display_number_Clock[i];
     ds_delay();                      //delay some times.          

     i=tableds1[2]&0x0f;             //hour's low.                 
//     PORTD=tableds2[i]&0x7f;         //send to port d.            
//     PORTA=0x3d;                   //light on hour's low. 
     Insert(1,i);
//     Time[1]=display_number_Clock[i];
     ds_delay();                      //delay some times.          
     i=tableds1[2]&0xf0;             //hour's high                 
     i=i>>4;                       //rotate right for 4 bits.   
//    PORTD=tableds2[i];              //send to port d.            
//     PORTA=0x3e;                   //light on hour's high. 
     Insert(0,i);
 //    Time[0]=display_number_Clock[i];
     ds_delay();                      //delay some times.    
   }

void Insert(int ArrayPos,char Number_To_insert)
{
     if(Time_Date==1)
     {
      Date[ArrayPos]=display_number_Clock[Number_To_insert];
     }
     if(Time_Date==0)
     {
     Time[ArrayPos]=display_number_Clock[Number_To_insert];
     }

}

//------------------------------------------------------------------
//delay
void  ds_delay()              //
    {
     int i;                 //define variable
     for(i=0x64;i--;)
     {;}     //delay
    }
