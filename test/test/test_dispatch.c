#include "unity.h"
#include "dispatch.c"
#include "frame.c"
#include "mock_uart_channel.c"

void setUp(void)
{
    DIS_init();
    
    DIS_assignChannelReadable(&readable);
    DIS_assignChannelWriteable(&writeable);
    DIS_assignChannelRead(&read8);
    DIS_assignChannelWrite(&write8);
    
    channel_reset();
}

void tearDown(void)
{
    
}

void test_init_readable(void)
{
    TEST_ASSERT_NOT_NULL(channelReadableFunctPtr);
    TEST_ASSERT_EQUAL_INT(channelReadableFunctPtr,readable);
}

void test_init_writeable(void)
{
    TEST_ASSERT_NOT_NULL(channelWriteableFunctPtr);
    TEST_ASSERT_EQUAL_INT(channelWriteableFunctPtr,writeable);
}

void test_init_read(void)
{
    TEST_ASSERT_NOT_NULL(channelReadFunctPtr);
    TEST_ASSERT_EQUAL_INT(channelReadFunctPtr,read8);
}

void test_init_write(void)
{
    TEST_ASSERT_NOT_NULL(channelWriteFunctPtr);
    TEST_ASSERT_EQUAL_INT(channelWriteFunctPtr,write8);
}

void test_publish_string(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            1, 3, 0, 1, 
                            'b','a','r',
                            128, 37,
                            END_OF_FRAME
                        };

    DIS_publish("foo", "bar");
    
    uint16_t i;
    for(i = 0; i < 15; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}
