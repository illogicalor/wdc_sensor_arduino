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
#include "wdcuart_physical.h"
#include "wdcuart_datalink.h"

/* Defines ------------------------------------------------------------------ */

/* Private Variables -------------------------------------------------------- */
static volatile bool wdcbus_active = false;
static volatile bool wdcbus_after_escape = false;
static volatile bool wdcbus_packet_ready = false;

/* Private Function Prototypes ---------------------------------------------- */
static void WDC_DLLIntHandler(void);
static void WDC_DLLReceiveHandler(uint8_t byte);

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
}

/**
 * @brief   De-initialize the data-link layer for the WDC communication
 *          protocol.
 * @retval  None.
 */
void WDC_DLLDeinit(void)
{

}

/* Private Function Definitions --------------------------------------------- */

/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

