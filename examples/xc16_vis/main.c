#include "dispatch.h"

/* device-specific header files */
#include "uart.h"
#include "config.h"

void initDispatch(void);

int main(void){
    uint32_t i = 0;
    /* initialize the communication channels */
    initDispatch();
    
    /* forever loop */
    while(1){
        if(i++ > 600){
            uint8_t arrayToPlot[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
            
            /* publish to a plot */
            DIS_publish("plot:10,u8", arrayToPlot);
            
            /* publish to a log */
            DIS_publish("log:10,u8", arrayToPlot);
            
            /* publish to a csv file using the lettered column headers */
            DIS_publish("csv", "a, b, c, d,e,f,g,h,i,j");
            DIS_publish("csv:10,u8", arrayToPlot);
            i = 0;
        }
        
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
