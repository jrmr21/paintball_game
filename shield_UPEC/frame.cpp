#include "core_header.h"

void frame1(int8_t *frame)
{
  lcd.clear();
  
  char *line1 = "-send data";
  char *line2 = "-recerve data";
  
  lcd.set_Cursor(0, 0);
  lcd.printstr(line1);
  lcd.set_Cursor(0, 1);
  lcd.printstr(line2);  

  *frame = 1;
}

void frame2(int8_t *frame)
{
  lcd.clear();
  
  char *line1 = "-snd, rcv";
  char *line2 = "-game";
  
  lcd.set_Cursor(0, 0);
  lcd.printstr(line1);
  lcd.set_Cursor(0, 1);
  lcd.printstr(line2);  

  *frame = 2;
} 
