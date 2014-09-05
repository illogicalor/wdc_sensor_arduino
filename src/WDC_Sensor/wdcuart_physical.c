/**
  ******************************************************************************
  * @file    wdcuart_physical.c
  * @author  Alex Hsieh
  * @version V0.0.1
  * @date    03-Sep-2014
  * @brief   Wearable Device Companion (WDC) physical-link layer for the WDC
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


/* Includes ----------------------------------------------------------------- */
#include <avr/interrupt.h>
#include <string.h>
#include "Arduino.h"
#include "wdcuart_physical.h"
#include "atmegahw_uart.h"

/* Defines ------------------------------------------------------------------ */
#define mADVANCE_QUEUE_TAIL()   \
        do \
        { \
          wdc_queue_tail = (wdc_queue_tail + 1) % WDC_PLL_QUEUE_DEPTH; \
          wdc_queue_size++; \
        } while (0);

/* Private Variables -------------------------------------------------------- */
static volatile bool wdcbus_active = false;
static uint8_t wdc_queue[WDC_PLL_QUEUE_DEPTH][WDC_PLL_MAX_FRAME_SIZE];
static volatile uint16_t wdc_queue_head = 0, wdc_queue_tail = 0;
static volatile uint16_t wdc_queue_size = 0;

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
  // TODO move away from Arduino code?
  //
  pinMode(WDC_EN_PIN, INPUT_PULLUP);
  attachInterrupt(WDC_EN_PIN, WDC_PLLIntHandler, FALLING);

  //
  // Initialize the UART to the default baud rate.  
  //
  AtmegaHW_UARTInit(WDC_DEFAULT_BAUD_RATE);
  sei();
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
 * @brief   
 * @retval  None.
 */
void WDC_PLLWritePacket(uint8_t *packet, uint16_t len)
{
  
}

/**
 * @brief   
 * @retval  None.
 */
void WDC_PLLReadPacket(uint8_t *packet)
{
  if (wdc_queue_size > 0)
  {
    
  }
}

/* Private Function Definitions --------------------------------------------- */
/**
 * @brief   
 * @retval  None.
 */
static void WDC_PLLIntHandler(void)
{
  uint16_t rcv_len;

  //
  // If WDC Enable Pin is LOW, a falling edge was caught and the
  // WDC_BUS is active. If it is HIGH, a rising edge was caught and
  // the WDC_BUS is inactive.
  //
  if (digitalRead(WDC_EN_PIN) == LOW)
  {
    wdcbus_active = true;

    //
    // Start of frame detected. Flush the RX buffer and prep for
    // receiving the raw packet data.
    //
    AtmegaHW_UARTFlushReceiveBuffer();
  }
  else if (digitalRead(WDC_EN_PIN) == HIGH)
  {
    wdcbus_active = false;

    //
    // End of frame detected. Store the received data in FIFO.
    //
    if (wdc_queue_size < WDC_PLL_QUEUE_DEPTH)
    {
      rcv_len = AtmegaHW_UARTCanRead();
      AtmegaHW_UARTRead(wdc_queue[wdc_queue_tail], rcv_len);
      mADVANCE_QUEUE_TAIL();
    }
  }
}

/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

