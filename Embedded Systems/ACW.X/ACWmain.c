/* 
 * File:   ACWmain.c
 * Author: ieaun
 *
 * Created on 29 November 2018, 12:04
 */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include "ds1302.h"
#include "Buttons.h"
#include "LCD.h"
#include "Buzzer.h"
#include "Temperature.h"

#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial


unsigned char display_SetTime[7] ={'T', 'I', 'M', 'E',':'};
unsigned char display_SetDate[7] ={'D', 'A', 'T', 'E',':'};
unsigned char display_SetTriggerTemp[7] ={'T','R','I','G',':'};

void Nextday();
void CalculateDate();
void GetWeekDay();
void CalculateTime();
void SetTimeMethod();
void BiggerThanX(int NumberChars);
void ArrayReset(int ChosenArray);
void GetValue(char ButtonNO);
void han_Display_Results();
void main();
void EnterData();
//
//*************Global Variables*********************************      
//The numbers 0-9 in char form.
unsigned char display_number[10] ={'0','1','2','3','4','5','6','7','8','9'};

char AllValues[3][7];             //Holds all values AllValues[ActiveSet][]
int ActiveSet=0; //if 1= Time, if 2=Date, if 3=Temp, if 4=Trigger Temp, else = no entry
int ButtonPressed;  // Stores which button has been pressed 3g 55 or any number other than 99, if 99 no button pressed

int CurrentPosValue=0;      // current pos in value eg first value of temp/trig/time/date
_Bool FinishedSet;       //if =1 then not finished setting 
_Bool Silencer=0; char letter='L';// if S= silent L=Loud

char Heating_Letter=' '; //holds * if temp bellow trigger / holds Real temperature for comparison

int Year_ds,Month_ds,Day_ds = 0; //holds data to be sent to ds1302 containing the date info
_Bool ResetTime_date = 0;       //0= reset needed, 1 = not needed

int Hour=25,Min=0; //Stores current time

char weekDay[3]; 
int Year_ds_Previous=0;

 
void main()
  {      
      lcd_init();ds1302_init();port_init();initThermo();initkey();      
      ArrayReset(0);ArrayReset(1);ArrayReset(2); 
      han_Display_Results(); 
      while(1)
      {   
         ActiveSet=0;
         //if time is set then activate clock
         if (AllValues[0][0]!=0x3f && AllValues[1][0]!='Y')
         {
             if (ResetTime_date==0)
             {
                 SetTimeMethod();
                 ResetTime_date=1;
             }
          ClockMain(&AllValues[0][0],&AllValues[0][1],&AllValues[0][2],&AllValues[0][3],&AllValues[0][4],&AllValues[0][5]);
          DateMain(&AllValues[1][0],&AllValues[1][1],&AllValues[1][2],&AllValues[1][3],&AllValues[1][4],&AllValues[1][5]);
          CalculateTime();
          CalculateDate();
          Nextday();
         }
               
          //Search for new button press 
         keymatrix(&ButtonPressed,&ActiveSet);  
         //if a button has been pressed
         EnterData();
         //if nothing is happening
         han_Display_Results();  //LCD, Display values for Temp,Trig,Date and Time 
      }
}

void han_Display_Results()
{  
  unsigned char display_Temp[7] ={'T','E','M','P',':',' '}; 
  GetWeekDay();  
  
  mainThermo(&AllValues[3][0],&AllValues[3][1],&AllValues[3][2]);
  
  han_Display(0x80,display_Temp);send_d(' ');send_d(AllValues[3][0]);send_d(AllValues[3][1]);send_d('.');send_d(AllValues[3][2]);if (AllValues[2][0]!=0x3f){send_d('*');}send_d(' ');send_d(Heating_Letter);send_d(' ');if (Silencer==1){letter = 'S';send_d(letter);delay();delay();delay();}if (Silencer==0){letter = 'L';send_d(letter);delay();delay();delay();}
  han_Display(0x90,display_SetTriggerTemp);send_d(' ');send_d(AllValues[2][0]);send_d(AllValues[2][1]);send_d(' ');send_d(' ');send_d('(');send_d(weekDay[0]);send_d(weekDay[1]);send_d(weekDay[2]);send_d(')');
  han_Display(0x88,display_SetDate);send_d(' ');send_d(AllValues[1][0]);send_d(AllValues[1][1]);send_d('/');send_d(AllValues[1][2]);send_d(AllValues[1][3]);send_d('/');send_d(AllValues[1][4]);send_d(AllValues[1][5]);
  han_Display(0x98,display_SetTime);send_d(' ');send_d(AllValues[0][0]);send_d(AllValues[0][1]);send_d(':');send_d(AllValues[0][2]);send_d(AllValues[0][3]);send_d(':');send_d(AllValues[0][4]);send_d(AllValues[0][5]);
  
 if (Hour!=25)
  { 
  if ( (  ((((Hour==6)&&(Min>=30))||(Hour>6)) && ((Hour <22)||(Hour==22)&&(Min<=30))) && (AllValues[1][6]<'6'))     ||     (((((Hour==7)&&(Min>=00))||(Hour>7)) && ((Hour <23)||(Hour==23)&&(Min<=00))) && (AllValues[1][6]>'5'))  )
    {    
     if (((AllValues[3][0]<AllValues[2][0])||((AllValues[3][0]<=AllValues[2][0])&&(AllValues[3][1]<=AllValues[2][1])))&&(AllValues[2][0]!=0x3f))
        {                                                                   
            Heating_Letter='*';
            int W=(AllValues[2][1]-'0')-3;
            if (((AllValues[3][0]<=AllValues[2][0])&&((AllValues[3][1]-'0')<=W))||(AllValues[3][0]<AllValues[2][0]))
                            {
                                if (Silencer!=1)
                                {
                                BuzzerActivate();
                                delay();
                                BuzzerActivate();
                                delay();
                                BuzzerActivate();
                                }
                            }
        }
     else
         Heating_Letter=' ';
    }
}
}

