/******************************************************************************
 * Module: ADC
 * File Name: adc.h
 * Description: header file for the ATmega16 ADC driver
 * Date : 19/2/2024
 * Author: Mohamed Ismail
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "../std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
/*
 * ADC Prescaler Division Factor
 */
typedef enum {
	DF_2_0, DF_2_1, DF_4, DF_8, DF_16, DF_32, DF_64, DF_128
} ADC_Prescaler;
/*
 * ADC Voltage Refrence Selection
 */
typedef enum {
	AREF, AVCC, Reserved, INTERNAL_2_56V
} ADC_ReferenceVolatge;

typedef struct {
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
} ADC_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType *Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

/*
 * Description: Function to disable the ADC definitions
 */
void ADC_deInit(void);
#endif /* ADC_H_ */
