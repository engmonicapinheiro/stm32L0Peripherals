#include "uart.h"
#include <stdint.h>

//TODO: refactor the driver to be module agnostic

static uint16_t ComputeUartBaudrate(uint32_t peripheralClk, uint32_t baudrate);
static void SetBaudrate(USART_TypeDef *USARTx, uint32_t peripheralClk, uint32_t baudrate);

int _write(int fd, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        UartWrite(ptr[i]);
    }
    return len;
}

//PA2->TX
//PA15->RX
void UartInit(void)
{
    /* enable clock access to GPIOA */
    RCC->IOPENR |= RCC_IOPENR_IOPAEN;

    /* set PA2 (TX) mode to alternate function */
    GPIOA->MODER &= ~(GPIO_MODER_MODE2_0);
    GPIOA->MODER |= GPIO_MODER_MODE2_1;

    /* set PA15 (RX) mode to alternate function */
    GPIOA->MODER &= ~(GPIO_MODER_MODE15_0);
    GPIOA->MODER |= GPIO_MODER_MODE15_1;

    /* set alternate function type to UART (AF4) for TX */
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2);
    GPIOA->AFR[0] |= (4U << GPIO_AFRL_AFSEL2_Pos);

    /* set alternate function type to UART (AF4) for RX */
    GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL15);
    GPIOA->AFR[1] |= (4U << GPIO_AFRH_AFSEL15_Pos);

    /***** Configure UART module *****/
    /* enable clock access to Uart module */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    /* configure the baudrate */
    SetBaudrate(USART2, APB1_CLK, UART_BAUDRATE);

    /* configure the transfer direction */
    USART2->CR1 = (USART_CR1_TE | USART_CR1_RE);  //clean the other bits in the register

    /* enable the Uart module */
    USART2->CR1 |= USART_CR1_UE;

}

void UartWrite(int ch)
{
    /* make sure transmit data register is empty */
    while(!(USART2->ISR & USART_ISR_TXE));
    /** write to the transmit data register */
    USART2->TDR = (ch & 0xFF);
}

char UartRead(void)
{
    /* wait for a new character to arrive */
    while (!(USART2->ISR & USART_ISR_RXNE));
    return (USART2->RDR);
}

static uint16_t ComputeUartBaudrate(uint32_t peripheralClk, uint32_t baudrate)
{
    return (peripheralClk + (baudrate/2)) / baudrate;
}

//TODO: refactor the driver to be module agnostic
static void SetBaudrate(USART_TypeDef *USARTx, uint32_t peripheralClk, uint32_t baudrate)
{
    USARTx->BRR = ComputeUartBaudrate(peripheralClk, baudrate);
}