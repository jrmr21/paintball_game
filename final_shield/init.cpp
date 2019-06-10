#include    "core_header.h"

extern RF24           radio(7, 8);

void    init_pin(void)
{
  Serial.begin(9600);

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  digitalWrite(R, 0);
  digitalWrite(G, 0);
  digitalWrite(B, 0);

  radio.begin();

  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
}

void    init_lcd(void)
{
  lcd.init();
  lcd.begin(16, 2);   // set resolution, angain ?? WHYY !!?
  lcd.clear();
}
