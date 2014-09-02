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
#include "Arduino.h"
#include "wdcuart_protocol.h"

/* Defines ------------------------------------------------------------------ */

/* Local Variables ---------------------------------------------------------- */
static volatile boolean wdcbus_active = false;

/* Local Function Prototypes ------------------------------------------------ */
static void wdc_int_handler(void);

/* Function Definitions ----------------------------------------------------- */
/**
 *  @brief  
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
  atmegahw_uart_init(DEFAULT_BAUD_RATE);
}

/* Local Function Definitions ----------------------------------------------- */
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

/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

