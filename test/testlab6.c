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
        //if (xSemaphoreTake(semaphore, 100) == pdTRUE){
        xSemaphoreTake(mutex, 100);
        printf("Thread2 running\n");
        vTaskDelay(10);
        xSemaphoreGive(mutex);
        //}
        //else{
            //printf("dum dum give me gum gum\n");
        //}

        //}
        //else{
            //}
            vTaskDelete(NULL);
}

void min_t(void *args){
        printf("Thread 3 low prior running\n");
        vTaskDelay(10);
        vTaskDelete(NULL);
}

void busy_busy(void)
{
    for (int i = 0; ; i++);
}


void busy_yield(void)
{
    for (int i = 0; ; i++) {
        taskYIELD();
    }
}

void superVisor(void *args){
    //while(1){
    printf("Supervisor initialized\n");
    semaphore = xSemaphoreCreateBinary();
    mutex = xSemaphoreCreateMutex();
    //UNITY_BEGIN();
    //UNITY_END();
    vSemaphoreDelete(semaphore);
    vSemaphoreDelete(mutex);
    vTaskDelete(NULL);
}

int main (void)
{
    printf("Start tests\n");

    stdio_init_all();

    semaphore = xSemaphoreCreateBinary();
    mutex = xSemaphoreCreateMutex();
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





    //ACTIVITY 2 P1

    TickType_t start_ticks = xTaskGetTickCount();
    xTaskCreate(busy_busy, "t4", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t4);
    xTaskCreate(busy_busy, "t5", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t5);
    printf("timing code here")

    TickType_t end_ticks = xTaskGetTickCount();

    TickType_t elapsed_ticks = end_ticks - start_ticks;
    printf(elapsed_ticks);


    //P2
    xTaskCreate(busy_yield, "t6", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t6);
    xTaskCreate(busy_yield, "t7", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t7);

    //P3
    xTaskCreate(busy_yield, "t8", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t8);
    xTaskCreate(busy_busy, "t9", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t9);



    //Same thing but different priorities.

    xTaskCreate(busy_busy, "t10", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2UL, &t10);
    xTaskCreate(busy_busy, "t11", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t11);
    printf("timing code here")

    //P2
    xTaskCreate(busy_yield, "t12", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2UL, &t12);
    xTaskCreate(busy_yield, "t13", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t13);


    vTaskStartScheduler();
    //if things go wrong here something major has gone wrong

    sleep_ms(5000);
    return UNITY_END();
}
