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
    static uint16_t i = 0;
    
    i++;
    
    uint16_t j;
    uint16_t jArr[64] = {0};
    for(j = 0; j < 64; j++){
        jArr[j] = j;
    }
    
    /* publish i back to the sender to 'close the loop' */
    DIS_publish("i:64,u16", jArr);
}