void Nextday()
{
    if((Year_ds!=Year_ds_Previous)&&(Year_ds_Previous!=0))
    {    
//        int Holder= AllValues[1][6]+'0';
//        Holder++;
//        AllValues[1][6]= display_number[Holder];
          switch(AllValues[1][6])
    {         
            case  'W':  break;  
            case  '1': AllValues[1][6]='2'; break;
            case  '2': AllValues[1][6]='3'; break;
            case  '3': AllValues[1][6]='4';break;
            case  '4': AllValues[1][6]='5'; break;
            case  '5': AllValues[1][6]='6'; break;
            case  '6': AllValues[1][6]='7'; break;
            case  '7': AllValues[1][6]='1'; break;
          //  case  '8': AllValues[1][6]='1'; break;
        default :  weekDay[0]='?',weekDay[1]='?',weekDay[2]='?'; break;          
    } 
        
        
    }
}

void CalculateTime()
{
    Hour=Min=0; 
 // convert char to int
   char T1=AllValues[0][0],T2=AllValues[0][1],T3=AllValues[0][2] ,T4=AllValues[0][3];  
    int Hour_Ten = (T1- '0')*10;
    int Hour_digit = T2- '0';
    int Min_Ten =(T3- '0')*10;
    int Min_digit = T4 - '0';
 // add values to get hour and min eg 22  or 01
     Hour = Hour_Ten + Hour_digit;
     Min =  Min_Ten + Min_digit; 
    
}


void EnterData()
{    
    if (ButtonPressed==55) //K10 pressed
     {
      if (letter=='L'){Silencer=1;}
      if (letter=='S'){Silencer=0;}    
      ActiveSet=0;
      ButtonPressed=99;    
    }  
 
    if (ButtonPressed!=99)       //If any button pressed
    { 
      if (ActiveSet!=0)  // Entering new data to be saved (Time,Trig,Date)
      {FinishedSet = 1;       //When finish entering data =0   
      switch (ActiveSet)
      {
              case 1: lcd_init();han_DSet();han_Display(0x90,display_SetTime);break;  //Display "set Time"
              case 2: lcd_init();han_DSet();han_Display(0x90,display_SetDate);break;  //Display "set Date"
              case 3: lcd_init();han_DSet();han_Display(0x90,display_SetTriggerTemp);break;  //Display "set Trig temp"  
      }
      while(FinishedSet == 1) //while still entering Data
       {
       keymatrix(&ButtonPressed,&ActiveSet);    //Search for button press
       if(ButtonPressed<98)   //If button press
            {
            lcd_init();han_Number(0x93,display_number[ButtonPressed]); //Display No Button Pressed
            GetValue(display_number[ButtonPressed]);                   // Set data in variable allvalues[][]
            delay();delay();delay();delay();delay(); lcd_init();
            }
       }
      }
      ActiveSet=0;
    }
}

