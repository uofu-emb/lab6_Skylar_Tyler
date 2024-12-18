#include <pico/sem.h>
#include <pico/time.h>
#include <stdint.h>
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
#define configGENERATE_RUN_TIME_STATS 1

#define DELAY 500;
//use var for timing
static uint32_t time1 = 0;
static uint32_t time2 = 0;
static uint32_t time3 = 0;
static uint32_t time4 = 0;
//THIS IS THE VAR. TO TELL WHICH TEST IS GOING TO BE COMPLETED
const int TESTNUMB = 3;

//for semaphore
static SemaphoreHandle_t semaphore;
static SemaphoreHandle_t mutex;
static TaskHandle_t main_handle; // this is the main handle
static TaskHandle_t t1; // max prio.
static TaskHandle_t t2; // mid prio.
static TaskHandle_t t3; // min prio.
static TaskHandle_t t4;
static TaskHandle_t t5;
static TaskHandle_t t6;
static TaskHandle_t t7;
static TaskHandle_t t8;
static TaskHandle_t t9;
static TaskHandle_t t10;
static TaskHandle_t t11;
static TaskHandle_t t12;
static TaskHandle_t t13;

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
 void test1(void){

     printf("the time1:%i the time2:%i \n", time1, time2);
     TEST_ASSERT_GREATER_OR_EQUAL(time1,time2);
     time1 = 0;
     time2 = 0;
 }

 void test2(void){
     //since this is busy_yeild it would be best to use time 3 and
     //time for to keep the tests isoloated.
     printf("the time3:%i the time4:%i \n", time3, time4);
     TEST_ASSERT_GREATER_OR_EQUAL(time3,time4);
     time3 = 0;
     time4 = 0;
 }
 void test3(void){
     //testing busy_yeild and busy_busy
     printf("the time3:%i the time2:%i \n", time3, time1);
     TEST_ASSERT_GREATER_OR_EQUAL(time1,time3);
     time3 = 0;
     time1 = 0;
 }

void max_t(void *args){
        printf("Thread1 running\n");
        vTaskDelay(10);
        vTaskDelete(NULL);
}

void mid_t(void *args){
        xSemaphoreTake(mutex, 100);
        printf("Thread2 running\n");
        vTaskDelay(10);
        xSemaphoreGive(mutex);
            vTaskDelete(NULL);
}

void min_t(void *args){
        printf("Thread 3 low prior running\n");
        vTaskDelay(10);
        vTaskDelete(NULL);
}

void busy_busy(void *args)
{
    uint32_t start = xTaskGetTickCount();
    //printf("HERE IS THE TIME: time1 %i", start);

    printf("busy busy 1 is running\n");
    for (int i = 0; ; i++){
        //printf("for loop running\n");
        int32_t stop = xTaskGetTickCount();
        time1 = start - stop;
        //printf("HERE IS THE TIME: time1 %i", time1);
        sleep_ms(1000);
        vTaskDelay(10);
    }


}
void busy_busy_tim2(void *args)
{
    uint32_t start = xTaskGetTickCount();
    //printf("HERE IS THE TIME: time2 %i", start);

    printf("busy busy 2 is running\n");
    for (int i = 0; ; i++){
        //printf("for loop running\n");
        int32_t stop = xTaskGetTickCount();
        time2 = start - stop;
        //printf("HERE IS THE TIME: time2 %i", time2);
        sleep_ms(1000);
        vTaskDelay(10);

    }

    vTaskDelete(NULL);

}


void busy_yield(void *args)
{
    printf("busy yeild is running\n");
    uint32_t start = xTaskGetTickCount();
    for (int i = 0; ; i++) {
        taskYIELD();
        int32_t stop = xTaskGetTickCount();
        time3 = start - stop;
        sleep_ms(1000);
        vTaskDelay(10);
    }
    vTaskDelete(NULL);
}
void busy_yield_2(void *args)
{
    printf("busy yeild is running\n");
    uint32_t start = xTaskGetTickCount();
    for (int i = 0; ; i++) {
        taskYIELD();
        int32_t stop = xTaskGetTickCount();
        time4 = start - stop;
        sleep_ms(1000);
        vTaskDelay(10);
    }
    vTaskDelete(NULL);
}

void superVisor(void *args){
    printf("Supervisor initialized\n");
    semaphore = xSemaphoreCreateBinary();
    mutex = xSemaphoreCreateMutex();
    vSemaphoreDelete(semaphore);
    vSemaphoreDelete(mutex);
    vTaskDelete(NULL);
}
void testSuperVisor1i(void *args){
    while(1){
    sleep_ms(2000);
    UNITY_BEGIN();
    vTaskDelay(1000);
    if(TESTNUMB == 1){
        RUN_TEST(test1);
    }
    if(TESTNUMB == 2){
        RUN_TEST(test2);
    }
    if(TESTNUMB == 3){
        RUN_TEST(test3);
    }
    UNITY_END();
    sleep_ms(3000);
    }
    vTaskDelete(NULL);
}




int main (void)
{
    printf("Start tests\n");

    stdio_init_all();
    UNITY_BEGIN();

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

    //TickType_t start_ticks = xTaskGetTickCount();
    if(TESTNUMB == 1){
        xTaskCreate(busy_busy, "t4", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t4);
        xTaskCreate(busy_busy_tim2, "t5", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t5);
        //printf("timing code here\n");
    }


    //prediction  they will share an equal amount of time waiting around.
    xTaskCreate(testSuperVisor1i, "testVisor",
                configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 5UL, NULL);

    // //P2
    if(TESTNUMB == 2){
     xTaskCreate(busy_yield, "t6", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t6);
     xTaskCreate(busy_yield_2, "t7", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t7);
    }
    // //P3
     if(TESTNUMB == 3){
     xTaskCreate(busy_yield, "t8", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t8);
     xTaskCreate(busy_busy, "t9", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t9);
     }


    // //Same thing but different priorities.

    // xTaskCreate(busy_busy, "t10", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2UL, &t10);
    // xTaskCreate(busy_busy, "t11", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t11);
    // printf("timing code here\n");

    // //P2
    // xTaskCreate(busy_yield, "t12", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2UL, &t12);
    // xTaskCreate(busy_yield, "t13", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &t13);


    vTaskStartScheduler();
    //something is going wrong if code is executed here.
    //

    sleep_ms(5000);
    return UNITY_END();
}
