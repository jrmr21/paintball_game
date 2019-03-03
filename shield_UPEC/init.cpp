#include    "core_header.h"

void    init_pin(void)
{
  Serial.begin(9600);

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

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
