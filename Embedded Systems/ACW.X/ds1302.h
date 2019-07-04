/* 
 * File:   ds1302.h
 * Author: ieaun
 *
 * Created on 05 December 2018, 11:38
 */

#ifndef DS1302_H
#define	DS1302_H
void DayChanger(_Bool *Changed);
void DateMain(char *Year1_Temp,char *Year2_Temp,char *Month1_Temp,char *Month2_Temp,char *Day1_Temp,char *Day2_Temp);
void ClockMain(char *Hour1_Temp,char *Hour2_Temp,char *Min1_Temp,char *Min2_Temp,char *Sec1_Temp,char *Sec2_Temp);
void port_init();                      //port initilize subroutine.
void ds1302_init();                    //DS1302 initilize subroutine.
void set_time(int Hour,int Min,int Day_st,int Month_st,int Year_st);                       //set time subroutine.
void get_time();                       //get time subroutine.
void ds_display(); 

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* DS1302_H */

