#include "dispatch.h"

/* device-specific header files */
#include "uart.h"
#include "config.h"

static uint32_t messagesReceived = 0;

void initDispatch(void);

void messagesReceivedSubscriber(void);
void stringSubscriber(void);
void iSubscriber(void);
void arraySubscriber(void);
void arrays8Subscriber(void);
void arrays16Subscriber(void);
void arrays32Subscriber(void);

int main(void){
    /* initialize the communication channels */
    initDispatch();
    
    /* subscribe to the topic 'foo' */
    DIS_subscribe("received", &messagesReceivedSubscriber);
    DIS_subscribe("string", &stringSubscriber);
    DIS_subscribe("i", &iSubscriber);
    DIS_subscribe("array", &arraySubscriber);
    DIS_subscribe("arrays8", &arrays8Subscriber);
    DIS_subscribe("arrays16", &arrays16Subscriber);
    DIS_subscribe("arrays32", &arrays32Subscriber);
    
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
    DIS_publish("string", "uC msg");
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

void arraySubscriber(void){
    messagesReceived++; // increment messages received
    
    int16_t arr[4];             // <--- note that the type here must match the transmitted type!
    DIS_getElements(0, arr);
    
    uint16_t i;
    for(i=0; i<4; i++){
        arr[i] += 1;    // modify each element of the array in preparation to return it
    }
    
    DIS_publish("array:4,s16", arr);    // publish 4 elements of the array
}

void arrays8Subscriber(void){
    messagesReceived++; // increment messages received
    
    int8_t arr0[4];    // <--- note that the type here must match the transmitted type!
    DIS_getElements(0, arr0);
    
    uint8_t arr1[4];   // <--- note that the type here must match the transmitted type!
    DIS_getElements(1, arr1);
    
    uint16_t i;
    for(i=0; i<4; i++){
        arr0[i] += 1;   // modify each element of the array in preparation to return it
        arr1[i] += 1;
    }
    
    DIS_publish("arrays8:4,s8,u8", arr0, arr1);    // publish 4 elements of two arrays
}

void arrays16Subscriber(void){
    messagesReceived++; // increment messages received
    
    int16_t arr0[4];    // <--- note that the type here must match the transmitted type!
    DIS_getElements(0, arr0);
    
    uint16_t arr1[4];   // <--- note that the type here must match the transmitted type!
    DIS_getElements(1, arr1);
    
    uint16_t i;
    for(i=0; i<4; i++){
        arr0[i] += 1;   // modify each element of the array in preparation to return it
        arr1[i] += 1;
    }
    
    DIS_publish("arrays16:4,s16,u16", arr0, arr1);    // publish 4 elements of two arrays
}

void arrays32Subscriber(void){
    messagesReceived++; // increment messages received
    
    int32_t arr0[4];    // <--- note that the type here must match the transmitted type!
    DIS_getElements(0, arr0);
    
    uint32_t arr1[4];   // <--- note that the type here must match the transmitted type!
    DIS_getElements(1, arr1);
    
    uint16_t i;
    for(i=0; i<4; i++){
        arr0[i] += 1;   // modify each element of the array in preparation to return it
        arr1[i] += 1;
    }
    
    DIS_publish("arrays32:4,s32,u32", arr0, arr1);    // publish 4 elements of two arrays
}
