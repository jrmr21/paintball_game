#include "core_header.h"

static RF24           radio(7, 8); // CE, CSN
extern unsigned char  terminal_adress;

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

    unsigned char texto[32] = " ";

    if (radio.available()) 
    {
        texto[0] = '\0';
        radio.read(&texto, sizeof(texto));
        
        print_str(texto);
        print_str((unsigned char)texto[7]);
        
        str_to_trame(trame, texto);
        
        if ((trame->adress_to != ADRESS_BRODCAST) && (trame->adress_to != terminal_adress)) // check if you can read or not
                                                                                            //  your adress or brodcast
        {
          trame->data[0][0] = '\0';
        }
    }
}

void  radio_send(trame_t *t)
{
  unsigned char text[50] = "\0";  
  trame_to_str(t, text);

  radio.write(text, t->size_trame);    // strlen is better of sizeof to calculate size char
  delay(50);
}
