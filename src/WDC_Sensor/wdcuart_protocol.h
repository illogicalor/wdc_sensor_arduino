/**
  ******************************************************************************
  * @file    
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

/* Defines ------------------------------------------------------------------ */
#define WDC_CS_PIN    2

/* Function Prototypes  ----------------------------------------------------- */
void wdcuart_init(void);

/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

