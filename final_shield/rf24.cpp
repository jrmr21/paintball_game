#include "core_header.h"

static RF24 radio(7, 8); // CE, CSN

void  radio_init_sender(const byte address[6])
{
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void  radio_init_receive(const byte address[6])
{
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void  radio_receive(trame_t* trame)
{
    unsigned char texto[32];
	  int i = 3;
	  int number_command = 0;

    if (radio.available()) 
    {
      radio.read(&texto, sizeof(texto));
    }
}

void  radio_send(trame_t *t)
{
  unsigned char text[50] = "\0";  
  trame_to_str(t, text);
  radio.write(text, strlen(text));    // strlen is better of sizeof to calculate size char
  delay(50);
}
