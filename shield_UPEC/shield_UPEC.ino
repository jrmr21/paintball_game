#include    "core_header.h"


void setup() 
{
  char *line1 = "jrmr";
  char *clean = "                ";
  char *arrow = "<=";
  
  init_pin();
  init_lcd();

  lcd.print(line1);
  lcd.setCursor(14, 0);
  lcd.print(arrow);
  
  int8_t bt1, bt2, bt3;
  
  while (1)
  {
    key_loop(&bt1, &bt2, &bt3);

    Serial.print("bt1: ");Serial.print(bt1);
    Serial.print("bt2: ");Serial.print(bt2);
    Serial.print("bt3: ");Serial.println(bt3);
    
    if (bt1)
    {
      lcd.clear();
      
      //lcd.setCursor(0, 1);
      lcd.print(line1);
      lcd.setCursor(14, 1);
      lcd.print(arrow);
    }
    
    lcd.backlight();    // set light ON (in loop, shit code..)  
  }
}
