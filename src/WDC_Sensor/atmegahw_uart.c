/**
  ******************************************************************************
  * @file    atmegahw_uart.c
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

/* Includes ----------------------------------------------------------------- */
#include "atmegahw_uart.h"
#include "avr/io.h"

/* Defines ------------------------------------------------------------------ */
#ifndef F_CPU
#define F_CPU   16000000UL
#endif /* F_CPU */

/* Local Variables ---------------------------------------------------------- */

/* Local Function Prototypes ------------------------------------------------ */
static void atmegahw_uart_set_baud(uint32_t baud);

/* Function Definitions ----------------------------------------------------- */
/**
 * @brief   Enable the UART hardware.
 * @param   baud  The UART baudrate.
 * @retval  None.
 */
void atmegahw_uart_init(uint32_t baud)
{
  //
  // Set the baud rate
  //
  atmegahw_uart_set_baud(baud);


}

/**
 * @brief   Disable the UART hardware.
 * @retval  None.
 */
void atmegahw_uart_deinit(void)
{
  // TODO
}

/* Local Function Definitions ----------------------------------------------- */
/**
 * @brief   Set the UART baud rate.
 * @param   baud  The UART baudrate.
 * @retval  None.
 */
static void atmegahw_uart_set_baud(uint32_t baud)
{
  uint32_t baud_prescale = (((F_CPU / (baud * 16UL))) - 1);

  UBRR0L = (uint8_t)(baud & 0xFF);
  UBRR0H = (uint8_t)((baud >> 8) & 0xFF);
}

/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

