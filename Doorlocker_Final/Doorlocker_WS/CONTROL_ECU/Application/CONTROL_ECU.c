/*
 * Project: Door locker Security System
 *
 * File Name: CONTROL_ECU.c
 *
 * Description: Control ECU source file
 *
 * Author: Mohamed Ismail
 *
 */

#include"CONTROL_ECU.h"
#include<avr/io.h>
#include<avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	/*
	 * Enable global interrupts
	 * */
	sei();

	/*
	 * Arrays to save enterd passwords
	 */
	uint8 userPass1[PASS_LENGTH];
	uint8 userPass2[PASS_LENGTH];
	uint8 savedPass[PASS_LENGTH];

	/* The UART Frame should be in the below format:
		* Date Length: 8-Bits Data
		* Parity Type: Even Parity
		* Stop Bits: 1-Stop Bit
	  	* baud rate is 9600
	 */
	UART_ConfigType UART_config = { _8BIT, EVEN, ONE, 9600};
	UART_init(&UART_config);
	/* The TWI Frame:
	 * SCL=F_CPU/(16+2(TWBR)*4^TWPS)
	 * Prescaler/1  TWPS=00
	 * Bit rate 400kb/s
	 * F_CPU = 8MHz
	 * Interrupt OFF
	 * Acknowledge OFF
	 */
	TWI_ConfigType TWI_Config = {slave1_addr, FAST_400KB};
	TWI_init(&TWI_Config);
	Buzzer_init();
	DcMotor_Init();

	while (1) {

		receive2pass_UART(userPass1,userPass2);
		_delay_ms(300);
		uint8 comp_result = Compare_PASS(userPass1,userPass2,savedPass);
		_delay_ms(500);

		switch(comp_result)
		{
			case CORRECT_PASSWORD:
					storePass(savedPass);
					while(remaining_trials>0 && break_cond)
					{
						UART_sendByte(SELECTING_OPTION);
						uint8 option = UART_recieveByte();
						_delay_ms(15);
						Receive_PASS(userPass1);
						_delay_ms(500);

						/* saves compare result state bet. entered & saved pass in eeprom */
						uint8 pass_resultState = Compare_savedPass(userPass1,savedPass);
						if(option == DOOR_CONTROL)
						{
							handlePlusOption(pass_resultState);
						}
						else if (option == PASSWORD_CHANGE)
						{
							handleMinusOption(pass_resultState);
						}
					}
					break;

			 case INCORRECT_PASSWORD:
					while (UART_recieveByte() != CHECKING_PASSWORD);
					UART_sendByte(INCORRECT_PASSWORD);
					break;
		}

	}

	return 0;
}

/*
 * System features functions to toggle alarm & run motor
 */
void doorLocker(void)
{
		DcMotor_Rotate(CW, 100);
		delaySeconds(CW_sec);

		DcMotor_Rotate(STOP, 0);
		delaySeconds(WAIT_sec);

		DcMotor_Rotate(A_CW,100);
		delaySeconds(CCW_sec);

		DcMotor_Rotate(STOP, 0);
}

void Alarm(void)
{
		Buzzer_on();
		delaySeconds(60);
		Buzzer_off();
}

/*
 * Timer1 seconds delay Handler
 */
void timer1_TickHandler(void)
{
	ticks++;
}

void delaySeconds(uint8 seconds)
{
	ticks = 0;
	/*
	 * Initial Value =0
	 * Prescaler F_CPU/256
	 * Compare mode
	 * Compare value =31250
	 */
	Timer1_ConfigType Timer1_Config = {0,F_CPU_256,COMPARE,31250};
	Timer1_init(&Timer1_Config);
	Timer1_setCallBack(timer1_TickHandler);
	while (ticks != seconds);
	Timer1_deInit();
}

/*
 * Receive Passwords and compare them if matching occurs save it
 */
