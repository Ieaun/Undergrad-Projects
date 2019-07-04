/* 
 * File:   LCD.h
 * Author: ieaun
 *
 * Created on 05 December 2018, 12:09
 */

#ifndef LCD_H
#define	LCD_H
//LCD  
void ArrayReset(int ChosenArray);
void lcd_init();                    //LCD init       
void clear_p();                     //clear screen  
void han_DSet();
void han_Number(int DisplayPos,int NumberSelected);
void GetValue(char CurrentNo);
void han_Display_Results();
void han_Display(int DisplayPos,const unsigned char *Data);
void BiggerThanX(int NumberChars);
void wr_zb();                       //display setting mode.
void send_d(unsigned char x);       //send data
void send_i(unsigned char x);       //send command.
void chk_busy();                    //check busy sub.
void qushu(int counts,const unsigned char *ps);       //search table.
void delay();                       //delay func, decide the speed of display.
void delay1();                      //delay func, decide the speed of blink.
void CallInvalid();
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

