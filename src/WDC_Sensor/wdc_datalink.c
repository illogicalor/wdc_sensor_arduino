/**
  ******************************************************************************
  * @file    wdc_datalink.c
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
#include "wdc_datalink.h"
#include "wdcuart_physical.h" // Change this depending on the desired PHY layer.

/* Defines ------------------------------------------------------------------ */
#define WDC_DLL_QUEUE_SIZE      4

/* Exported Types ----------------------------------------------------------- */
typedef struct
{
  // Note: Must be a packed data structure.
  uint8_t   header;
  uint8_t   payload[WDC_DLL_ENUMERATION_PACKET_LEN - 1];
} dll_enumeration_packet_t;

typedef struct
{
  // Note: Must be a packed data structure.
  uint8_t   header;
  uint8_t   payload[WDC_DLL_REQUEST_PACKET_LEN - 1];
} dll_request_packet_t;

typedef struct
{
  // Note: Must be a packed data structure.
  uint8_t   header;
  uint8_t   payload[WDC_DLL_DATA_PACKET_LEN - 1];
} dll_data_packet_t;

typedef struct
{
  // Note: Must be a packed data structure.
  uint8_t   header;
  uint8_t   payload[WDC_DLL_EVENT_PACKET_LEN - 1];
} dll_event_packet_t;

/* Private Variables -------------------------------------------------------- */
static dll_enumeration_packet_t dll_tx_queue[WDC_DLL_QUEUE_SIZE];
static dll_enumeration_packet_t dll_rx_queue[WDC_DLL_QUEUE_SIZE];

/* Private Function Prototypes ---------------------------------------------- */
static void WDC_DLLStartOfFrameHandler(void);
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
  // Register the Start- and End-of-Frame callback.
  //
  WDC_PLLRegisterEndOfFrameCallback(WDC_DLLEndOfFrameHandler);
  WDC_PLLRegisterStartOfFrameCallback(WDC_DLLStartOfFrameHandler);
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
 * @brief   
 * @retval  
 */
bool WDC_DLLDataTransmitEnumerationPacket(uint8_t *payload)
{

}

/**
 * @brief   
 * @retval  
 */
bool WDC_DLLDataTransmitRequestPacket(uint8_t *payload)
{

}

/**
 * @brief   
 * @retval  
 */
bool WDC_DLLDataTransmitDataPacket(uint8_t *payload)
{

}

/**
 * @brief   
 * @retval  
 */
bool WDC_DLLDataTransmitEventPacket(uint8_t *payload)
{

}

/* Private Function Definitions --------------------------------------------- */
/**
 * @brief   Handler for WDC frames.
 * @retval  None.
 */
static void WDC_DLLStartOfFrameHandler(void)
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
#if 0
    WDC_PLLReadPacket(dll_generic_packet);

    if (dll_generic_packet[WDC_DLL_HEADER_IDX] & bmWDC_DLL_HEADER_DIRN ==
        bmWDC_DLL_HEADER_DIRN_B2C)
    {
      //
      // Base to Companion.
      //
    }
    else
    {
      //
      // Companion to Base.
      //
    }
#endif
  }
}

/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

