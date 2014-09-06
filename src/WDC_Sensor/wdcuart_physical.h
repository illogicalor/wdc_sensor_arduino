/**
  ******************************************************************************
  * @file    wdcuart_physical.h
  * @author  Alex Hsieh
  * @version V0.0.1
  * @date    03-Sep-2014
  * @brief   Wearable Device Companion (WDC) physical-link layer for the WDC
  *          communication protocol.
  *  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 Illogical OR</center></h2>
  * 
  *
  ******************************************************************************
  */

#ifndef __WDCUART_PHYSICAL_H__
#define __WDCUART_PHYSICAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include <stdint.h>
#include <stdbool.h>

/* Defines ------------------------------------------------------------------ */
// WDC_EN Pin
#define WDC_EN_PIN              2

// UART Baud Rate Settings
#define WDC_DEFAULT_BAUD_RATE   9600
#define WDC_MAX_BAUD_RATE       UART_MAX_BAUD_RATE

// Frame Settings
#define WDC_PLL_QUEUE_DEPTH     2
#define WDC_PLL_FRAME_SIZE      100 // Size is in bytes.

/* Exported Types ----------------------------------------------------------- */

/* Function Prototypes ------------------------------------------------------ */
void      WDC_PLLInit(void);
void      WDC_PLLDeinit(void);
uint16_t  WDC_PLLCanWrite(void);
bool      WDC_PLLWritePacket(uint8_t *packet);
uint16_t  WDC_PLLCanRead(void);
bool      WDC_PLLReadPacket(uint8_t *packet);

#ifdef __cplusplus
}
#endif

#endif /* __WDCUART_PHYSICAL_H__ */
/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

