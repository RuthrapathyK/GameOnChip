#include "ILI9341.h"
#include "common.h"
#include "../src/Drivers/GPIO/gpio.h"
#include "../src/Drivers/SPI/spi.h"
#include "../src/Drivers/PinMux/pinconfig.h"
#include "../src/OS/scheduler.h"

static void ILI_chipSelect(ILI_PinState_e state)
{
      if(state == ILI_pinLow)
            GPIO_clearPin(PA3);
      else
            GPIO_setPin(PA3);
}

static void ILI_resetPin(ILI_PinState_e state)
{
      if(state == ILI_pinLow)
            GPIO_clearPin(PE1);
      else
            GPIO_setPin(PE1);
}

static void ILI_dataCommand_Select(ILI_cmdData_e flag)
{
      if(flag == ILI_enableCommand)
            GPIO_clearPin(PE2);
      else
            GPIO_setPin(PE2);
}

static void ILI_delayMS(uint32_t ms)
{
      OS_delay(ms);
}

static void ILI_chipSelect_Init(void)
{
      /* Initialize Chip Select Pin - Initially High */
      GPIO_Init(PA3, GPIO_DigitalOutput, 1);    
}

static void ILI_resetPin_Init(void)
{
      /* Initialize the Reset pin  - Initially High */
      GPIO_Init(PE1, GPIO_DigitalOutput, 1);
}

static void ILI_DataCommandPin_Init(void)
{
      /* Initialize the DC/RS pin (Data/Command)  - Initially DC */
      GPIO_Init(PE2, GPIO_DigitalOutput, 1);
}

void ILI_HardReset(void)
{
      /* Pull the Reset pin to Low */
      GPIO_clearPin(PE1);

      /* Wait till minimum time is elapsed */
      ILI_delayMS(20);

      /* Deassert the Reset Pin to Switch the Display ON */
      GPIO_setPin(PE1);

      /* Wait for the Display to complete the Startup */
      ILI_delayMS(200);
}

void ILI_readReg(uint8_t cmd, uint16_t *rx_buf, uint32_t rx_bitLen)
{
   uint16_t t_txBuf = cmd;
   uint32_t rx_ByteLen = 0;
   uint32_t rx_frameBitLen = 0;

   /* Enable Chip Select */
   ILI_chipSelect(ILI_pinLow);

   /* Set the Display to Command Mode*/
   ILI_dataCommand_Select(ILI_enableCommand);

   /* Send the Command */
   SPI_Send(&t_txBuf, 1);

   /* Set the Display to Data Mode*/
   ILI_dataCommand_Select(ILI_enableData);
   
   /* Derive the SPI0 modules Frame Bit Length */
   if(rx_bitLen > 8)
      rx_frameBitLen = rx_bitLen + 1;
   else
      rx_frameBitLen = rx_bitLen;

   /* Calculate the Number of Bytes from Bit Length */
   rx_ByteLen  = rx_frameBitLen / 8;

   if((rx_frameBitLen % 8) != 0)
      rx_ByteLen = rx_ByteLen + 1;
      
   /* Get the Data from the Dispaly Unit */
   SPI_Receive(rx_buf, rx_ByteLen);

   /* Rearrage the received Bytes according if Bit Length >8bits*/
   if(rx_bitLen > 8)
   {
      for(uint32_t iter = 0; iter < rx_ByteLen - 1; iter++)
      {
         rx_buf[iter] = ((((rx_buf[iter] << 1) & 0xFE) | ((rx_buf[iter + 1] >> 7) & 0x01)) & 0xFF);
      }
   }


   /* Disable Chip Select */
   ILI_chipSelect(ILI_pinHigh);
}

void ILI_writeReg(uint8_t cmd, uint16_t *paramData_buf, uint32_t paramData_bitLen)
{
      uint16_t t_txBuf = cmd;
      uint32_t tx_ByteLen = 0;

      /* Enable Chip Select */
      ILI_chipSelect(ILI_pinLow);

      /* Set the Display to Command Mode*/
      ILI_dataCommand_Select(ILI_enableCommand);

      /* Send the Command */
      SPI_Send(&t_txBuf, 1);

      /* Check if teh Data or Command Parameter needs to be written */
      if(paramData_bitLen > 0)
      {
            /* Set the Display to Data Mode*/
            ILI_dataCommand_Select(ILI_enableData);

            /* Calculate the Number of Bytes from Bit Length */
            tx_ByteLen  = paramData_bitLen / 8;

            if((paramData_bitLen % 8) != 0)
                  tx_ByteLen = tx_ByteLen + 1;

            /* Send the Parameter of the Command / Data to be written in Memory */
            SPI_Send(paramData_buf, tx_ByteLen);
      }

      /* Set the Display to Data Mode*/
      ILI_dataCommand_Select(ILI_enableData);

      /* Disable Chip Select */
      ILI_chipSelect(ILI_pinHigh);
}

void ILI_MemWrite_18bit(ILI_Pixel_type * data, uint32_t length)
{
      /* Shift it according to the 18bit configuration  */
      data->ILI_PixRed = 60 << 2;
      data->ILI_PixBlue = 0;
      data->ILI_PixGreen = 0;      

      /* Send only command to write Pixel Data */
      ILI_writeReg(ILI_CMD_RAMWR, (uint16_t *)&data, 0);

      /* Enable Chip Select */
      ILI_chipSelect(ILI_pinLow);

      /* Set the Display to Data Mode*/
      ILI_dataCommand_Select(ILI_enableData);

      /* Send the Data to be written in Memory */
      for(uint32_t iter = 0; iter < length; iter++)
            SPI_Send((uint16_t *)&data, 3);

      /* Disable Chip Select */
      ILI_chipSelect(ILI_pinHigh);
}

void ILI_MemRead_18bit(void)
{
      /* Read the Pixel Data */
      //ILI_readReg(ILI_CMD_RAMRD, rx_buffer, 5760);
}

void ILI_DriverInit(void)
{
      /* Initialize SPI0 peripheral with configurations suitable for ILI9341 */
      SPI_Init();

      /* Configure Pins for SPI0 */
      Pin_Config(Port_PA, 2, PA2_SSI0CLK);
      Pin_Config(Port_PA, 4, PA4_SSI0RX);
      Pin_Config(Port_PA, 5, PA5_SSI0TX);
      
      /* Initialize the Pins */
      ILI_chipSelect_Init();
      ILI_resetPin_Init();
      ILI_DataCommandPin_Init();

      /* Reset the Driver IC */
      ILI_HardReset();
    
}