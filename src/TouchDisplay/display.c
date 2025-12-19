#include "display.h"
#include "../Drivers/SPI/spi.h"
#include "../Drivers/GPIO/gpio.h"
#include "../Drivers/PinMux/pinconfig.h"
#include "../OS/scheduler.h"
#include "ILI9341.h"

uint16_t paramBuff[10] = {0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5};
uint16_t ScanLine = 0;
uint8_t count = 0;

Disp_Pixel_type Diplay_Pixel = {0};

static void Disp_delayMS(uint32_t ms)
{
    OS_delay(ms);
}

void Disp_setBrightness(uint8_t bright_val)
{
      uint16_t t_val =  bright_val;

      /* Set the Brightness Value */
      ILI_writeReg(ILI_CMD_WR_DISPLAY_BRIGHTNESS, &t_val, 8);  
      
      Disp_delayMS(25);
}

uint16_t Disp_getScanLine(void)
{
   uint16_t ret_val = 0;
   uint16_t t_data[2] = {0};

   ILI_readReg(ILI_CMD_GET_SCANLINE, t_data, 16);

   ret_val = (((t_data[0] << 8) | t_data[1]) & 0x3FF);

   return ret_val;
}

void Disp_Init(void)
{
      uint16_t selfDiag_1 = 0;
      uint16_t selfDiag_2 = 0;

      /* Initialize the Display Driver */
      ILI_DriverInit();

      /* Read Diagnostic bits */
      ILI_readReg(ILI_CMD_READ_SELFDIAG_RESULT, &selfDiag_1, 8);

      /* Set the Display Module to Sleep Out */
      ILI_writeReg(ILI_CMD_SLPOUT, paramBuff, 0);
      Disp_delayMS(200);

      /* Check whether the Read Diagnostic bits are inverted */
      ILI_readReg(ILI_CMD_READ_SELFDIAG_RESULT, &selfDiag_2, 8);
      if(((selfDiag_1 ^ selfDiag_2) >> 6) != 3)
            ASSERT(0);

      /* Idle mode OFF */
      ILI_writeReg(ILI_CMD_IDLE_MODE_OFF, paramBuff, 0);

      /* Normal Mode ON */
      ILI_writeReg(ILI_CMD_NORON, paramBuff, 0);

      /* Change the Brightness - Enable the Brightness and Backlight Modules*/
      paramBuff[0] = (1<<5 | 1<<2);
      ILI_writeReg(ILI_CMD_WR_DISPLAY_CTRL, paramBuff, 8);

      /* Set the Color Mode Pixel as 18bit- COLMOD*/
      paramBuff[0] = 0x66;
      ILI_writeReg(ILI_CMD_COLMOD, paramBuff, 0);

      /* Display ON */
      ILI_writeReg(ILI_CMD_DISPON, paramBuff, 0);

      /* Set Maximum Column Address and Page Address i.e Display Resolution */
      Disp_setPixel_Pointer(0, 0, 240, 320);
}

void Disp_setPixel_Pointer(uint16_t cur_col_addr, uint16_t cur_pg_addr, uint16_t max_col_addr, uint16_t max_pg_addr)
{
      ASSERT((max_col_addr <= 240) && (max_pg_addr <= 320) && (cur_col_addr < 240) && (cur_pg_addr < 320));

      uint16_t t_buf[4] = {0};
      uint16_t t_max_col_addr = max_col_addr - 1;
      uint16_t t_max_pg_addr = max_pg_addr - 1;

      /* Set Column Address */
      t_buf[0] = ((cur_col_addr >> 8) & 0x01);   // SC15:SC8
      t_buf[1] = (cur_col_addr & 0xFF);          // SC7:SC0
      t_buf[2] = ((t_max_col_addr >> 8) & 0x01); // EC15:EC8
      t_buf[3] = (t_max_col_addr & 0xFF);        // EC7:EC0
      ILI_writeReg(ILI_CMD_CASET, t_buf, 32);

      /* Set the Page Address */
      t_buf[0] = ((cur_pg_addr >> 8) & 0x01); // SP15:SP8
      t_buf[1] = (cur_pg_addr & 0xFF); // SP7:SP0
      t_buf[2] = ((t_max_pg_addr >> 8) & 0x01); // EP15:EP8
      t_buf[3] = (t_max_pg_addr & 0xFF); // EP7:EP0
      ILI_writeReg(ILI_CMD_RASET, t_buf, 32);

}
void Disp_sendPixels(Disp_Pixel_type *Pixel, uint32_t col_start, uint32_t pg_start, uint32_t length)
{
      ILI_Pixel_type t_pxl_dat = {0};

      /* Set the Pixel Pointer */
      Disp_setPixel_Pointer(col_start, pg_start, 240, 320);

      /* Map the Display data to ILI9341 driver IC */
      t_pxl_dat.ILI_PixRed = Pixel->Pixel_Red;
      t_pxl_dat.ILI_PixBlue = Pixel->Pixel_Blue;
      t_pxl_dat.ILI_PixGreen = Pixel->Pixel_Green;

      /* Send the Pixel data to Driver IC */
      ILI_MemWrite_18bit(&t_pxl_dat, length);
}
void Disp_Run(void)
{
     count %= 4;

     switch(count)
     {
      case 0:
            Diplay_Pixel.Pixel_Red = 63;
            Diplay_Pixel.Pixel_Green = 0;
            Diplay_Pixel.Pixel_Blue = 0;
            Disp_sendPixels(&Diplay_Pixel, 0,0, 240 * 160);
            break;
      case 1:
            Diplay_Pixel.Pixel_Red = 0;
            Diplay_Pixel.Pixel_Green = 0;
            Diplay_Pixel.Pixel_Blue = 63;
            Disp_sendPixels(&Diplay_Pixel, 0,0, 240 * 160);
            break;
      case 2:
            Diplay_Pixel.Pixel_Red = 0;
            Diplay_Pixel.Pixel_Green = 63;
            Diplay_Pixel.Pixel_Blue = 0;
            Disp_sendPixels(&Diplay_Pixel, 0,0, 240 * 160);
            break;
      case 3:
            Diplay_Pixel.Pixel_Red = 0;
            Diplay_Pixel.Pixel_Green = 0;
            Diplay_Pixel.Pixel_Blue = 0;
            Disp_sendPixels(&Diplay_Pixel, 0,0, 240 * 160);
            break;
      case 4:
            Diplay_Pixel.Pixel_Red = 63;
            Diplay_Pixel.Pixel_Green = 63;
            Diplay_Pixel.Pixel_Blue = 63;
            Disp_sendPixels(&Diplay_Pixel, 0,0, 240 * 160);
            break;
      default:
            break;            
     }
     count++;
}