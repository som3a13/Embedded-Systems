/******************************************************************************
 * Module: Pulse width modulation
 * File Name: pwm.h
 * Description: header file for PWM
 * Date : 19/2/2024
 * Author: Mohamed Ismail
 *******************************************************************************/

#ifndef MCAL_PWM_PWM_H_
#define MCAL_PWM_PWM_H_

#include "../std_types.h"


/*
 * Description:
 * Starts the PWM (Pulse Width Modulation) output using Timer0 with the specified duty cycle.
 * The function sets up the necessary configurations and starts generating PWM signals.
 * Parameters:
 * duty_cycle: The required duty cycle percentage of the generated PWM signal. Its value should be from 0 → 100
 */
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* MCAL_PWM_PWM_H_ */
