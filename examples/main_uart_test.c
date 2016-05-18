/*
 * File:   main_uart_test.c
 * Author: Jason
 *
 * Created on May 18, 2016, 10:05 AM
 */
#define FCY 12000000UL

#include "xc.h"
#include "uart.h"
#include "config.h"
#include <libpic30.h>

void myProcess(void);

int main(void) {
    UART_init();
    
    while(1){
        __delay_ms(500);
        myProcess();
    }
}

void myProcess(void){
    uint8_t i;
    uint8_t iArr[64];
    for(i=0; i < 64; i++){
        iArr[i] = i;
    }
    
    UART_write(iArr, 64);
}
