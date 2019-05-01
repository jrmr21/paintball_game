#include  "core_header.h"

void  opt_demo(void)
{
      int8_t i;
      int8_t bt1, bt2, bt3;
      
      i = 1;
      lcd.clear();
      lcd.print(" it's a demo ");
      while (i)
      {
          key_loop(&bt1, &bt2, &bt3);
          
          
          if (bt3)  i = 0;
          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
      lcd.clear();
}


void  radio_sender(void)
{
      int8_t i;
      int8_t bt1, bt2, bt3;
      
      i = 1;
      lcd.clear();
      lcd.print("it's a SENDER demo ");
      while (i)
      {
          key_loop(&bt1, &bt2, &bt3);
          
          
          if (bt3)  i = 0;
          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
      lcd.clear();
}

void  radio_recerve(void)
{
      int8_t i;
      int8_t bt1, bt2, bt3;
      
      i = 1;
      lcd.clear();
      lcd.print("it's a RECERVE demo ");
      while (i)
      {
          key_loop(&bt1, &bt2, &bt3);
          
          
          if (bt3)  i = 0;
          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
      lcd.clear();
}
