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
// UART Baudrate Settings
#if (UART_MAX_BAUD_RATE < WDC_UART_BAUD)
#error "WDC Buadrate is not supported on this device."
#endif

#define mADVANCE_RXQUEUE_TAIL() \
        do \
        { \
          wdc_rxqueue_tail = (wdc_rxqueue_tail + 1) % WDC_PLL_QUEUE_DEPTH; \
          wdc_rxqueue_size++; \
        } while (0);

#define mADVANCE_RXQUEUE_HEAD() \
        do \
        { \
          wdc_rxqueue_head = (wdc_rxqueue_head + 1) % WDC_PLL_QUEUE_DEPTH; \
          wdc_rxqueue_size--; \
        } while (0);

#define mADVANCE_TXQUEUE_TAIL() \
        do \
        { \
          wdc_txqueue_tail = (wdc_txqueue_tail + 1) % WDC_PLL_QUEUE_DEPTH; \
          wdc_txqueue_size++; \
        } while (0);

#define mADVANCE_TXQUEUE_HEAD() \
        do \
        { \
          wdc_txqueue_head = (wdc_txqueue_head + 1) % WDC_PLL_QUEUE_DEPTH; \
          wdc_txqueue_size--; \
        } while (0);

/* Private Variables -------------------------------------------------------- */
static volatile bool wdcbus_active = false;
static pll_packet_t wdc_rxqueue[WDC_PLL_QUEUE_DEPTH];
static volatile uint16_t wdc_rxqueue_head = 0, wdc_rxqueue_tail = 0;
static volatile uint16_t wdc_rxqueue_size = 0;
static pll_packet_t wdc_txqueue[WDC_PLL_QUEUE_DEPTH];
static volatile uint16_t wdc_txqueue_head = 0, wdc_txqueue_tail = 0;
static volatile uint16_t wdc_txqueue_size = 0;

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
  // TODO move away from Arduino code!!
  //
  pinMode(WDC_EN_PIN, INPUT_PULLUP);
  attachInterrupt(WDC_EN_PIN, WDC_PLLIntHandler, FALLING);

  //
  // Initialize the UART to the default baud rate.  
  //
  AtmegaHW_UARTInit(WDC_UART_BAUD);
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
bool WDC_PLLWritePacket(uint8_t *packet)
{
  if (wdc_txqueue_size < WDC_PLL_QUEUE_DEPTH)
  {
    memcpy(wdc_txqueue[wdc_txqueue_tail].payload, packet,
           WDC_PLL_MAX_FRAME_SIZE);
    mADVANCE_TXQUEUE_TAIL();
    return true;
  }

  return false;
}

/**
 * @brief   Get the number of packets that are in queue.
 * @retval  Number of packets available to read.
 */
uint16_t WDC_PLLCanRead(void)
{
  return wdc_rxqueue_size;
}

/**
 * @brief   Get a received packet (if one exists) from the physical layer.
 * @retval  None.
 */
bool WDC_PLLReadPacket(uint8_t *packet)
{
  if (wdc_rxqueue_size > 0)
  {
    memcpy(packet, wdc_rxqueue[wdc_rxqueue_head].payload,
           wdc_rxqueue[wdc_rxqueue_head].size);
    mADVANCE_RXQUEUE_HEAD();
    return true;
  }

  return false;
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
  // the WDC_BUS is inactive. A single frame starts on a falling edge
  // and ends on a rising edge.
  //
  if (digitalRead(WDC_EN_PIN) == LOW)
  {
    wdcbus_active = true;

    //
    // Start of frame detected. Flush the RX buffer and prep for
    // receiving the raw packet data.
    //
    AtmegaHW_UARTFlushReceiveBuffer();

    //
    // Send a packet from transmit queue if it isn't empty.
    //
    if (wdc_txqueue_size > 0)
    {
      AtmegaHW_UARTWrite(wdc_txqueue[wdc_txqueue_tail].payload,
                         wdc_txqueue[wdc_txqueue_tail].size);
      mADVANCE_TXQUEUE_HEAD();
    }
  }
  else if (digitalRead(WDC_EN_PIN) == HIGH)
  {
    wdcbus_active = false;

    //
    // End of frame detected. Store the received data in FIFO.
    //
    if (wdc_rxqueue_size < WDC_PLL_QUEUE_DEPTH)
    {
      rcv_len = AtmegaHW_UARTCanRead();
      if (rcv_len <= WDC_PLL_MAX_FRAME_SIZE)
      {
        AtmegaHW_UARTRead(wdc_rxqueue[wdc_rxqueue_tail].payload, rcv_len);
        wdc_rxqueue[wdc_rxqueue_tail].size = rcv_len;
        mADVANCE_RXQUEUE_TAIL();
      }
      else
      {
        //
        // Invalid packet received. Discard it?
        //
        AtmegaHW_UARTFlushReceiveBuffer();
      }
    }
    else
    {
      //
      // We had to drop the packet :(.
      //
    }
  }
}

/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

