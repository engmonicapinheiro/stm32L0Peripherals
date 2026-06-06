#ifndef __SPI_H
#define __SPI_H

#include "stm32l031xx.h"
#include <stdint.h>


void SpiGpioInit(void);
void SpiConfig(void);
void SpiTransmit(uint8_t *data, uint32_t size);
void SpiReceive(uint8_t *data, uint32_t size);
void CsEnable(void);
void CsDisable(void);

#endif //SPI_H