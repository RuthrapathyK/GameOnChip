#include "display.h"
#include "spi.h"
#include "gpio.h"
#include "pinconfig.h"
#include "scheduler.h"

uint16_t rx_buffer[10] = {0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5};
uint16_t rx2_buffer[10]= {0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5};
uint16_t rx3_buffer[10]= {0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5};

static void Disp_chipSelect(Disp_PinState_e state)
{
      if(state == Disp_pinLow)
            GPIO_clearPin(PA3);
      else
            GPIO_setPin(PA3);
}

static void Disp_resetPin(Disp_PinState_e state)
{
      if(state == Disp_pinLow)
            GPIO_clearPin(PE1);
      else
            GPIO_setPin(PE1);
}

static void Disp_dataCommand_Select(Disp_cmdData_e flag)
{
      if(flag == Disp_enableCommand)
            GPIO_clearPin(PE2);
      else
            GPIO_setPin(PE2);
}

void Disp_Init(void)
{
    SPI_Init();

    /* Configure Pins for SPI0 */
    Pin_Config(Port_PA, 2, PA2_SSI0CLK);
    Pin_Config(Port_PA, 4, PA4_SSI0RX);
    Pin_Config(Port_PA, 5, PA5_SSI0TX);
    
    /* Initialize Chip Select Pin - Initially High */
    GPIO_Init(PA3, GPIO_DigitalOutput, 1);

    /* Initialize the Reset pin  - Initially High */
    GPIO_Init(PE1, GPIO_DigitalOutput, 1);
    
    /* Initialize the DC/RS pin (Data/Command)  - Initially DC */
    GPIO_Init(PE2, GPIO_DigitalOutput, 1);
    
    /* Perform Hardware Reset of Display */
    GPIO_clearPin(PE1);
    OS_delay(20);
    GPIO_setPin(PE1);
    OS_delay(200);

}

void Disp_Run(void)
{
      Disp_readReg(0xDA, rx_buffer, 8);
      Disp_readReg(0xDB, &rx_buffer[1], 8);
      Disp_readReg(0xDC, &rx_buffer[2], 8);
}

void Disp_readReg(uint8_t cmd, uint16_t *rx_buf, uint8_t rx_bitLen)
{
   uint16_t t_txBuf = cmd;
   uint16_t t_rxBuf[10] = {0};  
   uint8_t rx_ByteLen = 0;
   uint8_t rx_frameBitLen = 0;

   /* Change the SPI0 modules Frame Bit Length to 8 bits for command */
   //Disp_changeFrame_len(8);

   /* Enable Chip Select */
   Disp_chipSelect(Disp_pinLow);

   /* Set the Display to Command Mode*/
   Disp_dataCommand_Select(Disp_enableCommand);

   /* Send the Command */
   SPI_Send(&t_txBuf, 1);

   /* Set the Display to Data Mode*/
   Disp_dataCommand_Select(Disp_enableData);
   
   /* Derive the SPI0 modules Frame Bit Length */
   if(rx_bitLen > 8)
      rx_frameBitLen = rx_bitLen + 1;
   else
      rx_frameBitLen = rx_bitLen;

   /* Change the SPI0 module Frame Size register */
   //Disp_changeFrame_len(rx_frameBitLen);

   /* Calculate the Number of Bytes from Bit Length */
   rx_ByteLen  = rx_frameBitLen / 8;

   if((rx_frameBitLen % 8) != 0)
      rx_ByteLen = rx_ByteLen + 1;
      
   /* Get the Data from the Dispaly Unit */
   SPI_Receive(t_rxBuf, rx_ByteLen);

   /* Rearrage the received Bytes according to Bit Length */
   if(rx_bitLen > 8)
   {
      for(uint8_t iter = 0; iter < rx_ByteLen - 1; iter++)
      {
         rx_buf[iter] = ((((t_rxBuf[iter] << 1) & 0xFE) | ((t_rxBuf[iter + 1] >> 7) & 0x01)) & 0xFF);
      }
   }
   else
   {
       rx_buf[0] = t_rxBuf[0];
   }

   /* Disable Chip Select */
   Disp_chipSelect(Disp_pinHigh);
}

void Disp_changeFrame_len(uint8_t frameBits)
{
   /* Check the Precondition */
   ASSERT((frameBits >= 4) && (frameBits <= 16));

    /* Poll till SPI0 is Idle after Transmission */
    while(((SSI0->SR >> 4) & 0x01))
    ;

    /* Disable the SPI0 module */
    SSI0->CR1 &= ~(1<<1);

    /* Configure the Frame Length in bits*/
    SSI0->CR0 |= frameBits - 1;

    /* Enable SPI0 module */
    SSI0->CR1 |= (1<<1);

}