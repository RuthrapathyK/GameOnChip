#include "display.h"
#include "spi.h"
#include "gpio.h"
#include "pinconfig.h"
#include "scheduler.h"

uint16_t tx_buffer[10] = {0};
uint16_t rx_buffer[10] = {0};


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
    
    /* Initialize Chip Select Pin */
    GPIO_Init(PA3, GPIO_DigitalOutput, 1);

    /* Initialize the Reset pin */
    GPIO_Init(PE1, GPIO_DigitalOutput, 1);
    
    /* Initialize the DC/RS pin (Data/Command) */
    GPIO_Init(PE2, GPIO_DigitalOutput, 1);   

}

void Disp_Run(void)
{
   tx_buffer[0] = 0x04;
   
   /* Enable Chip Select */
   Disp_chipSelect(Disp_pinLow);

   /* Set the Display to Command Mode*/
   Disp_dataCommand_Select(Disp_enableCommand);

   /* Send the Command */
   SPI_Send(tx_buffer, 1);

//    /* Disable Chip Select */
//    Disp_chipSelect(Disp_pinHigh);

//    OS_delay(1);

//    /* Enable Chip Select */
//    Disp_chipSelect(Disp_pinLow);

//    /* Set the Display to Data Mode*/
//    Disp_dataCommand_Select(Disp_enableData);
   
   /* Get the Data from the Dispaly Unit */
   SPI_Receive(rx_buffer, 4);

   /* Disable Chip Select */
   Disp_chipSelect(Disp_pinHigh);
}
