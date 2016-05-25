#include <dispatchSerial.h>
#include <dispatch.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  
  DIS_assignChannelReadable(&readable);
  DIS_assignChannelWriteable(&writeable);
  DIS_assignChannelRead(&read);
  DIS_assignChannelWrite(&write);
  
  DIS_init();
  
  DIS_subscribe("foo", &mySubscriberFunction);
}

void loop() {
  static int32_t lastMillis = 0;
  const int32_t TIME_INTERVAL = 10000;
  uint32_t now = millis();
  
  DIS_process();
}

void mySubscriberFunction(void){
  static uint16_t i = 0;
  
  i++;
  
  /* publish i back to the sender to 'close the loop' */
  DIS_publish("i,u16", &i);
}
