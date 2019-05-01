#include "core_header.h"


void frame1(int8_t *frame)
{
  lcd.clear();
  
  char *line1 = "-send data";             //  2
  char *line2 = "-recerve data";          //  1
  
  lcd.set_Cursor(0, 0);
  lcd.printstr(line1);
  lcd.set_Cursor(0, 1);
  lcd.printstr(line2);  

  *frame = 1;
}


void frame2(int8_t *frame)
{
  lcd.clear();
  
  char *line1 = "-snd, rcv";              //  4
  char *line2 = "-game";                 //   3
  
  lcd.set_Cursor(0, 0);
  lcd.printstr(line1);
  lcd.set_Cursor(0, 1);
  lcd.printstr(line2);  

  *frame = 2;
} 
