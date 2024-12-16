#include "FreeRTOSConfig_examples_common.h"
#include <pico/sem.h>
#include <pico/time.h>
#include <unity.h>
#include <stdio.h>
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>


TaskHandle_t Oversee;
//this is the sema
TaskHandle_t t1;
TaskHandle_t t2;
TaskHandle_t t3;

SemaphoreHandle_t sem;

void set_up(){
    sem = xSemaphoreCreateBinary();
    if(sem == NULL){
        printf("fail to init bin sem\n");
    }
    else{
        printf("init sem!\n ");
    }
}

//this takes the sema.
void task1(void *args){

}
//this gives the sema.
void task2(void *args){

}

void task3(void *args){

}

void main_task(void *args){
    printf("in main task\n");
    vTaskDelete(NULL);
}

int main(void *args){
    sleep_ms(5000);
    printf("Start of program\n");
    stdio_init_all();
    set_up();
    xTaskCreate(main_task, "main task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY , &Oversee);
    vTaskStartScheduler();
    return 0;
}
