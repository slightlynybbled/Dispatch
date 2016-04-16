#define WRITE_DATA_LENGTH 64
#define READ_DATA_LENGTH 64

uint16_t readableIndex = 0;
uint16_t writeableIndex = 0;

uint8_t writeData[WRITE_DATA_LENGTH] = {0};
uint8_t readData[READ_DATA_LENGTH] = {0};

void channel_reset(void){
    readableIndex = 0;
    writeableIndex = 0;
    
    int i;
    for(i = 0; i < WRITE_DATA_LENGTH; i++){
        writeData[i] = 0;
    }
    
    for(i = 0; i < READ_DATA_LENGTH; i++){
        readData[i] = 0;
    }
}

uint16_t readable(void){
    return readableIndex;
}

uint16_t writeable(void){
    return WRITE_DATA_LENGTH - writeableIndex;
}

void read8(void* data, uint16_t length){
    readableIndex -= length;
    if(readableIndex & 0x8000){
        readableIndex = 0;
    }
    
    int i;
    uint8_t* dataPtr = (uint8_t*)data;
    for(i = 0; i < length; i++){
        dataPtr[i] = readData[i];
    }
}

void write8(void* data, uint16_t length){
    writeableIndex -= length;
    if(writeableIndex & 0x8000){
        writeableIndex = 0;
    }
    
    int i;
    uint8_t* dataPtr = (uint8_t*)data;
    for(i = 0; i < length; i++){
        writeData[i] = dataPtr[i];
    }
}
