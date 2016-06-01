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

/**********************************************/
/* Use these functions to test the subscriber */
uint8_t subscriberCount = 0;
void subscriber0(void){
    subscriberCount++;
}

uint8_t u8arr[3] = {0};
uint16_t u16arr[3] = {0};
uint32_t u32arr[3] = {0};
void subscriber1(void){
    DIS_getElements(0, u8arr);
    DIS_getElements(1, u16arr);
    DIS_getElements(2, u32arr);
}

int8_t s8arr[3] = {0};
int16_t s16arr[3] = {0};
int32_t s32arr[3] = {0};
void subscriber2(void){
    DIS_getElements(0, s8arr);
    DIS_getElements(1, s16arr);
    DIS_getElements(2, s32arr);
}

/**********************************************/
/* tests below this line */

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
                            126, 22,
                            END_OF_FRAME
                        };

    DIS_publish("foo", "bar");
    
    uint16_t i;
    for(i = 0; i < 15; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_publish_string_using_using_DIS_publish_str(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            1, 3, 0, 1, 
                            'b','a','r',
                            126, 22,
                            END_OF_FRAME
                        };

    DIS_publish_str("foo", "bar");
    
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
                            82, 46,
                            END_OF_FRAME
                        };

    uint8_t data[1] = {10};
    DIS_publish("foo,u8", data);
    
    uint16_t i;
    for(i = 0; i < 13; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_publish_1_u8_using_DIS_publish_u8(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            1, 1, 0, 2, 
                            10,
                            82, 46,
                            END_OF_FRAME
                        };

    uint8_t data[1] = {10};
    DIS_publish_u8("foo", data);
    
    uint16_t i;
    for(i = 0; i < 13; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_publish_3_u8_using_DIS_publish_u8(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            1, 3, 0, 2, 
                            10, 20, 30,
                            134, 36,
                            END_OF_FRAME
                        };

    uint8_t data[3] = {10, 20, 30};
    DIS_publish_u8("foo:3", data);
    
    uint16_t i;
    for(i = 0; i < 15; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_publish_3_s8_using_DIS_publish_s8(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            1, 3, 0, 3, 
                            246, 246 ^ 0x20, 236, 226,
                            15, 96,
                            END_OF_FRAME
                        };

    int8_t data[3] = {-10, -20, -30};
    DIS_publish_s8("foo:3", data);
    
    uint16_t i;
    for(i = 0; i < 16; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_publish_1_u8u8_using_DIS_publish_2u8(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            2, 1, 0, 34, 
                            10,
                            20,
                            135, 250,
                            END_OF_FRAME
                        };

    uint8_t data0[1] = {10};
    uint8_t data1[1] = {20};
    DIS_publish_2u8("foo", data0, data1);
    
    uint16_t i;
    for(i = 0; i < 13; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_publish_3_s8s8_using_DIS_publish_2s8(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            2, 3, 0, 51, 
                            246, 246 ^ 0x20, 236, 226,
                            216, 206, 196,
                            170, 207,
                            END_OF_FRAME
                        };

    int8_t data0[3] = {-10, -20, -30};
    int8_t data1[3] = {-40, -50, -60};
    DIS_publish_2s8("foo:3", data0, data1);
    
    uint16_t i;
    for(i = 0; i < 19; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_publish_3_u16_using_DIS_publish_u16(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            1, 3, 0, 4, 
                            10, 0, 20, 0, 30, 0,
                            136, 116,
                            END_OF_FRAME
                        };

    uint16_t data[3] = {10, 20, 30};
    DIS_publish_u16("foo:3", data);
    
    uint16_t i;
    for(i = 0; i < 18; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_publish_3_s16_using_DIS_publish_s16(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            1, 3, 0, 5, 
                            246, 246 ^ 0x20, 255, 236, 255, 226, 255,
                            14, 226,
                            END_OF_FRAME
                        };

    int16_t data[3] = {-10, -20, -30};
    DIS_publish_s16("foo:3", data);
    
    uint16_t i;
    for(i = 0; i < 19; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_publish_2x3_u8u16(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            2, 3, 0, 0x42,  
                            10, 20, 30,
                            40, 0, 50, 0, 60, 0,
                            93, 5,
                            END_OF_FRAME
                        };

    uint8_t data0[] = {10, 20, 30};
    uint16_t data1[] = {40, 50, 60};
    
    DIS_publish("foo:3,u8,u16", data0, data1);
    
    uint16_t i;
    for(i = 0; i < 22; i++){
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
                            84, 186,
                            END_OF_FRAME
                        };

    uint8_t data0[] = {10, 20, 30};
    uint16_t data1[] = {40, 50, 60};
    uint32_t data2[] = {70, 80, 90};
    
    DIS_publish("foo:3,u8,u16,u32", data0, data1, data2);
    
    uint16_t i;
    for(i = 0; i < 34; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_publish_3x3_s8s16s32(void){
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            3, 3, 0, 0x53, 0x07, 
                            246, 246 ^ 0x20, 236, 226, // <= one of these happens to be an esc char
                            216, 255, 206, 255, 196, 255,
                            186, 255, 255, 255, 176, 255, 255, 255, 166, 255, 255, 255,
                            214, 236,           // <= remember that ESC, SOF, and EOF are done *after* the checksum is calculated
                            END_OF_FRAME
                        };

    int8_t data0[] = {-10, -20, -30};
    int16_t data1[] = {-40, -50, -60};
    int32_t data2[] = {-70, -80, -90};
    
    DIS_publish("foo:3,s8,s16,s32", data0, data1, data2);
    
    uint16_t i;
    for(i = 0; i < 35; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_subscribe_and_process(void){
    subscriberCount = 0;
    DIS_subscribe("foo", &subscriber0);  // subscribe to 'foo'
    
    /* ensure that subscriber is not 
        called through several calls to process */
    DIS_process();  
    DIS_process();  
    DIS_process();
    TEST_ASSERT_EQUAL_INT(0, subscriberCount);
    
    /* load the receiving function */
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            1, 1, 0, 2, 
                            10,
                            82, 46,
                            END_OF_FRAME
                        };
    int i;
    for(i = 0; i < 13; i++){
        readData[i] = dataTest[i];
    }
    readableIndex = 13;
    
    /* ensure that process is called many times, but 
        that the 'subscriber' is called one time */
    DIS_process();  
    DIS_process();  
    DIS_process();
    
    TEST_ASSERT_EQUAL_INT(1, subscriberCount);
}

void test_subscribe_unsigned(void){
    DIS_subscribe("foo", &subscriber1);  // subscribe to 'foo'
    
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            3, 3, 0, 0x42, 0x06, 
                            10, 20, 30,
                            40, 0, 50, 0, 60, 0,
                            70, 0, 0, 0, 80, 0, 0, 0, 90, 0, 0, 0,
                            84, 186,
                            END_OF_FRAME
                        };
    uint16_t i;
    for(i = 0; i < 34; i++){
        readData[i] = dataTest[i];
    }
    readableIndex = 34;
    
    DIS_process();  // should call the subscriber

    uint8_t data0[] = {10, 20, 30};
    uint16_t data1[] = {40, 50, 60};
    uint32_t data2[] = {70, 80, 90};
    
    for(i = 0; i < 3; i++){
        TEST_ASSERT_EQUAL_INT(data0[i], u8arr[i]);
        TEST_ASSERT_EQUAL_INT(data1[i], u16arr[i]);
        TEST_ASSERT_EQUAL_INT(data2[i], u32arr[i]);
    }
}

void test_subscribe_signed(void){
    DIS_subscribe("foo", &subscriber2);  // subscribe to 'foo'
    
    uint8_t dataTest[WRITE_DATA_LENGTH] = 
                        {   START_OF_FRAME,
                            'f', 'o', 'o', 0,
                            3, 3, 0, 0x53, 0x07, 
                            246, ESC ^ 0x20, 236, 226, // <= one of these happens to be an esc char
                            216, 255, 206, 255, 196, 255,
                            186, 255, 255, 255, 176, 255, 255, 255, 166, 255, 255, 255,
                            214, 236,
                            END_OF_FRAME
                        };
    uint16_t i;
    for(i = 0; i < 35; i++){
        readData[i] = dataTest[i];
    }
    readableIndex = 35;
    
    DIS_process();  // should call the subscriber

    int8_t data0[] = {-10, -20, -30};
    int16_t data1[] = {-40, -50, -60};
    int32_t data2[] = {-70, -80, -90};
    
    for(i = 0; i < 3; i++){
        TEST_ASSERT_EQUAL_INT(data0[i], s8arr[i]);
        TEST_ASSERT_EQUAL_INT(data1[i], s16arr[i]);
        TEST_ASSERT_EQUAL_INT(data2[i], s32arr[i]);
    }
}

