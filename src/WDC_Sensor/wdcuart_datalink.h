/**
  ******************************************************************************
  * @file    wdcuart_datalink.h
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

#ifndef __WDCUART_DATALINK_H__
#define __WDCUART_DATALINK_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include <stdint.h>
#include <stdbool.h>
#include "wdcuart_physical.h"

/* Defines ------------------------------------------------------------------ */
// WDC Data-Link Header Definitions
#define WDC_DLL_HEADER_IDX                        0
#define bmWDC_DLL_HEADER_ENDPOINT                 (3 << 0)
#define bmWDC_DLL_HEADER_PACKET_TYPE              (3 << 2)
#define bmWDC_DLL_HEADER_PACKET_TYPE_ENUMERATION  (0 << 2)
#define bmWDC_DLL_HEADER_PACKET_TYPE_REQUEST      (1 << 2)
#define bmWDC_DLL_HEADER_PACKET_TYPE_DATA         (2 << 2)
#define bmWDC_DLL_HEADER_PACKET_TYPE_EVENT        (3 << 2)
#define bmWDC_DLL_HEADER_DIRN                     (1 << 7)
#define bmWDC_DLL_HEADER_DIRN_B2C                 (1 << 7)
#define bmWDC_DLL_HEADER_DIRN_C2B                 (0 << 7)

// 
#define WDC_DLL_ENUMERATION_PACKET_LEN            4
#define WDC_DLL_REQUEST_PACKET_LEN                4
#define WDC_DLL_DATA_PACKET_LEN                   (WDC_PLL_MAX_FRAME_SIZE)
#define WDC_DLL_EVENT_PACKET_LEN                  (WDC_PLL_MAX_FRAME_SIZE)

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

/* Function Prototypes ------------------------------------------------------ */
void WDC_DLLInit(void);
void WDC_DLLDeinit(void);

#ifdef __cplusplus
}
#endif

#endif /* __WDCUART_DATALINK_H__ */
/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

