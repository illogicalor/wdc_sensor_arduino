/**
  ******************************************************************************
  * @file    atmegahw_uart.h
  * @author  Alex Hsieh
  * @version V0.0.1
  * @date    01-Sep-2014
  * @brief   Low-level UART driver for the Wearable Device Companion (WDC)
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

#ifndef __ATMEGAHW_UART_H__
#define __ATMEGAHW_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include <stdint.h>

/* Exported Types ----------------------------------------------------------- */
typedef void (*uart_int_callback_t)(uint8_t);

/* Defines ------------------------------------------------------------------ */
// UART Baud Rate
#define UART_MAX_BAUD_RATE  (F_CPU / 16UL)
#define RXBUF_SIZE          128
#define TXBUF_SIZE          128

/* Function Prototypes ------------------------------------------------------ */
void  AtmegaHW_UARTInit(uint32_t baud);
void  AtmegaHW_UARTDeinit(void);
void  AtmegaHW_UARTSetBaud(uint32_t baud);

int   AtmegaHW_UARTCanRead(void);
int   AtmegaHW_UARTRead(uint8_t *buf, uint16_t len);
int   AtmegaHW_UARTWriteBytesRemaining(void);
int   AtmegaHW_UARTWrite(const uint8_t *buf, uint16_t len);
int   AtmegaHW_UARTPutChar(char c);
int   AtmegaHW_UARTPuts(const char *str);
void  AtmegaHW_UARTFlushReceiveBuffer(void);
void  AtmegaHW_UARTFlushTransmitBuffer(void);
void  AtmegaHW_UARTDeleteReceiveChar(void);

#ifdef __cplusplus
}
#endif

#endif /* __ATMEGAHW_UART_H__ */
/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

