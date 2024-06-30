/*
 * Project: Door locker Security System
 *
 * File Name: CONTROL_ECU.c
 *
 * Description: Control ECU header file
 *
 * Author: Mohamed Ismail
 *
 */

#ifndef APPLICATION_CONTROL_ECU_H_
#define APPLICATION_CONTROL_ECU_H_

#include"../HAL/DC_MOTOR/motor.h"
#include"../HAL/BUZZER/buzzer.h"
#include"../HAL/EEPROM/external_eeprom.h"
#include"../MCAL/timer1/timer1.h"
#include"../MCAL/I2C/twi.h"
#include "../MCAL/UART/uart.h"

#include "../inc/std_types.h"




#define PASS_LENGTH  5


/*
 * States to Make M1 & M2 receive and transmit correctly
 */
typedef enum {
    SEND_UART,
    INCORRECT_PASSWORD,
    CORRECT_PASSWORD,
    TRANSMIT,
    CHECKING_PASSWORD,
    AVALIABLE,
    SELECTING_OPTION,
    DOOR_CONTROL,
    PASSWORD_CHANGE
} UART_States;
/*
 * Motor delays
 */
typedef enum
{
	CW_sec=15,
	CCW_sec=15,
	WAIT_sec=3
}Motor_DELAY;

/*
 * Receive Passwords and compare them if matching occurs save it
 */
void  receive2pass_UART(uint8 *userPass1,uint8 *userPass2);
uint8 Compare_PASS(uint8 *userPass1,uint8 *userPass2,uint8 *savedPass);

/*
 * EEPROM READ & WRITE functions
 */
void  EEPROM_write_Password(uint8 *savedPass);
void  EEPROM_read_Password(uint8 *savedPass);
/*
 * store pass in eeprom & send state of password
 */
void storePass(uint8 *savedPass);

/*
 * Receive Password And Compare with saved Password
 */
void  Receive_PASS(uint8 *userPass);
uint8 Compare_savedPass(uint8 *userPass,uint8 *savedPass);

/*
 * Handling (+) & (-) options
 */
void handlePlusOption(uint8 pass_result);
void handleMinusOption(uint8 pass_result);

/*
 * Timer1 Handler
 */
void  timer1_TickHandler(void);
void  delaySeconds(uint8 seconds);
/*
 * System features functions to toggle alarm & run motor
 */
void  doorLocker(void);
void  Alarm(void);

/*
 * Global Variables
 */
volatile uint8 ticks = 0;
volatile uint8 remaining_trials = 3;
volatile uint8 break_cond=1;


#endif /* APPLICATION_CONTROL_ECU_H_ */
