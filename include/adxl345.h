#ifndef __ADXL345_H
#define __ADXL345_H

#include "spi.h"
#include <stdlib.h>


/* registers addresses */
#define POWER_CTRL_REG      0x2D
#define DATA_FORMAT_REG     0x31

#define DATA_START_ADDR     0x32

/* values to write to the registers */
#define SET_MEASURE_B       0x08
#define RESET               0x00
#define FOUR_G              0x01

#define MULTI_BYTE_EN       0x40
#define READ_OPERATION      0x80


/* functions prototypes */
void AdxlWrite(uint8_t address, uint8_t value);
void AdxlRead(uint8_t address, uint8_t* rxdata);
void AdxlInit(void);

#endif  //ADXL345_H