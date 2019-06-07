#include "core_header.h"

static RF24 radio(7, 8); // CE, CSN

void  radio_init_sender(const byte address[6])    // initialisation du mode sender
{
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void  radio_init_receive(const byte address[6])   // initialisation du mode receive
{
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void  radio_receive(trame_t* trame)           // read data and write all in struct trame
{
    unsigned char texto[32] = " ";

    if (radio.available()) 
    {
        texto[0] = '\0';
        radio.read(&texto, sizeof(texto));
        str_to_trame(trame, texto);
    }
}

void  radio_send(trame_t *t)                // read trame and send data
{
  unsigned char text[50] = "\0";  
  trame_to_str(t, text);
  radio.write(text, strlen(text));    // strlen is better of sizeof to calculate size char
  delay(50);
}
