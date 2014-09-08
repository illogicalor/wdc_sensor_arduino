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

// UART Baudrate Settings
#ifdef WDC_PROTOCOL_VERSION
#define WDC_UART_BAUD           500000UL
#else
#define WDC_UART_BAUD           500000UL
#endif

// Frame Settings
#define WDC_PLL_QUEUE_DEPTH     2
#define WDC_PLL_MAX_FRAME_SIZE  50 // Max size is in bytes.

/* Exported Types ----------------------------------------------------------- */
typedef struct
{
  uint16_t  len;
  uint8_t   payload[WDC_PLL_MAX_FRAME_SIZE];
} pll_packet_t;

typedef void (*eof_callback_t)(void);
typedef void (*sof_callback_t)(void);

/* Function Prototypes ------------------------------------------------------ */
void  WDC_PLLInit(void);
void  WDC_PLLDeinit(void);
bool  WDC_IsBusActive(void);
void  WDC_PLLWritePacket(uint8_t *packet, uint16_t len);
bool  WDC_PLLCanRead(void);
bool  WDC_PLLReadPacket(uint8_t *packet);

void  WDC_PLLRegisterStartOfFrameCallback(eof_callback_t cb);
void  WDC_PLLRegisterEndOfFrameCallback(eof_callback_t cb);

#ifdef __cplusplus
}
#endif

#endif /* __WDCUART_PHYSICAL_H__ */
/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

