/*
 * File:   main_uart_test.c
 * Author: Jason
 *
 * Created on May 18, 2016, 10:05 AM
 */
#define FCY 12000000UL

#include "xc.h"
#include "frame.h"
#include "uart.h"
#include "config.h"
#include <libpic30.h>

void myProcess(void);

int main(void) {
    UART_init();
    
    FRM_assignChannelReadable(&UART_readable);
    FRM_assignChannelWriteable(&UART_writeable);
    FRM_assignChannelRead(&UART_read);
    FRM_assignChannelWrite(&UART_write);
    
    while(1){
        __delay_ms(500);
        myProcess();
    }
}

void myProcess(void){
    uint8_t i;
    
    FRM_init();
    for(i=0; i < 64; i++){
        FRM_data(i);
    }
    FRM_finish();
    
}
