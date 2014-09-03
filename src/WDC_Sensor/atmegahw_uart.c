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
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "atmegahw_uart.h"

/* Defines ------------------------------------------------------------------ */
#ifndef F_CPU
#error  "F_CPU must be defined at the expected clock frequency."
#endif /* F_CPU */

#ifndef NULL
#define NULL  ((void *)0)
#endif /* NULL */

/* Private Variables -------------------------------------------------------- */
static volatile uint8_t rxbuf[RXBUF_SIZE];
static volatile uint16_t rxbuf_head, rxbuf_tail;
static volatile uint8_t txbuf[TXBUF_SIZE];
static volatile uint16_t txbuf_head, txbuf_tail;

static uart_int_callback_t rx_callback = NULL;
static uart_int_callback_t tx_callback = NULL;

/* Local Function Prototypes ------------------------------------------------ */

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
    (1 << RXCIE0) |   // Enable Interrupt on Receive Complete.
    (0 << TXCIE0) |   // Disable Interrupt on Transmit Complete.
    (0 << UDRIE0) |   // Disable Interrupt on Data Register Empty.
    (1 << RXEN0)  |   // Enable UART Receiver.
    (1 << TXEN0);     // Enable UART Transmitter.
  UCSR0C = // 8-N-1
    (0 << UMSEL01)  |
    (0 << UMSEL00)  | // Asynchronous UART.
    (0 << UPM01)    |
    (0 << UPM00)    | // No parity bit.
    (0 << USBS0)    | // 1 stop-bit.
    (1 << UCSZ01)   |
    (1 << UCSZ00);    // 8-bit data.
}

/**
 * @brief   Disable the UART hardware.
 * @retval  None.
 */
void atmegahw_uart_deinit(void)
{
  // TODO
}

/**
 * @brief   Set the UART baud rate.
 * @param   baud  The UART baudrate.
 * @retval  None.
 */
void atmegahw_uart_set_baud(uint32_t baud)
{
  uint32_t baud_prescale;

  //
  // Sanity check. Make sure the baudrate is possible.
  //
  if (baud > UART_MAX_BAUD_RATE)
  {
    return;
  }
 
  baud_prescale = (((F_CPU / (baud * 16UL))) - 1);

  UBRR0L = (uint8_t)(baud & 0xFF);
  UBRR0H = (uint8_t)((baud >> 8) & 0xFF);
}

/**
 * @brief   Get the number of bytes that can be read from the UART
 *          receive buffer.
 * @retval  The number of bytes avaiabe to read from the UART receive buffer.
 */
int atmegahw_uart_canread(void)
{
  uint16_t len;
  uint16_t head = rxbuf_head, tail = rxbuf_tail;

  if (head <= tail)
  {
    len = tail = head;
  }
  else
  {
    len = RXBUF_SIZE - head + tail;
  }

  return len;
}

/**
 * @brief   Read data (if available) received over UART.
 * @param   buf The buffer to receive data.
 * @param   len Number of expected bytes to read.
 * @retval  Number of actual bytes read.
 */
int atmegahw_uart_read(uint8_t *buf, uint16_t len)
{
  uint16_t tail = rxbuf_tail;

  if (len && buf)
  {
    //
    // Sanity check the length parameter
    //
    if (len > atmegahw_uart_canread())
    {
      len = atmegahw_uart_canread();
    }

    //
    // Retrieve the data.
    //
    if (rxbuf_head <= tail)
    {
      memcpy(buf, rxbuf + rxbuf_head, len);
      rxbuf_head += len;
    }
    else
    {
      if ((RXBUF_SIZE - rxbuf_head) >= len)
      {
        memcpy(buf, rxbuf + rxbuf_head, len);
        rxbuf_head += len;
        if (rxbuf_head == RXBUF_SIZE)
        {
          rxbuf_head = 0;
        }
      }
      else
      {
        uint16_t len0 = RXBUF_SIZE - rxbuf_head;
        uint16_t len1 = len - len0;

        memcpy(buf, rxbuf + rxbuf_head, len0);
        memcpy(buf + len0, rxbuf, len1);
        rxbuf_head = len1;
      }
    }
  }
}

/**
 * @brief   Write data over UART.
 * @param   buf The data buffer.
 * @param   len Length of the data.
 * @retval  Number of bytes written over UART.
 */
