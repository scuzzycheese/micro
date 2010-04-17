/* 
 * File:   ar1010.h
 * Author: scuzzy
 *
 * Created on 17 April 2010, 22:40
 */

#ifndef _AR1010_H
#define	_AR1010_H

#include <inttypes.h>

#define FTR(x) (x - 690)
#define RTF(x) (x + 690)

#define SLA_W 0x20 //write address
#define SLA_R 0x21 //read address


//Exported functions
void ar1010Init();
void ar1010Tune(uint16_t freq);
void ar1010Seek();
void ar1010Volume(uint8_t volu);
uint16_t ar1010getCurFreq();
void ar1010WaitForReady();

//internal private functions
static uint16_t getRegister_helper(uint8_t regNumber);
static uint16_t getRegister(uint8_t regNumber, uint8_t vola);
static uint8_t setRegister(uint8_t regNumber, uint16_t regValue);
static void setAllRegs(uint16_t *regVals);
static void getCurFreq();
#endif	/* _AR1010_H */

