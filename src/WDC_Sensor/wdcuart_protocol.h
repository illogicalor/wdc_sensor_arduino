/**
  ******************************************************************************
  * @file    wdcuart_protocol.h
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

#ifndef __WDCUART_PROTOCOL_H__
#define __WDCUART_PROTOCOL_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include <stdint.h>

/* Defines ------------------------------------------------------------------ */
// WDC_EN Pin 
#define WDC_EN_PIN          2

// UART Baud Rate Settings
// Note: The max baud depends on the WDC processor.
#define DEFAULT_BAUD_RATE   9600
#define MAX_BAUD_RATE       115200

/* Function Prototypes  ----------------------------------------------------- */
void wdc_comm_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __WDCUART_PROTOCOL_H__ */
/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

