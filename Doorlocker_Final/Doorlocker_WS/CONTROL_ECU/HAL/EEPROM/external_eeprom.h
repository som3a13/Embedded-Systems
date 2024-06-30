/*
 * Module: External EEPROM
 *
 * File Name: external_eeprom.h
 *
 * Description: header file for eeprom driver
 *
 * Author: Mohamed Ismail
 */
#ifndef HAL_EEPROM_EXTERNAL_EEPROM_H_
#define HAL_EEPROM_EXTERNAL_EEPROM_H_

#include "../../inc/std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

#endif /* HAL_EEPROM_EXTERNAL_EEPROM_H_ */
