#include "unity.h"
#include "frame.c"
#include "mock_channel.c"

#define BUFFER_ARRAY_LENGTH 8

void setUp(void)
{
    
}

void tearDown(void)
{
    
}

void test_init_readable(void)
{
    FRM_assignChannelReadable(&readable);
    
    TEST_ASSERT_EQUAL_INT(channelReadableFunctPtr,readable);
}

void test_init_writeable(void)
{
    FRM_assignChannelWriteable(&writeable);
    
    TEST_ASSERT_EQUAL_INT(channelWriteableFunctPtr,writeable);
}

void test_init_read(void)
{
    FRM_assignChannelRead(&read8);
    
    TEST_ASSERT_EQUAL_INT(channelReadFunctPtr,read8);
}

void test_init_write(void)
{
    FRM_assignChannelWrite(&write8);
    
    TEST_ASSERT_EQUAL_INT(channelWriteFunctPtr,write8);
}