void receive2pass_UART(uint8 *userPass1, uint8 *userPass2)
{
	uint8 counter;
	UART_sendByte(SEND_UART);
	for (counter =0;counter<PASS_LENGTH;counter++)
	{
		 userPass1[counter] =UART_recieveByte();
	}
	for (counter =0;counter<PASS_LENGTH;counter++)
	{
		 userPass2[counter] =UART_recieveByte();
	}
	_delay_ms(500 );
}

uint8 Compare_PASS(uint8 *userPass1, uint8 *userPass2,uint8 *savedPass)
{
	uint8 counter;
	for(counter =0;counter<PASS_LENGTH;counter++)
	{
		if(userPass1[counter] != userPass2[counter])
		{
			  return INCORRECT_PASSWORD;
		}
		 savedPass[counter] = userPass1[counter];/*save the password*/
	}
	 return CORRECT_PASSWORD;
}

/*
 * EEPROM READ & WRITE functions
 */
void EEPROM_write_Password(uint8 *savedPass)
{
	uint8 counter;
	for (counter =0;counter<PASS_LENGTH;counter++)
	{
		  EEPROM_writeByte(0x01 + counter,savedPass[counter]);
		  _delay_ms(200);
	}
}
void EEPROM_read_Password(uint8 *savedPass)
{
	uint8 EEPROM_Read_Byte;
	uint8 counter;
	for (counter =0;counter<PASS_LENGTH ;counter++)
	{
		 EEPROM_readByte(0x01 + counter,&EEPROM_Read_Byte);
		 savedPass[counter] = EEPROM_Read_Byte;
		 _delay_ms(200);
	}
}
/*
 * store pass in eeprom & send state of password
 */
void storePass(uint8 *savedPass)
{
	EEPROM_write_Password(savedPass);
	EEPROM_read_Password(savedPass);
	_delay_ms(500);
	while (UART_recieveByte() != CHECKING_PASSWORD);
	UART_sendByte(CORRECT_PASSWORD);
	_delay_ms(500);
	break_cond = 1;
}

/*
 * Receive Password And Compare with saved Password
 */
void Receive_PASS(uint8 *userPass)
{
	uint8 counter;
	UART_sendByte(AVALIABLE);
	for (counter =0;counter<PASS_LENGTH;counter++)
	{
		 userPass[counter] = UART_recieveByte();
	}
	 _delay_ms(500);
}

uint8 Compare_savedPass(uint8 *userPass,uint8 *savedPass)
{
	uint8 counter;
	for (counter =0;counter<PASS_LENGTH;counter++)
	{
		if(userPass[counter] != savedPass[counter])
		{
			 _delay_ms(500);
			 return INCORRECT_PASSWORD;
		}
	}
	 _delay_ms(500);
	 return CORRECT_PASSWORD;
}

/*
 * Handling (+) & (-) options
 */
void handlePlusOption(uint8 plus_result)
{
	switch (plus_result)
	{
		case CORRECT_PASSWORD:
			while (UART_recieveByte() != TRANSMIT);
			UART_sendByte(CORRECT_PASSWORD);
			remaining_trials =3;
			break_cond = 1;
			/*perform door locking*/
			doorLocker();

			break;
		case INCORRECT_PASSWORD:
			while (UART_recieveByte() != TRANSMIT);
			UART_sendByte(INCORRECT_PASSWORD);
			remaining_trials--;
			if(remaining_trials == 0)
			{
				remaining_trials = 3;
				break_cond = 1;
				/*triggers alarm after 0 trials*/
				Alarm();
			}
			break;
	}
}
void handleMinusOption(uint8 minus_result)
{
	switch (minus_result)
	{
		case CORRECT_PASSWORD:
					while (UART_recieveByte() != TRANSMIT);
					UART_sendByte(CORRECT_PASSWORD);
					break_cond = 0;
					/*will go to MC1 and change pass*/
					break;
		case INCORRECT_PASSWORD:
					while (UART_recieveByte() != TRANSMIT);
					UART_sendByte(INCORRECT_PASSWORD);
					remaining_trials--;
					if(remaining_trials == 0)
					{
						remaining_trials = 3;
						break_cond = 1;
						/*triggers alarm*/
						Alarm();
					}
					break;
	}
}