void GetWeekDay()
{
    switch(AllValues[1][6])
    {         
            case  'W':  weekDay[0]='W',weekDay[1]='K',weekDay[2]='D'; break;  
            case  '1':  weekDay[0]='M',weekDay[1]='O',weekDay[2]='N'; break;
            case  '2':  weekDay[0]='T',weekDay[1]='U',weekDay[2]='E'; break;
            case  '3':  weekDay[0]='W',weekDay[1]='E',weekDay[2]='D'; break;
            case  '4':  weekDay[0]='T',weekDay[1]='H',weekDay[2]='U'; break;
            case  '5':  weekDay[0]='F',weekDay[1]='R',weekDay[2]='I'; break;
            case  '6':  weekDay[0]='S',weekDay[1]='A',weekDay[2]='T'; break;
            case  '7':  weekDay[0]='S',weekDay[1]='U',weekDay[2]='N'; break;
            case  '8':  AllValues[1][6]='1';weekDay[0]='M',weekDay[1]='O',weekDay[2]='N'; break;
        default :  weekDay[0]='?',weekDay[1]='?',weekDay[2]='?'; break;          
    }      
}

void CalculateDate()
{
  
if (AllValues[1][0]!='D')
 {Year_ds_Previous=Year_ds;
 int Day_Ten = (AllValues[1][0]- '0')*10;
 int Day_digit = AllValues[1][1]- '0';
 int Month_Ten =(AllValues[1][2]- '0')*10;
 int Month_digit = AllValues[1][3] - '0';
 int Year_Ten =(AllValues[1][4]- '0')*10;
 int Year_digit = AllValues[1][5] - '0';

  Day_ds   = Day_Ten + Day_digit;
  Month_ds =  Month_Ten + Month_digit;  
  Year_ds  =  Year_Ten + Year_digit; 
 }
}

void SetTimeMethod()
{    
    CalculateTime();
    CalculateDate();
    set_time(Hour,Min,Year_ds,Month_ds,Day_ds);  
    return;
}

void GetValue(char ButtonNO)
{
    switch(ActiveSet)
    {
               case 0: 
                        break;
               case 1: // TIME   
                   AllValues[0][CurrentPosValue] = ButtonNO;
                   ButtonPressed=99;
                   CurrentPosValue++;
                   BiggerThanX(3);     //TODO:make sure to set seconds to 00 when time has been set.            
                        break; 
               case 2: // DATE 
                   AllValues[1][CurrentPosValue] = ButtonNO;
                   ButtonPressed=99;
                   CurrentPosValue++;
                   BiggerThanX(6);
                        break; 
               case 3: // trig TEMP 
                   AllValues[2][CurrentPosValue] = ButtonNO;
                   ButtonPressed=99;
                   CurrentPosValue++;
                   BiggerThanX(1);
                        break; 
    }
}
//------------------------------------------------------
// if out of bounds with pos then reset 
void BiggerThanX(int NumberChars)                            
{
    if (ActiveSet==1 && CurrentPosValue>NumberChars)
    {
        SetTimeMethod();
    }
    
    if (CurrentPosValue>NumberChars)
    {  
         switch (ActiveSet)
      {
              case 1:  if (AllValues[0][0]!=0x3f){if (AllValues[0][0]>'2' || (AllValues[0][0]>='2' && AllValues[0][1]>'3') || AllValues[0][2]>='6' ){lcd_init();CallInvalid();ArrayReset(0);break;}} //Display "Invalid"
            //  case 2: if (AllValues[1][0]!='D'){if (AllValues[1][0]>'3' || (AllValues[1][0]>='3' && AllValues[1][1]>'1') ||(AllValues[1][2]>'1')||(AllValues[1][2]>='1' && AllValues[1][3]>'2') || ((AllValues[1][0]='0')&&(AllValues[1][1]='0')) || ((AllValues[1][2]='0')&&(AllValues[1][3]='0')) ) {lcd_init();CallInvalid();ArrayReset(1);break;}}  //Display "Invalid"
      }  
       CurrentPosValue=0;    
       FinishedSet=0;
       ButtonPressed=99;
       
       if ( ActiveSet==1 || ActiveSet==2)
       {
       ResetTime_date=0;
       }
       
        ActiveSet=0;
    }
          
}
//reset a specific Allvalues[][] array
void ArrayReset(int ChosenArray)
{  
   for (int j=0;j<6;j++)
    {AllValues[ChosenArray][j]=0x3f;}
   
   if (ChosenArray==1)
   {
    AllValues[1][0]='Y';
    AllValues[1][1]='Y';
    AllValues[1][2]='M';
    AllValues[1][3]='M';
    AllValues[1][4]='D';
    AllValues[1][5]='D'; 
    AllValues[1][6]='W';
   } 
}

//Display the word "set"
void han_DSet()
{
  unsigned char display_Set[5] ={'S','E','T',' '};
  send_i(0x80);                     //set display position
  qushu(0x4,display_Set);                 //get data from table
}
//Display the word "
void CallInvalid()
{
  unsigned char display_Invalid[7]={'I','N','V','A','L','I','D'};
  lcd_init();
  han_Display(0x88,display_Invalid);send_d('D');
}
                    
