#include "spi.h"
#include "gpio.h"


//PA5-> SCK
//PA6-> MISO
//PA7-> MOSI
//PA9-> slave select

void SpiGpioInit(void)
{
    /* enable clock access to GPIOA */
    RCC->IOPENR |= RCC_IOPENR_IOPAEN;

    /* set PA5, PA6, PA7 mode to alternate function */
    //PA5:
    GPIOA->MODER &= ~(GPIO_MODER_MODE5_0);
    GPIOA->MODER |= (GPIO_MODER_MODE5_1);

    //PA6:
    GPIOA->MODER &= ~(GPIO_MODER_MODE6_0);
    GPIOA->MODER |= (GPIO_MODER_MODE6_1);

    //PA7:
    GPIOA->MODER &= ~(GPIO_MODER_MODE7_0);
    GPIOA->MODER |= (GPIO_MODER_MODE7_1);

    //PA9 (slave select) pin to output pin:
    GPIOA->MODER |= (GPIO_MODER_MODE9_0);
    GPIOA->MODER &= ~(GPIO_MODER_MODE9_1);

    /* set PA5, PA6, PA7 alternate function type to SPI1 (AF0) */

    //PA5:
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL5);
    GPIOA->AFR[0] |= (0U << GPIO_AFRL_AFSEL5_Pos);

    //PA6:
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL6);
    GPIOA->AFR[0] |= (0U << GPIO_AFRL_AFSEL6_Pos);

    //PA7
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL7);
    GPIOA->AFR[0] |= (0U << GPIO_AFRL_AFSEL7_Pos);
}

void SpiConfig(void)
{
    /* enable clock access to SPI1 module */
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    /* set clock to fPCLK/32 */
    SPI1->CR1 |= (4U << SPI_CR1_BR_Pos);

    /* set CPOL to 1 and CPHA to 1 */
    SPI1->CR1 |= SPI_CR1_CPOL;
    SPI1->CR1 |= SPI_CR1_CPHA;

    /* enable full duplex */
    SPI1->CR1 &= ~(SPI_CR1_RXONLY);

    /* set MSB first */
    SPI1->CR1 &= ~(SPI_CR1_LSBFIRST);

    /* set mode to master */
    SPI1->CR1 |=SPI_CR1_MSTR;

    /* set 8 bit data mode */
    SPI1->CR1 &= ~(SPI_CR1_DFF);

    /* select software slave management by setting SSM=1 and SSI=1 */
    SPI1->CR1 |= SPI_CR1_SSI;
    SPI1->CR1 |= SPI_CR1_SSM;

    /* enable SPI module */
    SPI1->CR1 |= SPI_CR1_SPE;
}

void SpiTransmit(uint8_t *data, uint32_t size)
{
    uint32_t i = 0;
    uint8_t temp;

    while(i < size)
    {
        /* wait for the TXE bit to set in the status register */
        /* this will indicate that the transmit buffer is empty */
        while (!((SPI1->SR) & SPI_SR_TXE));

        /* write the data to the data register */
        SPI1->DR = data[i];
        i++;
    }

    /* wait for TXE to be set again */
    while (!((SPI1->SR) & SPI_SR_TXE));

    /* wait for the BSY bit to reset in the status register */
    while (!((SPI1->SR) & SPI_SR_BSY));

    /* clear the OVR flag */
    temp = SPI1->DR;
    temp = SPI1->SR;
}

void SpiReceive(uint8_t *data, uint32_t size)
{
    while (size)
    {
        SPI1->DR = 0; //send dummy data
        while (!((SPI1->SR) & SPI_SR_RXNE));
        /* read data from data register */
        *data++ = (SPI1->DR);
        size--;

    }
}

void CsEnable(void)
{
    GPIOA->ODR &= ~(GPIO_ODR_OD9);
}

void CsDisable(void)
{
    GPIOA->ODR |= (GPIO_ODR_OD9);
}