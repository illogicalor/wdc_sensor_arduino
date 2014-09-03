/**
  ******************************************************************************
  * @file    wdcuart_protocol.c
  * @author  Alex Hsieh
  * @version V0.0.1
  * @date    01-Sep-2014
  * @brief   Arduino version of the Wearable Device Companion (WDC) for sensors.
  *  
  *          Wearable Device Companion:
  *          A WDC includes a processor and one or more sensors. The processor
  *          collects data from the sensor(s) at a certain frequency and sends
  *          it up to the host (Wearable Device Base). The WDC processor can
  *          additionally choose to post-process the raw data and feed it up to
  *          the Wearable Device Base (WDB) as well. Initially, the WDC goes
  *          through an enumeration stage so the WDB knows what to expect, as
  *          well as how to control, the WDC.
  *
  *          Please see separate documentation for details on the WDC/WDB spec.
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
#include <avr/interrupt.h>
#include "Arduino.h"
#include "wdcuart_protocol.h"

/* Defines ------------------------------------------------------------------ */

/* Private Variables -------------------------------------------------------- */
static volatile bool wdcbus_active = false;
static volatile bool wdcbus_after_escape = false;
static volatile bool wdcbus_packet_ready = false;

/* Private Function Prototypes ---------------------------------------------- */
static void wdc_int_handler(void);
static void wdc_rx_handler(uint8_t byte);

/* Function Definitions ----------------------------------------------------- */
/**
 *  @brief  Initialize the Wearable Device Companion communications protocol.
 *  @retval None.
 */
void wdc_comm_init(void)
{ 
  //
  // Initialize the WDC_EN pin.
  // The interrupt should initially be set for falling edges.
  //
  pinMode(WDC_EN_PIN, INPUT_PULLUP);
  attachInterrupt(WDC_EN_PIN, wdc_int_handler, FALLING);

  //
  // Initialize the UART to the default baud rate.
  //
  atmegahw_uart_init(WDC_DEFAULT_BAUD_RATE);

  // 
  // Register UART receive callback.
  //
  atmegahw_uart_register_rx_callback(wdc_rx_handler);

  //
  // Enable global interrupts
  //
  sei();
}

/**
 *  @brief  Update the WDC Communications baud rate.
 *  @param  baud  The new UART baud rate.
 *  @retval None.
 */
void wdc_comm_set_baud(uint32_t baud)
{
  atmegahw_uart_set_baud(baud);
}

/* Private Function Definitions --------------------------------------------- */
/**
 *  @brief  WDC_EN pin toggle interrupt handler.
 *  @retval None.
 */
static void wdc_int_handler(void)
{
  //
  // If WDC Enable Pin is LOW, a falling edge was caught and the
  // WDC_BUS is active. If it is HIGH, a rising edge was caught and
  // the WDC_BUS is inactive.
  //
  if (digitalRead(WDC_EN_PIN) == LOW)
  {
    wdcbus_active = true;
  }
  else if (digitalRead(WDC_EN_PIN) == HIGH)
  {
    wdcbus_active = false;
  }
}

/**
 *  @brief  
 *  @retval None.
 */
static void wdc_rx_handler(uint8_t byte)
{
  if (wdcbus_after_escape) {
    wdcbus_after_escape = false;
  } else {
    if (byte == WDC_START_FLAG) {
      atmegahw_uart_rxbuf_flush();
    } else if (byte == WDC_END_FLAG) {
      atmegahw_uart_rxchar_delete();
      wdcbus_packet_ready = 1;
    } else if (byte == WDC_ESCAPE) {
      atmegahw_uart_rxchar_delete();
      wdcbus_after_escape = 1;
    }
  }
}
/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

