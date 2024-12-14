#include <pico/sem.h>
#include <pico/time.h>
#include <unity.h>
#include "FreeRTOSConfig_examples_common.h"
#include "portmacro.h"
#include "projdefs.h"
#include "unity_config.h"
#include "unity_internals.h"
#include <stdio.h>
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#pragma once
//#define configUSE_IDLE_HOOK 1

#define DELAY 500;
//for semaphore
static SemaphoreHandle_t semaphore;
static SemaphoreHandle_t mutex;
static TaskHandle_t main_handle; // this is the main handle
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
        vTaskDelay(10);
        vTaskDelete(NULL);
}

void mid_t(void *args){
    while(1){
        printf("Mid_t chicken\n");
        //if (xSemaphoreTake(semaphore,(TickType_t)10) == pdTRUE){
        xSemaphoreTake(semaphore, portMAX_DELAY);
        printf("Thread2 running\n");
        vTaskDelay(10);
        //}
        //else{
            printf("monkey magic\n");
            //}
        xSemaphoreGive(semaphore);
    }
        vTaskDelete(NULL);
}

void min_t(void *args){
        printf("Thread 3 low prior running\n");
        vTaskDelay(10);
        vTaskDelete(NULL);
}


void superVisor(void *args){
    //while(1){
     semaphore = xSemaphoreCreateBinary();
    UNITY_BEGIN();
    printf("Supervisor initialized\n");
    UNITY_END();
    vSemaphoreDelete(semaphore);
    vTaskDelete(NULL);
}

int main (void)
{
    printf("Start tests\n");

    stdio_init_all();


    TaskHandle_t main_handle;

    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    //this is where  tests occu
    //xTaskCreate(mid_t, "t2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2UL, &t2);
    xTaskCreate(superVisor, "superVisor",
                configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    xTaskCreate(max_t, "t1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+ 3UL, &t1);
    xTaskCreate(mid_t, "t2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2UL, &t2);
    xTaskCreate(min_t, "t3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t3);

    vTaskStartScheduler();
    //if things go wrong here something major has gone wrong

    sleep_ms(5000);
    return UNITY_END();
}
