#include "core_header.h"

static RF24           radio(7, 8); // CE, CSN
extern unsigned char  terminal_adress;

void  radio_init_sender(const byte address[6])
{
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void  radio_init_receive(const byte address[6])
{
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
        str_to_trame(trame, texto);
       
        if ((trame->adress_to != ADRESS_BRODCAST) && (trame->adress_to != terminal_adress)) // check if you can read or not
                                                                                            //  your adress or brodcast
        {
          trame->data[0][0] = '\0';
        }
        else if (trame->secure == 2)
        {
          radio_init_sender("00001");           // change mode sender
          delay(7);
          char      network[4];
          trame_t   trameS;

          network[0]          = terminal_adress;
          network[1]          = trame->adress_to;          // default guy
          network[2]          = '\0';
    
          create_trame(&trameS, network, GAME_STOP, END_COMMAND);
          radio_send(&trameS);
          radio_send(&trameS);
          radio_send(&trameS);
          radio_init_receive("00001");
        }
    }
}

void  radio_send(trame_t *t)
{
  unsigned char text[50] = "\0";  
  
  trame_to_str(t, text);

  radio.write(text, t->size_trame);    // strlen is better of sizeof to calculate size char
  delay(5);
}

int  radio_send_secure(trame_t *t)
{
  trame_t   trameR;  
  uint8_t   snd_succes;

  t->secure           = 2;
  trameR.data[0][0]   = '\0';

  for (uint8_t i = 0; (i < 6) && (strcmp( SUCCES_RECEIVE, trameR.data[0]) != 0); i++)
  {
    radio_init_sender("00001");           // change mode sender
    delay(7);
    
    radio_send(t);
    
    radio_init_receive("00001");
    delay(5);
    for (uint8_t i = 0; (i < 100) && (trameR.data[0][0] == '\0'); i++)
    {
      radio_receive(&trameR);
      delay(1);
    } 
  }
  
  radio_init_sender("00001");           // change mode sender
  return ((strcmp( SUCCES_RECEIVE, trameR.data[0]) == 0)? 0 : 1);
}
