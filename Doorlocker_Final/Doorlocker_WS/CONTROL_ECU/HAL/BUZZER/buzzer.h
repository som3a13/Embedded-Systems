/*
 * Module: Buzzer
 *
 * File Name: Buzzer.h
 *
 * Description: header file for Buzzer driver
 *
 * Author: Mohamed Ismail
 */
#ifndef HAL_BUZZER_BUZZER_H_
#define HAL_BUZZER_BUZZER_H_

/*
 * Buzzer PINS Configurations
 */
#define BUZZER_PORT_ID         PORTB_ID
#define BUZZER_PIN_ID          PIN5_ID

void Buzzer_init();
void Buzzer_on(void);
void Buzzer_off(void);


#endif /* HAL_BUZZER_BUZZER_H_ */
