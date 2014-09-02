/**
  ******************************************************************************
  * @file    atmegahw_uart.h
  * @author  Alex Hsieh
  * @version V0.0.1
  * @date    01-Sep-2014
  * @brief   Low-level UART driver for the WDC UART protocol.
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
#define RXBUF_SIZE    128

/* Function Prototypes ------------------------------------------------------ */
void atmegahw_uart_init(uint32_t baud);
void atmegahw_uart_deinit(void);
int atmegahw_uart_canread(void);
int atmegahw_uart_read(uint8_t *buf, uint16_t len);
int atmegahw_uart_write(const uint8_t *buf, uint16_t len);
int atmegahw_uart_putchar(char c);
int atmegahw_uart_puts(const char *str);

void atmegahw_uart_rxbuf_flush(void);

void atmegahw_uart_register_rx_callback(uart_int_callback_t callback);

#ifdef __cplusplus
}
#endif

#endif /* __ATMEGAHW_UART_H__ */
/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

