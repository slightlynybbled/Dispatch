#include "unity.h"
#include "dispatch.c"
#include "frame.c"
#include "mock_uart_channel.c"
#include <stdio.h>

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

void test_publish_1_u8(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            1, 1, 0, 2, 
                            10,
                            83, 56,
                            END_OF_FRAME
                        };

    uint8_t data[1] = {10};
    DIS_publish("foo,u8", data);
    
    uint16_t i;
    for(i = 0; i < 13; i++){
        printf("%d ", i);
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_publish_3x3_u8u16u32(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            3, 3, 0, 0x42, 0x06, 
                            10, 20, 30,
                            40, 0, 50, 0, 60, 0,
                            70, 0, 0, 0, 80, 0, 0, 0, 90, 0, 0, 0,
                            87, 250,
                            END_OF_FRAME
                        };

    uint8_t data0[] = {10, 20, 30};
    uint16_t data1[] = {40, 50, 60};
    uint32_t data2[] = {70, 80, 90};
    
    DIS_publish("foo:3,u8,u16,u32", data0, data1, data2);
    
    uint16_t i;
    for(i = 0; i < 34; i++){
        printf("%d ", i);
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_publish_3x3_s8s16s32(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            3, 3, 0, 0x53, 0x07, 
                            246, ESC ^ 0x20, 236, 226, // <= one of these happens to be an esc char
                            216, 255, 206, 255, 196, 255,
                            186, 255, 255, 255, 176, 255, 255, 255, 166, 255, 255, 255,
                            234, 234,
                            END_OF_FRAME
                        };

    int8_t data0[] = {-10, -20, -30};
    int16_t data1[] = {-40, -50, -60};
    int32_t data2[] = {-70, -80, -90};
    
    DIS_publish("foo:3,s8,s16,s32", data0, data1, data2);
    
    uint16_t i;
    for(i = 0; i < 35; i++){
        printf("%d ", i);
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}
