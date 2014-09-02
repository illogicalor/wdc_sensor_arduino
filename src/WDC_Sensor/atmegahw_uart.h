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

/* Includes ----------------------------------------------------------------- */
#include <stdint.h>

/* Defines ------------------------------------------------------------------ */

/* Function Prototypes ------------------------------------------------------ */
void atmegahw_uart_init(uint32_t baud);
void atmegahw_uart_deinit(void);

#endif /* __ATMEGAHW_UART_H__ */
/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

