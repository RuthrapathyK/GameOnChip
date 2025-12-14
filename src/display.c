#include "display.h"
#include "spi.h"
#include "gpio.h"
#include "pinconfig.h"
#include "scheduler.h"

uint16_t paramBuff[10] = {0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5};
uint16_t ScanLine = 0;

Display_Pixel_type pixel_data = {0};

uint8_t rgb_red = 0;
uint8_t rgb_blue = 0;
uint8_t rgb_green = 0;

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

static void Disp_delayMS(uint32_t ms)
{
      OS_delay(ms);
}

void Disp_HardReset(void)
{
      /* Pull the Reset pin to Low */
      GPIO_clearPin(PE1);

      /* Wait till minimum time is elapsed */
      Disp_delayMS(20);

      /* Deassert the Reset Pin to Switch the Display ON */
      GPIO_setPin(PE1);

      /* Wait for the Display to complete the Startup */
      Disp_delayMS(200);
}

void Disp_readReg(uint8_t cmd, uint16_t *rx_buf, uint32_t rx_bitLen)
{
   uint16_t t_txBuf = cmd;
   uint32_t rx_ByteLen = 0;
   uint32_t rx_frameBitLen = 0;

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
   Disp_chipSelect(Disp_pinHigh);
}

void Disp_writeReg(uint8_t cmd, uint16_t *paramData_buf, uint32_t paramData_bitLen)
{
      uint16_t t_txBuf = cmd;
      uint32_t tx_ByteLen = 0;

      /* Enable Chip Select */
      Disp_chipSelect(Disp_pinLow);

      /* Set the Display to Command Mode*/
      Disp_dataCommand_Select(Disp_enableCommand);

      /* Send the Command */
      SPI_Send(&t_txBuf, 1);

      /* Check if teh Data or Command Parameter needs to be written */
      if(paramData_bitLen > 0)
      {
            /* Set the Display to Data Mode*/
            Disp_dataCommand_Select(Disp_enableData);

            /* Calculate the Number of Bytes from Bit Length */
            tx_ByteLen  = paramData_bitLen / 8;

            if((paramData_bitLen % 8) != 0)
                  tx_ByteLen = tx_ByteLen + 1;

            /* Send the Parameter of the Command / Data to be written in Memory */
            SPI_Send(paramData_buf, tx_ByteLen);
      }

      /* Set the Display to Data Mode*/
      Disp_dataCommand_Select(Disp_enableData);

      /* Disable Chip Select */
      Disp_chipSelect(Disp_pinHigh);
}

void Disp_setBrightness(uint8_t bright_val)
{
      uint16_t t_val =  bright_val;

      /* Set the Brightness Value */
      Disp_writeReg(DISP_CMD_WR_DISPLAY_BRIGHTNESS, &t_val, 8);  
      
      Disp_delayMS(25);
}

uint16_t Disp_getScanLine(void)
{
   uint16_t ret_val = 0;
   uint16_t t_data[2] = {0};

   Disp_readReg(DISP_CMD_GET_SCANLINE, t_data, 16);

   ret_val = (((t_data[0] << 8) | t_data[1]) & 0x3FF);

   return ret_val;
}

void Disp_Init(void)
{
      uint16_t selfDiag_1 = 0;
      uint16_t selfDiag_2 = 0;

      /* Initialize SPI0 peripheral with configurations suitable for ILI9341 */
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
      Disp_HardReset();

      /* Read Diagnostic bits */
      Disp_readReg(DISP_CMD_READ_SELFDIAG_RESULT, &selfDiag_1, 8);

      /* Set the Display Module to Sleep Out */
      Disp_writeReg(DISP_CMD_SLPOUT, paramBuff, 0);
      Disp_delayMS(200);

      /* Check whether the Read Diagnostic bits are inverted */
      Disp_readReg(DISP_CMD_READ_SELFDIAG_RESULT, &selfDiag_2, 8);
      if(((selfDiag_1 ^ selfDiag_2) >> 6) != 3)
            while(1);

      /* Idle mode OFF */
      Disp_writeReg(DISP_CMD_IDLE_MODE_OFF, paramBuff, 0);

      /* Normal Mode ON */
      Disp_writeReg(DISP_CMD_NORON, paramBuff, 0);

      /* Change the Brightness - Enable the Brightness and Backlight Modules*/
      paramBuff[0] = (1<<5 | 1<<2);
      Disp_writeReg(DISP_CMD_WR_DISPLAY_CTRL, paramBuff, 8);

      /* Set the Color Mode Pixel as 18bit- COLMOD*/
      paramBuff[0] = 0x66;
      Disp_writeReg(DISP_CMD_COLMOD, paramBuff, 0);

      /* Display ON */
      Disp_writeReg(DISP_CMD_DISPON, paramBuff, 0);

      /* Set Column Address */
      paramBuff[0] = 0x00; // SC15:SC8
      paramBuff[1] = 0x00; // SC7:SC0
      paramBuff[2] = 0x00; // EC15:EC8
      paramBuff[3] = 0xEF; // EC7:EC0
      Disp_writeReg(DISP_CMD_CASET, paramBuff, 32);

      /* Set the Page Address */
      paramBuff[0] = 0x00; // SP15:SP8
      paramBuff[1] = 0x00; // SP7:SP0
      paramBuff[2] = 0x01; // EP15:EP8
      paramBuff[3] = 0x3F; // EP7:EP0
      Disp_writeReg(DISP_CMD_RASET, paramBuff, 32);
}
void Disp_MemoryWrite_18bit(void)
{
      /* Load the Pixel Data to Buffer */
      pixel_data.Pixel_Red = rgb_red << 2;
      pixel_data.Pixel_Blue = rgb_blue << 2;
      pixel_data.Pixel_Green = rgb_green << 2;      

      /* Send only command to write Pixel Data */
      Disp_writeReg(DISP_CMD_RAMWR, (uint16_t *)&pixel_data, 0);

      /* Enable Chip Select */
      Disp_chipSelect(Disp_pinLow);

      /* Set the Display to Data Mode*/
      Disp_dataCommand_Select(Disp_enableData);

      /* Send the Data to be written in Memory */
      for(uint32_t iter = 0; iter < 240 * 320; iter++)
            SPI_Send((uint16_t *)&pixel_data, 3);

      /* Disable Chip Select */
      Disp_chipSelect(Disp_pinHigh);
}

void Disp_MemoryRead_18bit()
{
      /* Set Column Address */
      paramBuff[0] = 0x00; // SC15:SC8
      paramBuff[1] = 0x00; // SC7:SC0
      paramBuff[2] = 0x00; // EC15:EC8
      paramBuff[3] = 0xEF; // EC7:EC0
      Disp_writeReg(DISP_CMD_CASET, paramBuff, 32);

      /* Set the Page Address */
      paramBuff[0] = 0x00; // SP15:SP8
      paramBuff[1] = 0x00; // SP7:SP0
      paramBuff[2] = 0x00; // EP15:EP8
      paramBuff[3] = 0xEF; // EP7:EP0
      Disp_writeReg(DISP_CMD_RASET, paramBuff, 32);

      /* Read the Pixel Data */
      //Disp_readReg(DISP_CMD_RAMRD, rx_buffer, 5760);
}
void Disp_Run(void)
{
      Disp_MemoryWrite_18bit();
//      Disp_MemoryRead_18bit();
//     OS_delay(1000);
}