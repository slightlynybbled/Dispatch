#include "dispatch.h"

/* device-specific header files */
#include "uart.h"
#include "config.h"

void initDispatch(void);
void mySubscriberFunction(void);

int main(void){
    /* initialize the communication channels */
    initDispatch();
    
    /* subscribe to the topic 'foo' */
    DIS_subscribe("foo", &mySubscriberFunction);
    
    /* send a single dispatch consisting of 4 data points */
    uint8_t data[] = {1, 2, 3, 4};
    DIS_publish("bar:4,u8", data);
    
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
    UART_init();
    
    DIS_assignChannelReadable(&UART_readable);
    DIS_assignChannelWriteable(&UART_writeable);
    DIS_assignChannelRead(&UART_read);
    DIS_assignChannelWrite(&UART_write);
    
    DIS_init();
}

void mySubscriberFunction(void){
    
}
