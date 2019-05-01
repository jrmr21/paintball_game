#include "core_header.h"

static RF24 radio(7, 8); // CE, CSN

void  radio_init_sender(const byte address[6])
{
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void  radio_init_recerve(const byte address[6])
{
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void  radio_recerve(char text[32])
{
      if (radio.available()) 
      {
          text[0] = '\0';         // fake clear tab
          
          radio.read(&text, sizeof(text));
          Serial.println(text);
      }  
}

void  radio_send(const char text[32])
{
  radio.write(&text, sizeof(text));
  delay(100);
}
