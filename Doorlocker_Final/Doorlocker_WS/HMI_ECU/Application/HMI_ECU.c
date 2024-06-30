/*
 * Project: Door locker Security System
 *
 * File Name: HMI_ECU.c
 *
 * Description: Human Machine Interface ECU
 *
 * Author: Mohamed Ismail
 *
 */

#include"HMI_ECU.h"
#include<avr/io.h>
#include <avr/interrupt.h>
#include<util/delay.h>



int main(void) {
	/*enable global interrupt*/
	sei();
	/* The UART Frame should be in the below format:
		* Date Length: 8-Bits Data
		* Parity Type: Even Parity
		* Stop Bits: 1-Stop Bit
	  	* baud rate is 9600
	 */
	UART_ConfigType UART_config ={_8BIT,EVEN, ONE, 9600};
	UART_init(&UART_config);
	LCD_init();

	uint8 userPass1[PASS_LENGTH];
	uint8 userPass2[PASS_LENGTH];
	uint8 pass_flag;
	while (1) {
		getUserPass(userPass1);
		_delay_ms(300);
		confirmPass(userPass2);
		_delay_ms(300);

		send2pass_UART(userPass1, userPass2);
		_delay_ms(300);
		UART_sendByte(CHECKING_PASSWORD);
		pass_flag = UART_recieveByte();

		switch (pass_flag)
		{
			case VALID_PASSWORD:
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Pass Matched!");
					_delay_ms(300);
					handleSystemMenu(userPass1);
				break;
			case INVALID_PASSWORD:
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Pass Not Matched!");
					_delay_ms(300);
				break;
				/*
				 * Return to enter pass again
				 */
		}

	}
	return 0;
}


/*
 * getUserPass function takes a userPass of 5 digits from the user and
 * saves it in an array.
 */
void getUserPass(uint8 *userPass)
{
	uint8 counter;
	uint8 pressedkey;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter Pass:");
	LCD_moveCursor(1,0);
	counter=0;

	while (counter < PASS_LENGTH)
	{
		pressedkey =KEYPAD_getPressedKey();

		if ((pressedkey>= 0) && (pressedkey<= 9))
		{
			userPass[counter] = pressedkey;
			LCD_displayCharacter('*');
			counter++;
		}
		_delay_ms(500);
	}
	/*
	 * Wait till enter key pressed
	 */
	while (KEYPAD_getPressedKey()!='=');
	_delay_ms(500);
}

/*
 * confirmPass function re-enters the same userPass to confirm it.
 */
void confirmPass(uint8 *userPass) {
	uint8 counter;
	uint8 pressedkey;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Re-enter Pass:");
	LCD_moveCursor(1, 0);
	counter = 0;

	while (counter < PASS_LENGTH)
	{
		pressedkey = KEYPAD_getPressedKey();
		if ((pressedkey >= 0) && (pressedkey <= 9))
		{
			userPass[counter] = pressedkey;
			LCD_displayCharacter('*');
			counter++;
		}
		_delay_ms(500);
	}
	while(KEYPAD_getPressedKey()!= '=');
	_delay_ms(500);
}

/*
 * send2pass_UART function sends two passwords via UART.
 */
void send2pass_UART(uint8 *userPass1, uint8 *userPass2) {
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Transmitting");
	LCD_moveCursor(1, 0);
	while (UART_recieveByte() != SEND_UART);

	//Send Pass1
	for (uint8 counter=0;counter<PASS_LENGTH;counter++)
	{
		UART_sendByte(userPass1[counter]);
		_delay_ms(15);
	}
	_delay_ms(500);

	//Send Pass2
	for (uint8 counter=0;counter<PASS_LENGTH;counter++)
	{
			UART_sendByte(userPass2[counter]);
			_delay_ms(15);
	}
}

/*
 * Send saved userPasss function sends two userPasss via UART to check.
 */
void SenduserPassUART(uint8 *userPass1) {
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Transmitting");
	LCD_moveCursor(1, 0);
	while(UART_recieveByte()!= AVALIABLE);

	for (uint8 counter =0;counter<PASS_LENGTH;counter++)
	{
		UART_sendByte(userPass1[counter]);
		_delay_ms(15);
	}
}
/*
 * Timer1 Handler
 */
void timer1_TickHandler(void)
{
	ticks++;
}

void delaySeconds(uint8 seconds)
{
	/*
	 * Initial Value =0
	 * Prescaler F_CPU/256
	 * Compare mode
	 * Compare value =31250
	 */
    ticks = 0;
    Timer1_ConfigType Timer1_Config = {0,F_CPU_256,COMPARE,31250};
    Timer1_init(&Timer1_Config);

    Timer1_setCallBack(timer1_TickHandler);
    while (ticks != seconds);

    Timer1_deInit();
}
void doorLocker(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,4,"Door is");
	LCD_displayStringRowColumn(1,2,"Unlocking");
	delaySeconds(CW_sec);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,3,"WAITING");
	delaySeconds(WAIT_sec);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,4,"Door is");
	LCD_displayStringRowColumn(1,3,"Locking");
	delaySeconds(CCW_sec);
}

/*
 * handleSystemMenu for handling system options
 */
void handleSystemMenu(uint8 *userPass) {
	uint8 pressedkey;
	uint8 PlusOption;
	uint8 MinusOption;
	while (1)
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,1,"+ : Open Door");
		LCD_displayStringRowColumn(1,1,"- : Change pass");
		pressedkey = KEYPAD_getPressedKey();
		while (UART_recieveByte() != SELECTING_OPTION );

		while( remaining_trials>0)
		{
			switch (pressedkey)
			{
				case '+' :
					UART_sendByte(DOOR_CONTROL);
					getUserPass(userPass);
					SenduserPassUART(userPass);
					UART_sendByte(TRANSMIT);
					PlusOption= UART_recieveByte();
					handlePlusOption(PlusOption);
					break;
				case '-' :
					UART_sendByte(PASSWORD_CHANGE);
					getUserPass(userPass);
					SenduserPassUART(userPass);
					UART_sendByte(TRANSMIT);
					MinusOption= UART_recieveByte();
					handleMinusOption(MinusOption);
					break;
			}
			/*
			 * Go to main menu
			 */
			if(PlusOption == VALID_PASSWORD || MinusOption == VALID_PASSWORD||remaining_trials == 0 )
				{
					remaining_trials = 3;
					break;
				}
		}
		if(MinusOption == VALID_PASSWORD)
		{
				break;  // Jump to set new password [getUserPass function]
		}
			_delay_ms(300);
	}
}

void handlePlusOption(uint8 PlusOption)
{
    switch (PlusOption) {
        case VALID_PASSWORD:
            doorLocker();
            remaining_trials = 3;
            break;
        case INVALID_PASSWORD:
            LCD_clearScreen();
            LCD_displayStringRowColumn(0,1,"Wrong Password");
            _delay_ms(600);
            remaining_trials--;
            if (remaining_trials == 0) {
                LCD_clearScreen();
                LCD_displayStringRowColumn(0,5,"ERROR!");
                delaySeconds(60);
            }
            break;
    }
}

void handleMinusOption(uint8 MinusOption)
{

    switch (MinusOption) {
        case VALID_PASSWORD:
            remaining_trials = 3;
            break;
        case INVALID_PASSWORD:
            LCD_clearScreen();
            LCD_displayStringRowColumn(0,1,"Wrong Password");
            _delay_ms(600);
            remaining_trials--;
            if (remaining_trials == 0) {
                LCD_clearScreen();
                LCD_displayStringRowColumn(0,5,"ERROR!");
                delaySeconds(60);
            }
            break;
    }
}



