/**
  ******************************************************************************
  * @file    wdcuart_datalink.c
  * @author  Alex Hsieh
  * @version V0.0.1
  * @date    01-Sep-2014
  * @brief   Wearable Device Companion (WDC) data-link layer for the WDC
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
#include "wdcuart_datalink.h"

/* Defines ------------------------------------------------------------------ */

/* Private Variables -------------------------------------------------------- */

/* Private Function Prototypes ---------------------------------------------- */
static void WDC_DLLEndOfFrameHandler(void);

/* Function Definitions ----------------------------------------------------- */
/**
 * @brief   Initialize the data-link layer for the WDC communication
 *          protocol.
 * @retval  None.
 */
void WDC_DLLInit(void)
{
  //
  // Initialize the physical-link layer of the WDC communication protocol.
  //
  WDC_PLLInit();

  //
  // Register the End-of-Frame callback.
  //
  WDC_PLLRegisterEndOfFrameCallback(WDC_DLLEndOfFrameHandler);
}

/**
 * @brief   De-initialize the data-link layer for the WDC communication
 *          protocol.
 * @retval  None.
 */
void WDC_DLLDeinit(void)
{
  // TODO
}

/**
 * @brief   Handler for WDC frames.
 * @retval  None.
 */
static void WDC_DLLEndOfFrameHandler(void)
{
  //
  // Read the Data-Link Layer Header byte to determine
  // the type of packet and how to handle it.
  //
  if (WDC_PLLCanRead())
  {
    
  }
}

/* Private Function Definitions --------------------------------------------- */

/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

