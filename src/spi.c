#include "spi.h"
#include "pinconfig.h"
#include "TM4C123GH6PM.h"

void SPI_Init(void)
{
    /* Enable Clock for SPI0 peripheral */
    SYSCTL->RCGCSSI |= 1<<0;

    /* Configure Pins for SPI0 */
    Pin_Config(Port_PA, 2, PA2_SSI0CLK);
    Pin_Config(Port_PA, 3, PA3_SSI0FSS);
    Pin_Config(Port_PA, 4, PA4_SSI0RX);
    Pin_Config(Port_PA, 5, PA5_SSI0TX);

    /* Disable the SPI0 module */
    SSI0->CR1 &= ~(1<<1);

    /* Choose SPI0 module to be Master */
    SSI0->CR1 &= ~(1<<2);

    /* Configure Clock source as  System Clock */
    SSI0->CC &= ~(0xF<<0);

    /* Configure Prescalar for SPI0 module as 2 */
    SSI0->CPSR = 2;

    /* Configure the Serial Clock rate of SPI0 module as 1MHz */
    SSI0->CR0 |= 7 << 8;

    /* Select Freescale mode with CPOL = 0 and CPHA = 0*/
    SSI0->CR0 &= ~(3<<4); // Frescale Mode
    SSI0->CR0 &= ~(3<<6); // CPOL and CPHA

    /* Configure the Data size in the Frame as */
    SSI0->CR0 |= 7;

    /* Enable SPI0 module */
    SSI0->CR1 |= (1<<1);
}

void SPI_Send(uint16_t *tx_buf, uint32_t len)
{
    for(uint32_t iter = 0; iter < len; iter++)
    {
        /* Poll for the TX FIFO to be empty */
        while(!((SSI0->SR) & 0x1))
        ;

        /* Write the Data to be transmitted */
        SSI0->DR = tx_buf[iter];
    }
}

void SPI_Receive(uint16_t *rx_buf, uint32_t len)
{
    for(uint32_t iter = 0; iter < len; iter++)
    {
        /* Poll for the TX FIFO to be empty */
        while(!((SSI0->SR) & 0x1))
        ;

        /* Write the Dummy Data to be transmitted */
        SSI0->DR = 0x00;

        /* Poll for the RX FIFO to be non-empty */
        while(!((SSI0->SR) & 0x1))
        ;

        /* Read the Data from Buffer */
        rx_buf[iter] = SSI0->DR;
    }
}

void SPI_Transaction(uint16_t *tx_buf, uint16_t *rx_buf, uint32_t len)
{
    for(uint32_t iter = 0; iter < len; iter++)
    {
        /* Poll for the TX FIFO to be empty */
        while(!((SSI0->SR) & 0x1))
        ;

        /* Write the Dummy Data to be transmitted */
        SSI0->DR = tx_buf[iter];

        /* Poll for the RX FIFO to be non-empty */
        while(!((SSI0->SR) & 0x1))
        ;

        /* Read the Data from Buffer */
        rx_buf[iter] = SSI0->DR;
    }   
}