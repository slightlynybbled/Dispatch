#include "dispatch.h"

/* device-specific header files */
#include "uart.h"
#include "config.h"

void initDispatch(void);

int main(void){
    /* initialize the communication channels */
    initDispatch();
    
    /* send a single dispatch */
    uint8_t data[] = {1, 2, 3, 4};
    DIS_publish("test:4,u8", data);
    
    /* forever loop */
    while(1){
        /* the dispatches must be periodically monitored in 
         * order to properly handle the subscriptions */
        DIS_process();
    }
    
    return 0;
}

void initDispatch(void){
    /* link dispatch to the UART channels */
    DIS_assignChannelInit(&UART_init);
    DIS_assignChannelReadable(&UART_readable);
    DIS_assignChannelWriteable(&UART_writeable);
    DIS_assignChannelRead(&UART_read);
    DIS_assignChannelWrite(&UART_write);
    
    DIS_init();
}
