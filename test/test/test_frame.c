#include "unity.h"
#include "frame.c"
#include "uart_channel.c"

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
    TEST_ASSERT_EQUAL_INT(0, readable());
}

void test_mock_writeable(void)
{
    TEST_ASSERT_EQUAL_INT(WRITE_DATA_LENGTH, writeable());
}

void test_push_byte_normal(void)
{
    uint8_t data = 10;
    FRM_pushByte(data);
    
    TEST_ASSERT_EQUAL_INT(data, writeData[0]);
}

void test_push_byte_SOF(void)
{
    uint8_t data = START_OF_FRAME;
    FRM_pushByte(data);
    
    TEST_ASSERT_EQUAL_INT(ESC, writeData[0]);
    TEST_ASSERT_EQUAL_INT(START_OF_FRAME ^ ESC_XOR, writeData[1]);
}

void test_push_byte_EOF(void)
{
    uint8_t data = END_OF_FRAME;
    FRM_pushByte(data);
    
    TEST_ASSERT_EQUAL_INT(ESC, writeData[0]);
    TEST_ASSERT_EQUAL_INT(END_OF_FRAME ^ ESC_XOR, writeData[1]);
}

void test_push_byte_ESC(void)
{
    uint8_t data = ESC;
    FRM_pushByte(data);
    
    TEST_ASSERT_EQUAL_INT(ESC, writeData[0]);
    TEST_ASSERT_EQUAL_INT(ESC ^ ESC_XOR, writeData[1]);
}

void test_mock_frame_write(void){
    uint8_t dataIn[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint8_t dataTest[] = {  START_OF_FRAME, 
                            0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                            45, 165,
                            END_OF_FRAME};
    
    FRM_push(dataIn, 10);
    
    int i;
    for(i = 0; i < 14; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

void test_mock_write_esc(void){
    uint8_t dataIn[] = {0, START_OF_FRAME, 2, END_OF_FRAME, 4, ESC, 6, 7, 8, 9};
    uint8_t dataTest[] = {  START_OF_FRAME,
                            0, ESC, START_OF_FRAME ^ ESC_XOR,
                            2, ESC, END_OF_FRAME ^ ESC_XOR,
                            4, ESC, ESC ^ ESC_XOR,
                            6, 7, 8, 9,
                            146, 117, 
                            END_OF_FRAME};
    
    FRM_push(dataIn, 10);
    
    int i;
    for(i = 0; i < 17; i++){
        TEST_ASSERT_EQUAL_INT(dataTest[i], writeData[i]);
    }
}

/*void test_mock_read(void){
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
}*/