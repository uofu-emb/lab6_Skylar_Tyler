#include <pico/time.h>
#include <unity.h>
#include "FreeRTOSConfig_examples_common.h"
#include "portmacro.h"
#include "unity_config.h"
#include <stdio.h>
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#pragma once

#define DELAY 500;

static SemaphoreHandle_t semaphore;
static TaskHandle_t t1; // max prio.
static TaskHandle_t t2; // mid prio.
static TaskHandle_t t3; // min prio.

void setUp(void) {}

void tearDown(void) {}

/*
 Induce priority inversion.

1. create two preemptable threads (and a supervisor to manage them). check
2. create a semaphore shared between the two. Create it with xSemaphoreCreateBinary.
3. set one thread to higher priority. set it to delay start.
4. have the lower priority thread acquire the semphore first.
5. Predict the behavior of the system.
 */

void max_t(void *args){
        printf("Thread1 running\n");
        //xSemaphoreTake(semaphore, portMAX_DELAY);
        //xSemaphoreGive(semaphore);
        //vTaskDelay(10000);
        //xSemaphoreGive(semaphore);
}

void mid_t(void *args){
    while(1){
        printf("Thread2 running\n");
        xSemaphoreTake(semaphore, portMAX_DELAY);
        printf("Thread2 running");
        vTaskDelay(10);
    }
}
void low_t(void *args){
    while(1){
        printf("Thread 3 low prior running\n");
        vTaskDelay(10);
    }
}

void superVisor(void *args){
    //semaphore = xSemaphoreCreateBinary();
        printf("Supervisor initialized\n");
        //higher priorty
        xTaskCreate(max_t, "thread 1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &t1);
        //mid priority
        //xTaskCreate(mid_t, "thread2",
        //            configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, &t2);
        //low priority.
        //xTaskCreate(low_t, "thread 3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &t3);

        //vTaskStartScheduler();

        //vSemaphoreDelete(semaphore);
        vTaskDelay(100);
    //vSemaphoreDelete(semaphore);

}

int main (void)
{
    printf("Start tests\n");

    stdio_init_all();


    TaskHandle_t main_handle;
    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    //this is where  tests occu
    //vTaskStartScheduler();
    xTaskCreate(superVisor, "superVisor",
                configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+10, &main_handle);
    vTaskStartScheduler();
    printf("got out of the main loop");
    sleep_ms(5000);
    UNITY_END();
    return 0;
}
