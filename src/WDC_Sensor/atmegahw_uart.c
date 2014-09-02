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
 * @note    Global interrupts must be set for this to work.
 * @param   baud  The UART baudrate.
 * @retval  None.
 */
void atmegahw_uart_init(uint32_t baud)
{
  //
  // Set the baud rate
  //
  atmegahw_uart_set_baud(baud);

  //
  // Configure and enable the UART interrupts.
  // 
  UCSR0B = 
    (1 << RXCIE0) |   // Interrupt on Receive
    (1 << RXEN0)  |   // Enable UART Receiver
    (1 << TXEN0);     // Enable UART Transmitter
  UCSR0C = // 8-N-1
    (0 << UMSEL01)  |
    (0 << UMSEL00)  | // Asynchronous UART
    (0 << UPM01)    |
    (0 << UPM00)    | // No parity bit
    (0 << USBS0)    | // 1 stop-bit
    (1 << UCSZ01)   |
    (1 << UCSZ00);    // 8-bit data
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

/**
 *  @brief  Interupt Service Routine for the UART Receiver
 */
ISR(USART_RX_vect)
{
  
}

/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

