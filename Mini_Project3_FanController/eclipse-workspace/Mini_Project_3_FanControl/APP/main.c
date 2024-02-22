/******************************************************************************
 * Project: Fan Controller System
 * File Name: main.c
 * Description: Application layer
 * Date : 21/2/2024
 * Author: Mohamed Ismail
 *******************************************************************************/
#include "../HAL/DC_MOTOR/motor.h"
#include "../HAL/LM35/lm35_sensor.h"
#include "../HAL/LCD/lcd.h"
#include "../MCAL/ADC/adc.h"
typedef enum {
	OFF,ON
}FAN_STATE;

int main(void) {
	uint8 tempVal = 0;
	/*Initialization for the modules
	 * 1.ADC prescalar / Ref_voltage
	 * 2.LCD init / StartUp display
	 * 3.Motor init
	 * 4.Make instance to use FAN_STATE enum
	 * */

	ADC_ConfigType ADC_LM35_Config = { INTERNAL_2_56V, DF_8 };
	ADC_init(&ADC_LM35_Config);
	LCD_init();
	DcMotor_Init();
	FAN_STATE Fan_state;
	uint8 (*temp)(void)=LM35_getTemperature;
	/*
	 * Displaying init chars on LCD
	 */
	LCD_displayStringRowColumn(0, 3, "FAN is OFF ");
	LCD_displayStringRowColumn(1, 3, "Temp =    C");

	while (1) {
		/*
		 * Store Return of temp() in tempVal to save temperature reading
		 */
		tempVal=temp();
		/*
		 * Displaying Temperature value on LCD
		 */
		LCD_moveCursor(1, 10);
		if (tempVal >= 100) {
			LCD_integerToString(tempVal);
		} else {
			LCD_integerToString(tempVal);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
		if (tempVal < 30) {
			DcMotor_Rotate(STOP, 0);
			Fan_state = OFF;
		}
		else if (tempVal >= 30 && tempVal < 60) {
			DcMotor_Rotate(CW, 25);
			Fan_state = ON;
		}
		else if (tempVal >= 60 && tempVal < 90) {
			DcMotor_Rotate(CW, 50);
			Fan_state = ON;
		}
		else if (tempVal >= 90 && tempVal < 120) {
			DcMotor_Rotate(CW, 75);
			Fan_state = ON;
		}
		else if (tempVal >= 120) {
			DcMotor_Rotate(CW, 100);
		}
    /*
     * Display FAN State on LCD
     */
		LCD_moveCursor(0, 10);
		if(Fan_state==ON)
		{
			LCD_displayStringRowColumn(0, 10, "ON ");
		}
		else
		{
			LCD_displayStringRowColumn(0, 10, "OFF");
		}

	}
	return 0;
}
