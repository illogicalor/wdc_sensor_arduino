/**
  ******************************************************************************
  * @file    wdcuart_physical.cpp
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


/* Includes ----------------------------------------------------------------- */
#include <string.h>
#include "Arduino.h"
#include "wdcuart_physical.h"

/* Defines ------------------------------------------------------------------ */
// UART Baudrate Settings
#if ((F_CPU / 16UL) < WDC_UART_BAUD)
#error "WDC Buadrate is not supported on this device."
#endif

#ifndef NULL
#define NULL  ((void *)0)
#endif

/* Private Variables -------------------------------------------------------- */
static volatile bool wdcbus_active = false;
static sof_callback_t sof_callback = NULL;
static eof_callback_t eof_callback = NULL;

/* Private Function Prototypes ---------------------------------------------- */
static void WDC_PLLIntHandler(void);

/* Function Definitions ----------------------------------------------------- */
/**
 * @brief   Initialize the physical-link layer for the WDC UART communication
 *          protocol.
 * @retval  None.
 */
void WDC_PLLInit(void)
{
  //
  // Initialize the WDC_EN pin.
  // The interrupt should initially be set for falling edges.
  //
  pinMode(WDC_EN_PIN, INPUT_PULLUP);
  attachInterrupt(WDC_EN_PIN, WDC_PLLIntHandler, FALLING);

  //
  // Initialize the UART to the default baud rate.  
  //
  Serial.begin(WDC_UART_BAUD);
}

/**
 * @brief   De-initialize the physical-link layer for the WDC UART communication
 *          protocol.
 * @retval  None.
 */
void WDC_PLLDeinit(void)
{
  // TODO
}

/**
 * @brief   Check whether the WDC bus is active or not.
 * @retval  True if the bus is currently active. False otherwise.
 */
bool WDC_IsBusActive(void)
{
  return wdcbus_active;
}

/**
 * @brief   
 * @retval  None.
 */
void WDC_PLLWritePacket(uint8_t *packet, uint16_t len)
{
  if ((len > 0) && (packet != NULL))
  {
    Serial.write(packet, len);
  }
}

/**
 * @brief   
 * @retval  True if 
 */
bool WDC_PLLCanRead(void)
{
  return (Serial.available() > 0);
}

/**
 * @brief   Get a received packet (if one exists) from the physical layer.
 * @retval  None.
 */
bool WDC_PLLReadPacket(uint8_t *packet)
{
  if (WDC_PLLCanRead())
  {
    Serial.readBytes((char *)packet, Serial.available());
    return true;
  }

  return false;
}

/**
 * @brief   Register the Start-of-Frame callback.
 * @retval  None.
 */
void WDC_PLLRegisterStartOfFrameCallback(eof_callback_t cb)
{
  sof_callback = cb;
}

/**
 * @brief   Register the End-of-Frame callback.
 * @retval  None.
 */
void WDC_PLLRegisterEndOfFrameCallback(eof_callback_t cb)
{
  eof_callback = cb;
}

/* Private Function Definitions --------------------------------------------- */
/**
 * @brief   
 * @retval  None.
 */
static void WDC_PLLIntHandler(void)
{
  //
  // If WDC Enable Pin is LOW, a falling edge was caught and the
  // WDC_BUS is active. If it is HIGH, a rising edge was caught and
  // the WDC_BUS is inactive. A single frame starts on a falling edge
  // and ends on a rising edge.
  //
  if (digitalRead(WDC_EN_PIN) == LOW)
  {
    wdcbus_active = true;

    //
    // Start of frame detected. Flush the RX buffer and prep for
    // receiving any data.
    //
    if (Serial.available() > 0)
    {
      // TODO this needs to be non-blocking...
      while (Serial.read() >= 0);
    }

    //
    // Service the Start-of-Frame callback.
    //
    if (sof_callback)
    {
      sof_callback();
    }
  }
  else if (digitalRead(WDC_EN_PIN) == HIGH)
  {
    wdcbus_active = false;

    //
    // End of frame detected. Store the received data.
    //
    if (Serial.available() > 0)
    {
      //
      // Service the End-of-Frame callback.
      //
      if (eof_callback)
      {
        eof_callback();
      }
    }
    else
    {
      //
      // Invalid packet received. Discard it.
      // TODO this needs to be non-blocking...
      //
      while (Serial.read() >= 0);
    }
  }
}

/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

