 /******************************************************************************
 * Module: Temperature Sensor
 * File Name: lm35_sensor.h
 * Description: header file for the LM35 Temperature Sensor driver
 * Date : 19/2/2024
 * Author: Mohamed Ismail
 *******************************************************************************/

#ifndef HAL_LM35_LM35_SENSOR_H_
#define HAL_LM35_LM35_SENSOR_H_

#include "../../MCAL/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SENSOR_CHANNEL_ID         2
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void);



#endif /* HAL_LM35_LM35_SENSOR_H_ */
