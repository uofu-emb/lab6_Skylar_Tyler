#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

// This example uses a common include to avoid repetition
#include "FreeRTOSConfig_examples_common.h"
configGENERATE_RUN_TIME_STATS = 1;
configUSE_STATS_FORMATTING_FUNCTIONS = 1;
configSUPPORT_DYNAMIC_ALLOCATION =1;


extern void timerSetup(void);
extern uint32_t getTimerValue(void);

#define portGET_RUN_TIME_COUNTER_VALUE() getTimerValue()
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() timerSetup()

#endif
