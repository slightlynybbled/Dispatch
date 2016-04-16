#include "unity.h"
#include "frame.c"
#include "mock_channel.c"

#define BUFFER_ARRAY_LENGTH 8

void setUp(void)
{
    FRM_assignChannelReadable(&readable);
    FRM_assignChannelWriteable(&writeable);
    FRM_assignChannelRead(&read8);
    FRM_assignChannelWrite(&write8);
    
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

void test_mock_readable(void)
{
    channel_reset();
    TEST_ASSERT_EQUAL_INT(0, readable());
}

void test_mock_writeable(void)
{
    channel_reset();
    TEST_ASSERT_EQUAL_INT(WRITE_DATA_LENGTH, writeable());
}

void test_mock_write(void){
    uint8_t dataIn[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    write8(dataIn, 10);
    
    int i;
    for(i = 0; i < 10; i++){
        TEST_ASSERT_EQUAL_INT(dataIn[i], writeData[i]);
    }
}

void test_mock_read(void){
    uint8_t dataIn[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint8_t dataOut[READ_DATA_LENGTH] = {0};
    
    int i;
    for(i = 0; i < 10; i++){
        readData[i] = dataIn[i];
    }
    
    read8(dataOut, 10);

    for(i = 0; i < 10; i++){
        TEST_ASSERT_EQUAL_INT(dataIn[i], dataOut[i]);
    }
}

void test_send_10(void)
{
    uint8_t dataIn[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint8_t dataTest[WRITE_DATA_LENGTH] = { START_OF_FRAME, 
                                            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
                                            END_OF_FRAME};
    
    FRM_push(dataIn, 10);
    
    TEST_ASSERT_EQUAL_INT(dataTest[0], writeData[0]);
}
