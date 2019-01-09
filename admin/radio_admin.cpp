#include  "radio_admin.h"

void  init_radioAdmin()
{
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void  loop_radioAdmin()
{
  if (radio.available()) 
  {
    char text[32] = "";
    
    radio.read(&text, sizeof(text));
    Serial.println(text);
   }
}
