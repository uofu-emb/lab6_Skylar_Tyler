#include <pico/time.h>
#include <unity.h>
#include "FreeRTOSConfig_examples_common.h"
#include "portmacro.h"
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

static SemaphoreHandle_t semaphore;
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
    while(1){
        //xSemaphoreTake(semaphore, portMAX_DELAY);
        printf("Thread1 running\n");
        //xSemaphoreGive(semaphore);
        vTaskDelay(100);
        ///xSemaphoreGive(semaphore);
    }
}

void mid_t(void *args){
    while(1){
        printf("Thread2 running\n");
        //xSemaphoreTake(semaphore, portMAX_DELAY);
        printf("Thread2 running");
        vTaskDelay(10);
    }
}
void min_t(void *args){
    while(1){
        printf("Thread 3 low prior running\n");
        vTaskDelay(10);
    }
}
void vApplciationIdleHook(void){
    printf("MONKEY MAGIC?\n");
}

void superVisor(void *args){
    //semaphore = xSemaphoreCreateBinary();
        //vTaskResume(main_handle);
        e:
            UNITY_BEGIN();
            int i = 0;
            bool k = 1;
            while(k){
            printf("Supervisor initialized\n");
            i++;
            if(i== 5){
            k = 0;
            }
            }
            printf("this code is where things will break");
            UNITY_END();
            //xTaskCreate(TaskFunction_t pxTaskCode, const char *const pcName, const uint32_t uxStackDepth, void *const pvParameters, UBaseType_t uxPriority, TaskHandle_t *const pxCreatedTask)
            //return;
            sleep_ms(1000);
            vTaskDelay(1000);

        goto e;
        //vTaskSuspend(main_handle);
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
    xTaskCreate(superVisor, "superVisor",
                configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
    xTaskCreate(max_t, "t1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t1);
    xTaskCreate(mid_t, "t2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2UL, &t2);
    xTaskCreate(min_t, "t1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3UL, &t3);

    vTaskStartScheduler();

    xTaskCreate(max_t, "mask task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &main_handle);
    xTaskCreate(max_t, "t1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t1);
    vTaskStartScheduler();

    sleep_ms(5000);
    return UNITY_END();
}
