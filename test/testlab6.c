#include <unity.h>
#include "unity_config.h"
#include <stdio.h>
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#pragma once

#define DELAY 500;

SemaphoreHandle_t semaphore;

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

void thread1(void *args){
    while(1){
        printf("Thread1 running");
        vTaskDelay(500);
    }
}

void thread2(void *args){
    while(1){
        printf("Thread2 running");
        xSemaphoreTake(semaphore, portMAX_DELAY);
        printf("Thread2 running");
        vTaskDelay(50000);
        printf("Thread2 running");

        
        
    }
}

void superVisor(void *args){
    while(1){
        printf("Supervisor initialized\n");

        TaskHandle_t t1;
        TaskHandle_t t2;
        
        semaphore = xSemaphoreCreateBinary();
        
        //lower priorty
        xTaskCreate(thread1, "thread 1",
                    configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &t1);
        
        xTaskCreate(thread2, "thread2",
                    configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, &t2);
        
        vTaskStartScheduler();
       
        vSemaphoreDelete(semaphore);
    }
    
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
                configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+10, &main_handle);
    vTaskStartScheduler();

    
    sleep_ms(5000);
    return UNITY_END();
}
