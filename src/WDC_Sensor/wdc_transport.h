/**
  ******************************************************************************
  * @file    wdc_transport.h
  * @author  Alex Hsieh
  * @version V0.0.1
  * @date    03-Sep-2014
  * @brief   Wearable Device Companion (WDC) transport-link layer for the WDC
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

/* Defines ------------------------------------------------------------------ */

/* Function Prototypes ------------------------------------------------------ */
void WDC_TLLInit(void);
void WDC_TLLDeinit(void);

#ifdef __cplusplus
}
#endif

#endif /* __WDCUART_DATALINK_H__ */
/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