int atmegahw_uart_write(const uint8_t *buf, uint16_t len)
{
  uint16_t head = txbuf_head;

  //
  // Sanity check the length and buffer.
  //
  if (len && buf)
  {
    if (head <= txbuf_tail)
    {
      if (txbuf_head == 0)
      {
        if (((TXBUF_SIZE - 1) - txbuf_tail) >= len)
        {
          memcpy(txbuf + txbuf_tail, buf, len);
          txbuf_tail += len;
        }
        else
        {
          len = (TXBUF_SIZE - 1) - txbuf_tail;
          memcpy(txbuf + txbuf_tail, buf, len);
          txbuf_tail = TXBUF_SIZE - 1;
        }
      }
      else
      {
        if ((TXBUF_SIZE - txbuf_tail) >= len)
        {
          memcpy(txbuf + txbuf_tail, buf, len);
          txbuf_tail += len;
          if (txbuf_tail == TXBUF_SIZE)
          {
            txbuf_tail = 0;
          }
        }
        else
        {
          uint16_t len0 = TXBUF_SIZE - txbuf_tail;
          memcpy(txbuf + txbuf_tail, buf, len0);
          txbuf_tail = 0;
          buf += len0;

          uint16_t len1 = len - len0;
          if (((txbuf_head - 1) - txbuf_tail) >= len1)
          {
            memcpy(txbuf + txbuf_tail, buf, len1);
            txbuf_tail += len1;
          }
          else
          {
            len1 = (head - 1) - txbuf_tail;
            if (len1)
            {
              memcpy(txbuf + txbuf_tail, buf, len1);
              txbuf_tail += len1;
            }
          }

          len = len0 + len1;
        }
      }
    }
    else
    {
      if (((head - 1) - txbuf_tail) >= len)
      {
        memcpy(txbuf + txbuf_tail, buf, len);
        txbuf_tail += len;
      }
      else
      {
        len = (head - 1) - txbuf_tail;
        if (len)
        {
          memcpy(txbuf + txbuf_tail, buf, len);
          txbuf_tail += len;
        }
      }
    }

    //
    // Enable the UART Data Register Empty interrupt.
    //
    UCSR0B |= (1 << UDRIE0);
  }

  return len;
}

/**
 * @brief   Transmits a single character over UART
 * @note    This function blocks until the character is successfully
 *          transferred.
 * @param   c The character to transmit over UART.
 * @retval  
 */
int atmegahw_uart_putchar(char c)
{
  //
  // Wait for empty transmit buffer (blocking).
  //
  while (!(UCSR0A & (1 << UDRE0)));

  //
  // Put the character into the buffer.
  //
  UDR0 = c;

  return c;
}

/**
 * @brief   
 * @retval  
 */
int atmegahw_uart_puts(const char *str)
{
  uint16_t len = strlen(str);
  return atmegahw_uart_write((const uint8_t *)str, len);
}

/**
 * @brief   Flush the UART receive buffer.
 * @retval  None.
 */
void atmegahw_uart_rxbuf_flush(void)
{
  rxbuf_head = rxbuf_tail = 0;
}

/**
 * @brief   Register a callback upon receiving a character over UART.
 * @param   callback  
 * @retval  None.
 */
void atmegahw_uart_register_rx_callback(uart_int_callback_t callback)
{
  rx_callback = callback;
}

/* Private Function Definitions --------------------------------------------- */
/**
 *  @brief  UART RX Complete Handler
 *  @retva  None.
 */
ISR(USART_RX_vect)
{
  uint8_t rxchar;
  uint16_t head = rxbuf_head;

  //
  // Read the received data from the data register
  //
  rxchar = UDR0;

  //
  // Properly add the data to the FIFO
  //
  if (head <= rxbuf_tail)
  {
    if (head == 0)
    {
      if (rxbuf_tail < (RXBUF_SIZE - 1))
      {
        rxbuf[rxbuf_tail++] = rxchar;
      }
    }
    else
    {
      rxbuf[rxbuf_tail++] = rxchar;
      if (rxbuf_tail == RXBUF_SIZE)
      {
        rxbuf_tail = 0;
      }
    }
  }
  else
  {
    if (rxbuf_tail < (head - 1))
    {
      rxbuf[rxbuf_tail++] = rxchar;
    }
  }

  //
  // Process user-defined UART receive callback
  //
  if (rx_callback)
  {
    rx_callback(rxchar);
  }
}

/**
 *  @brief  UART Data Register Empty Handler
 *  @retva  None.
 */
ISR(USART_UDRE_vect)
{
  uint8_t txchar;
  uint16_t tail = txbuf_tail;

  //
  // Get the next data byte to transmit over UART from the FIFO
  //
  txchar = txbuf[txbuf_head++];

  //
  // Transmit the data byte over UART.
  //
  UDR0 = txchar;  // This clears the UDRE0 bit automatically.
  if (txbuf_head == TXBUF_SIZE)
  {
    txbuf_head = 0;
  }

  //
  // Disable the interrupt if all the data in the FIFO has
  // been transmitted.
  //
  if (txbuf_head == tail)
  {
    UCSR0B &= ~(1 << UDRIE0); // Disable Interrupt on Data Register Empty.
  }

  //
  // Process user-defined UART transmit callback
  //
  if (tx_callback)
  {
    tx_callback(txchar);
  }
}
/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

