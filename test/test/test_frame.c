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


