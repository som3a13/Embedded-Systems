/*
 * Module: Buzzer
 *
 * File Name: Buzzer.c
 *
 * Description: source file for Buzzer driver
 *
 * Author: Mohamed Ismail
 */
#include"buzzer.h"

#include "../../inc/common_macros.h"
#include "../../MCAL/GPIO/gpio.h"


void Buzzer_init()
{
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}

void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}

void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}
