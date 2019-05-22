#include  "core_header.h"

unsigned char terminal_adress = 0;

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

void  led(void)
{
      int8_t i;
      int8_t bt1, bt2, bt3;
      uint32_t  mili; 
      
      i     = 1;
      mili  = millis();
      lcd.clear();
      lcd.print(" it's a demo ");
      
      while (i)
      {
          key_loop(&bt1, &bt2, &bt3);

          if ((millis() - mili) > 1500)    // evry 1s
          {
            mili  = millis(); 
             
            digitalWrite(R, 1);
            digitalWrite(G, 0);
            digitalWrite(B, 0);
          }
          else if ((millis() - mili) > 1000)
          {
            digitalWrite(R, 0);
            digitalWrite(G, 1);
            digitalWrite(B, 0);
          }
          else if ((millis() - mili) > 500)
          {
            digitalWrite(R, 0);
            digitalWrite(G, 0);
            digitalWrite(B, 1);
          }
          
          if (bt3)  i = 0;
          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
      digitalWrite(R, 0);
      digitalWrite(G, 0);
      digitalWrite(B, 0);
      lcd.clear();
}

void  demo_sender(void)
{
      int8_t    flag;
      int8_t    i;
      int8_t    bt1, bt2, bt3;
      uint32_t  mili;           // same "unsigned long" but we don't like write ARDUINO shit
      unsigned char      test[2];

      i     = 1;
      flag  = 0;
      mili  = millis();
      lcd.clear();
      lcd.set_Cursor(0,0);                // X, Y
      lcd.print("it's a SENDER demo ");
      
      lcd.set_Cursor(0,1);
      lcd.print("SEND");
      radio_init_sender("00001");
      
      while (i)
      {
          key_loop(&bt1, &bt2, &bt3);

          if ((millis() - mili) > 1000)    // evry 1s
          { 
            test[0] = (flag)? 223 : 130;
            test[1] = '\0';
            flag = !flag;

            radio_send(test);
            
            lcd.set_Cursor(5, 1);
            lcd.print("=>>");
            
            mili = millis();
          }
          else if ((millis() - mili) > 500)
          {
             lcd.set_Cursor(5, 1);
             lcd.print("=||");
          }
          
          if (bt3)  i = 0;
          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
      lcd.clear();
}

void  game_one(void)
{
      int8_t  i;
      int8_t  bt1, bt2, bt3;

      i         = 1;
      
      lcd.clear();
      
      lcd.set_Cursor(0,0);
      lcd.print(" *** GAME 1 ***");

      lcd.set_Cursor(0,1);
      lcd.print("1 = M | 2 = G");
      
      while (i)
      {
          key_loop(&bt1, &bt2, &bt3);


          if (bt1)
          {
            game_one_master();
            i = 0;
          }
          else if (bt2)
          {

            i = 0;
          }
          else if (bt3)  i = 0;
          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
      lcd.clear();
}

void  demo_receirve(void)
{
      int8_t  i;
      int8_t  bt1, bt2, bt3;
      char    tempo[32];
      unsigned char    text[32];
      
      i         = 1;
      tempo[0]  = '\0';
      text[0]   = '\0';
      lcd.clear();
      lcd.set_Cursor(0,0);
      lcd.print("RECEIRVE demo ");

      radio_init_receirve("00001");
      while (i)
      {
          key_loop(&bt1, &bt2, &bt3);

          radio_receirve(tempo);
          
          if (strcmp(tempo, text) != 0)   // we have a difference
          {
              strcpy(text, tempo);
              lcd.set_Cursor(0, 1);
              lcd.print(clear_line);

              lcd.set_Cursor(0, 1);
              lcd.print(((int)tempo[0]) + 256);
          }
          
          if (bt3)  i = 0;
          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
      lcd.clear();
}

void  adress(void)
{
    int8_t  i;
    int8_t  bt1, bt2, bt3;
    char    tempo[32];
    char    text[32];
    unsigned char old_terminal_adress = terminal_adress;
  
    i               = 1;
    text[0]         = '\0';
    lcd.clear();
    lcd.set_Cursor(0,0);
    lcd.print("terminal_adress");
    lcd.set_Cursor(0,1);
    lcd.print(terminal_adress);

    while (i)
    {
        key_loop(&bt1, &bt2, &bt3);
    
        if (old_terminal_adress != terminal_adress)
        {
          old_terminal_adress = terminal_adress;
          
          lcd.set_Cursor(0,1);
          lcd.print(clear_line);
          lcd.set_Cursor(0,1);
          lcd.print(terminal_adress);
        }
        
        if (bt1)
        {
            terminal_adress++;
            // Si on incremente a 255 on passe tout de suite a 0
            if (terminal_adress == 255)
              terminal_adress = 0;
        }
        
        if (bt2)
        {
            terminal_adress--;
            // Si on décremente a 0 on passe tout de suite a 254
            if (terminal_adress == 255)
              terminal_adress = 254;
        }

   
        if (bt3)  i = 0;
          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
      
    lcd.clear();
}
