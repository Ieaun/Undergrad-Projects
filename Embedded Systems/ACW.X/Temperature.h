/* 
 * File:   Temperature.h
 * Author: ieaun
 *
 * Created on 05 December 2018, 12:06
 */

#ifndef TEMPERATURE_H
#define	TEMPERATURE_H
//Thermo
void delayThermo(char x,char y);
void mainThermo(int *Tens_Temp,int *Ones_Temp,int *Decimals_Temp );
void get_temp();
void initThermo();
void displayThermo();
void CheckTemp();
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TEMPERATURE_H */

