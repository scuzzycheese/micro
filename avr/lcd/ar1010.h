/**
 *  Copyright (c) 2010 Daine Mamacos <daine.mamacos@reverseorder.net>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef AR1010_H
#define	AR1010_H

#include <inttypes.h>

#define FTR(x) ((x) - 690)
#define RTF(x) ((x) + 690)

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

#endif

