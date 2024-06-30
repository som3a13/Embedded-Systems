/*
 * Project: Door locker Security System
 *
 * File Name: HMI_ECU.h
 *
 * Description: Header file for HMI_ECU
 *
 * Author: Mohamed Ismail
 */

#ifndef APPLICATION_HMI_ECU_H_
#define APPLICATION_HMI_ECU_H_

#include"../HAL/LCD/lcd.h"
#include"../HAL/KEYPAD/keypad.h"
#include"../MCAL/UART/uart.h"
#include"../MCAL/timer1/timer1.h"

#include "../inc/std_types.h"

#define PASS_LENGTH  5
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
 * States to Make M1 & M2 receive and transmit correctly
 */
typedef enum {
    SEND_UART,
    INVALID_PASSWORD,
    VALID_PASSWORD,
    TRANSMIT,
    CHECKING_PASSWORD,
    AVALIABLE,
    SELECTING_OPTION,
    DOOR_CONTROL,
    PASSWORD_CHANGE
} UART_States;


/*
 * Password handling functions
 */
void getUserPass(uint8 *userPass);

void confirmPass(uint8 *userPass);

void SenduserPassUART(uint8 *userPass1);

void send2pass_UART(uint8 *userPass1,uint8 *userPass2);


/*
 * MainMenu Functions
 */
void handleSystemMenu(uint8 *userPass);
void handleMinusOption(uint8 MinusOptionState);
void handlePlusOption(uint8 PlusOptionState);
/*
 * Door State Display on LCD Function
 */
void doorLocker(void);
/*
 * Timer1 Handler
 */
void timer1_TickHandler(void);
void delaySeconds(uint8 seconds);

volatile uint8 remaining_trials = 3;
volatile uint8 ticks = 0;


#endif /* APPLICATION_HMI_ECU_H_ */
