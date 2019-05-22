#include "core_header.h"

static RF24 radio(7, 8); // CE, CSN

void  radio_init_sender(const byte address[6])
{
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void  radio_init_receirve(const byte address[6])
{
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void  radio_receirve(unsigned char *text)
{
      unsigned char texto[32] = "";
      
      if (radio.available()) 
      {
          text[0] = '\0';         // fake clear tab
          
          radio.read(&texto, sizeof(texto));
          Serial.println(texto[0]);

          strcpy(text, texto);
          Serial.print("msg: ");
          Serial.println((int)text[0]);
      }  
}

void  radio_send(const unsigned char *text)
{
  radio.write(text, strlen(text));    // strlen is better of sizeof to calculate size char
  delay(50);
}
