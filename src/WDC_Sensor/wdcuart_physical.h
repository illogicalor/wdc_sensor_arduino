/**
  ******************************************************************************
  * @file    wdcuart_physical.h
  * @author  Alex Hsieh
  * @version V0.0.1
  * @date    03-Sep-2014
  * @brief   Wearable Device Companion (WDC) physical-link layer (PHY) for the
  *          WDC communication protocol (UART).
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
#if WDC_PROTOCOL_VERSION == 0x0100
#define WDC_UART_BAUD           500000UL
#else
#define WDC_UART_BAUD           500000UL
#endif

/* Exported Types ----------------------------------------------------------- */
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

