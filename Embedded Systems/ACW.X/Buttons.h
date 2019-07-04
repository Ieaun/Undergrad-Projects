/* 
 * File:   Buttons.h
 * Author: ieaun
 *
 * Created on 05 December 2018, 12:05
 */

#ifndef BUTTONS_H
#define	BUTTONS_H
void  keymatrix(int *ButtonPressed_,int *ActiveSet);
//void  delayKey();              //delay function declare
void  initkey();               //I/O PORT initialize function declare
void  scan();               //key scan function declare
void  display(int x);       //display function declare
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

