#include "HardwareSerial.h"
#include "dispatchSerial.h"

void read(uint8_t * data, uint16_t length)
{
    Serial.readBytes((char*)(data), length);
}

void write(uint8_t * data, uint16_t length)
{
    Serial.write((char*)(data), length);
}

uint16_t readable()
{
    return (uint16_t)Serial.available();
}

uint16_t writeable()
{
    return (uint16_t)Serial.availableForWrite();
}
