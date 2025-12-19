#ifndef __ILI9341_H
#define __ILI9341_H

#include "common.h"

/* Command defines sorted ascending by value */
#define ILI_CMD_NOP              0x00
#define ILI_CMD_SW_RESET         0x01
#define ILI_CMD_READ_DISP_IDENT  0x04
#define ILI_CMD_READ_DISP_STATUS 0x09

/* Read / query commands */
#define ILI_CMD_READ_POWER_MODE    0x0A
#define ILI_CMD_READ_MADCTL        0x0B
#define ILI_CMD_READ_PIXEL_FORMAT  0x0C
#define ILI_CMD_READ_IMAGE_FORMAT  0x0D
#define ILI_CMD_READ_SIGNAL_MODE   0x0E
#define ILI_CMD_READ_SELFDIAG_RESULT   0x0F

/* Sleep / power */
#define ILI_CMD_SLPIN             0x10
#define ILI_CMD_SLPOUT            0x11
#define ILI_CMD_PTLON             0x12
#define ILI_CMD_NORON             0x13

/* Inversion / gamma */
#define ILI_CMD_INVOFF            0x20
#define ILI_CMD_INVON             0x21
#define ILI_CMD_GAMMASET          0x26

/* Display ON/OFF */
#define ILI_CMD_DISPOFF           0x28
#define ILI_CMD_DISPON            0x29

/* Column/Row and Memory access */
#define ILI_CMD_CASET             0x2A /* Column Address Set */
#define ILI_CMD_RASET             0x2B /* Row Address Set (Page Address Set) */
#define ILI_CMD_RAMWR             0x2C /* Memory Write */
#define ILI_CMD_COLSET             0x2A /* Color Set */
#define ILI_CMD_RAMRD             0x2E /* Memory Read */

/* Partial / tearing / idle */
#define ILI_CMD_PARTIAL_AREA      0x30
#define ILI_CMD_VERTICAL_SCROLL      0x33
#define ILI_CMD_TEARING_LINE_OFF  0x34
#define ILI_CMD_TEARING_LINE_ON   0x35

/* Memory Access Control / Pixel format */
#define ILI_CMD_MADCTL            0x36 /* Memory Access Control */
#define ILI_CMD_VSCRSADD          0x37 /* Vertical Scrolling Start Address */
#define ILI_CMD_IDLE_MODE_OFF     0x38
#define ILI_CMD_IDLE_MODE_ON      0x39
#define ILI_CMD_COLMOD            0x3A /* Pixel Format Set */

/* Memory continue / read continue */
#define ILI_CMD_MEM_CONTINUE      0x3C /* Memory Write Continue */
#define ILI_CMD_MEM_READ_CONT     0x3E /* Memory Read Continue */

/* Power control / display settings */
#define ILI_CMD_SET_TEAR_SCANLINE           0x44
#define ILI_CMD_GET_SCANLINE           0x45

/* Brightness and Display Control */
#define ILI_CMD_WR_DISPLAY_BRIGHTNESS       0x51
#define ILI_CMD_RD_DISPLAY_BRIGHTNESS       0x52
#define ILI_CMD_WR_DISPLAY_CTRL             0x53
#define ILI_CMD_RD_DISPLAY_CTRL             0x54
#define ILI_CMD_WR_DISPLAY_CABC             0x55
#define ILI_CMD_RD_DISPLAY_CABC             0x56
#define ILI_CMD_WR_DISPLAY_CABC_MIN         0x5E
#define ILI_CMD_WR_DISPLAY_CABC_MAX         0x5F

/* Read ID / chip identification */
#define ILI_CMD_READ_ID1          0xDA
#define ILI_CMD_READ_ID2          0xDB
#define ILI_CMD_READ_ID3          0xDC

// /* Frame control / display function */
// #define ILI_CMD_FRMCTR1           0xB1
// #define ILI_CMD_FRMCTR2           0xB2
// #define ILI_CMD_FRMCTR3           0xB3
// #define ILI_CMD_INVCTR            0xB4
// #define ILI_CMD_DISSET5           0xB6

// /* Power control */
// #define ILI_CMD_PWCTR1            0xC0
// #define ILI_CMD_PWCTR2            0xC1
// #define ILI_CMD_PWCTR3            0xC2
// #define ILI_CMD_PWCTR4            0xC3
// #define ILI_CMD_PWCTR5            0xC4
// #define ILI_CMD_VMCTR1            0xC5
// #define ILI_CMD_VMCTR2            0xC7

// /* Gamma */
// #define ILI_CMD_GMCTRP1           0xE0 /* Positive Gamma Correction */
// #define ILI_CMD_GMCTRN1           0xE1 /* Negative Gamma Correction */

// /* MADCTL (Memory Access Control) flags - used with ILI_CMD_MADCTL (0x36) */
// #define ILI_MADCTL_MY  0x80 /* Row Address Order */
// #define ILI_MADCTL_MX  0x40 /* Column Address Order */
// #define ILI_MADCTL_MV  0x20 /* Row/Column Exchange */
// #define ILI_MADCTL_ML  0x10 /* Vertical Refresh Order */
// #define ILI_MADCTL_RGB 0x00 /* Red-Green-Blue pixel order */
// #define ILI_MADCTL_BGR 0x08 /* Blue-Green-Red pixel order */
// #define ILI_MADCTL_MH  0x04 /* Horizontal Refresh Order */

// /* Pixel Formats (used with ILI_CMD_COLMOD / ILI_CMD_PIXFMT) */
// #define ILI_PIXFMT_16BPP 0x55 /* 16 bits/pixel (RGB565) */
// #define ILI_PIXFMT_18BPP 0x66 /* 18 bits/pixel (RGB666) */


typedef enum{
    ILI_pinLow,
    ILI_pinHigh,
    ILI_Max
}ILI_PinState_e;

typedef enum{
    ILI_enableCommand,
    ILI_enableData,
    ILI_enableMax
}ILI_cmdData_e;

typedef struct  __attribute__((packed)) {
    uint16_t ILI_PixBlue;
    uint16_t ILI_PixGreen;
    uint16_t ILI_PixRed;
}ILI_Pixel_type;

void ILI_DriverInit(void);
void ILI_HardReset(void);
void ILI_readReg(uint8_t cmd, uint16_t *rx_buf, uint32_t rx_bitLen);
void ILI_writeReg(uint8_t cmd, uint16_t *tx_buf, uint32_t tx_bitLen);
void ILI_MemWrite_18bit(ILI_Pixel_type * pix_dat, uint32_t length);
void ILI_MemRead_18bit(void);

#endif