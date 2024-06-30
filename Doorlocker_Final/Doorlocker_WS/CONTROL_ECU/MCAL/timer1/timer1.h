/*
 * File Name: timer1.h
 *
 * Description: header file for timer1
 *
 * Author: Mohamed Ismail
*/
#ifndef MCAL_TIMER1_TIMER1_H_
#define MCAL_TIMER1_TIMER1_H_

#include "../../inc/std_types.h"
#include "../GPIO/gpio.h"

typedef enum {
	NORMAL,
  COMPARE
}Timer1_Mode;
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXTERNAL_CLK_FALLING,EXTERNAL_CLK_RISING
}Timer1_Prescaler;

typedef struct {
	uint16  initial_value;
	 Timer1_Prescaler  prescaler;
	 Timer1_Mode mode;
	uint16  compare_value;

}Timer1_ConfigType;


void Timer1_init(const Timer1_ConfigType*Config_Ptr);

void  Timer1_deInit(void);

void Timer1_setCallBack(void(*a_ptr)(void));

#endif  /* MCAL_TIMER1_TIMER1_H_ */
