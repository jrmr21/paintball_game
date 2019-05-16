#include "radio_slave.h"

    void init_radioSlave(){
      radio.begin();
      radio.openWritingPipe(address);
      radio.setPALevel(RF24_PA_MIN);
      radio.stopListening();      
    }

    void transmit(char* buf){
      radio.write(buf, strlen(buf));
    }
