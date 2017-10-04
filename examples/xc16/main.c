#include "dispatch.h"

/* device-specific header files */
#include "uart.h"
#include "config.h"

void initDispatch(void);

void messagesReceivedSubscriber(void);
void stringSubscriber(void);
void iSubscriber(void);

static uint32_t messagesReceived = 0;

int main(void){
    /* initialize the communication channels */
    initDispatch();
    
    /* subscribe to the topic 'foo' */
    DIS_subscribe("received", &messagesReceivedSubscriber);
    DIS_subscribe("string", &stringSubscriber);
    DIS_subscribe("i", &iSubscriber);
    
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

void messagesReceivedSubscriber(void){
    DIS_publish("received,u32", &messagesReceived);
}

void stringSubscriber(void){
    messagesReceived++; // increment messages received
    
    /* this subscriber is expecting a string input, so here is an example
     * of retrieving that string (even though it won't be utilized in this
     * function) */
    char strReceived[64] = {};
    DIS_getElements(0, strReceived);
    
    /* publish i back to the sender to 'close the loop' */
    DIS_publish("string", "message from the micro!");
}

void iSubscriber(void){
    messagesReceived++; // increment messages received
    
    /* this subscriber is expecting a single 16-bit element, so get the 0th
     * element and provide a location in which to place that element (in this
     * case, that location is the address of i) */
    uint16_t i;
    DIS_getElements(0, &i);
    
    /* increment i just to ensure that we have done some operation on it */
    i++;
    
    /* publish i back to the sender to 'close the loop' */
    DIS_publish("i,u16", &i);
}
