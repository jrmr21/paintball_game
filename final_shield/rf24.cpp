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
    unsigned char texto[32] = {1, 255, 15,'J', 1, 1, 'M', 2, 2, 'A', 3, 3, '\0'};
	  int i = 3;
	  int number_command = 0;
    //  if (radio.available()) 
    //  {
          //radio.read(&texto, sizeof(texto));

		      trame->adress = texto[0];
		      trame->adress_to = texto[1];
		  
		      trame->size_trame = texto[2];

     // trame->data[0][0] = 5;
     // trame->data[0][1] = 5;
     // trame->data[0][2] = 5;
		      while(texto[i] != '\0')
		      {
		          trame->data[number_command][0] = texto[i];
			        i++;
		      	  trame->data[number_command][1] = texto[i]; 
			        i++;
 			        trame->data[number_command][2] = texto[i];
			        i++;
			  
			        number_command++;
		      }
		      trame->number_command = number_command;		  
   //   }


}

void  radio_send(trame_t *t)
{
  unsigned char *text;
  
  trame_to_str(t, text);

  /*Serial.println(" send: ");
  while(*text)
    Serial.print((char)*text++);
  Serial.println(" end send");*/
                                      // WARNING USE CONST OR NOT
  radio.write(text, strlen(text));    // strlen is better of sizeof to calculate size char
  delay(50);
}
