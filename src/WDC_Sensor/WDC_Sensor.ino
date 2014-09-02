/**
  ******************************************************************************
  * @file    
  * @author  Alex Hsieh
  * @version V0.0.1
  * @date    01-Sep-2014
  * @brief   Arduino version of the Wearable Device Companion (WDC) for sensors.
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
#include "wdcuart_protocol.h"

/* Defines ------------------------------------------------------------------ */

/* Arduino Setup Function --------------------------------------------------- */
void setup()
{
  //
  // Initialize the WDC communication bus.
  //
  wdc_comm_init();
}

/* Arduino Main Loop -------------------------------------------------------- */
void loop()
{
  
}

/****************** (C) COPYRIGHT Illogical OR *****************END OF FILE****/

