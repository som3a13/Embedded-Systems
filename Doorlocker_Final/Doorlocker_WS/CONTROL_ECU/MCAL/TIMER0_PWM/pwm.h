/*
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for PWM
 *
 * Author: Mohamed Ismail
 *
 */
#ifndef MCAL_TIMER0_PWM_PWM_H_
#define MCAL_TIMER0_PWM_PWM_H_

#include "../../inc/std_types.h"
#include "../GPIO/gpio.h"

/*
 * Description:
 * Starts the PWM (Pulse Width Modulation) output using Timer0 with the specified duty cycle.
 * The function sets up the necessary configurations and starts generating PWM signals.
 * Parameters:
 * duty_cycle: The required duty cycle percentage of the generated PWM signal. Its value should be from 0 → 100
 */
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* MCAL_TIMER0_PWM_PWM_H_ */
