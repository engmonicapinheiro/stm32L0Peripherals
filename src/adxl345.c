#include "adxl345.h"

void AdxlWrite(uint8_t address, uint8_t value)
{
    uint8_t data[2];

    /* enable multibyte, place address and data into buffer */
    data[0] = (address | MULTI_BYTE_EN);
    data[1] = value;

    /* pull the cs pin low to enable the slave */
    CsEnable();

    /* transmit the address and data */
    SpiTransmit(data, 2);

    /* pull the cs pin high to disable the slave */
    CsDisable();
}

void AdxlRead(uint8_t address, uint8_t* rxdata)
{
    address |= READ_OPERATION;
    address |= MULTI_BYTE_EN;

    /* pull the cs pin low to enable the slave */
    CsEnable();

    /* send address of memory location to read from */
    SpiTransmit(&address, 1);

    /* read 6 bytes of data */
    SpiReceive(rxdata, 6);

    /* pull the cs pin high to disable the slave */
    CsDisable();
}

void AdxlInit(void)
{
    SpiGpioInit();
    SpiConfig();

    /* data format range +- 4g*/
    AdxlWrite(DATA_FORMAT_REG, FOUR_G);

    /* reset all bits */
    AdxlWrite(POWER_CTRL_REG, RESET);

    AdxlWrite(POWER_CTRL_REG, SET_MEASURE_B);
}