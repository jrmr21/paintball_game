#include "core_header.h"

void	game_one_master(void)
{
      int8_t  i;
      int8_t  j;
      int8_t  bt1, bt2, bt3;
      char    tempo[32];
      char    text[32];
      char    players[5][3];
      
      j         = 0;
      i         = 1;
      tempo[0]  = '\0';
      text[0]   = '\0';
      
      lcd.clear();
      
      lcd.set_Cursor(0,0);
      lcd.print(" *** MASTER ***");

      radio_init_receirve("00001");
      while (i)
      {
          key_loop(&bt1, &bt2, &bt3);


          radio_receirve(tempo);

          /*
          for (int8_t k = 0; 
              if (strcmp(tempo, text) != 0)   // we have a difference
              {
                  strcpy(text, tempo);
              }
            */
  
          if (bt3) 
          {
            i = 0;
          }
          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
      lcd.clear();

}
