#include  "radio_admin.h"


void setup() 
{
  Serial.begin(9600);
  init_radioAdmin();

  while (1)
  {
    loop_radioAdmin();
  } 
}
