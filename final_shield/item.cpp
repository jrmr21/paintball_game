#include  "core_header.h"

unsigned char terminal_adress = 0;

void  opt_demo(void)
{
      uint8_t i;
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

          if ((millis() - mili) > 1500)    // every 1s
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
      int8_t    bt1, bt2, bt3;
      uint32_t  mili;           // same "unsigned long" but we don't like write ARDUINO shit
      trame_t   trame;
      char      network[4];

      flag  = 0;
      bt3   = 0;
      mili  = millis();
          
      network[0]  = terminal_adress;
      network[1]  = MASTER_ADRESS;
      network[2]  = '\0';
      
      lcd.clear();
      lcd.set_Cursor(0,0);                // X, Y
      lcd.print("it's a SENDER demo ");
      
      lcd.set_Cursor(0,1);
      lcd.print("SEND");
      radio_init_sender("00001");

      while (!bt3)
      {
          key_loop(&bt1, &bt2, &bt3);

          if ((millis() - mili) > 1000)    // evry 1s
          { 
            (flag)? create_trame(&trame, network, GET_TIME, TIME_START, TIME_START, END_COMMAND) : create_trame(&trame, network, TIME_STOP, GET_TIME, END_COMMAND);

            
            flag = !flag;
            debug_trame(&trame);

            lcd.set_Cursor(5, 1);
            lcd.print("=>>");
            
            mili = millis();
          }
          else if ((millis() - mili) > 500)
          {
             lcd.set_Cursor(5, 1);
             lcd.print("=||");
          }
          
          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
      lcd.clear();
}

void  game_mode(void)
{
      int8_t  bt1, bt2, bt3;
      
      lcd.clear();

      lcd.set_Cursor(0,0);
      lcd.print(" *** GAME 1 ***");
      lcd.set_Cursor(0,1);
      
      lcd.print("1 = M | 2 = G");

      key_loop(&bt1, &bt2, &bt3);
      while (!bt3 || !bt2)
      { 
        
          key_loop(&bt1, &bt2, &bt3);


          if (bt1)
          {
            game_master();
          }
          else if (bt2)
          {
            game_slave();
          }
          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
      lcd.clear();
}

void  demo_receive(void)
{
      int8_t  bt1, bt2, bt3;
      char    tempo[32];
      unsigned char    text[32];
      trame_t   trame;
      
      tempo[0]  = '\0';
      text[0]   = '\0';
      lcd.clear();
      lcd.set_Cursor(0,0);
      lcd.print("receive demo ");

      radio_init_receive("00001");
      key_loop(&bt1, &bt2, &bt3);
      while (!bt3)
      {
          key_loop(&bt1, &bt2, &bt3);
          radio_receive(&trame);
          
          if (strcmp(tempo, text) != 0)   // we have a difference
          {
              strcpy(text, tempo);
              lcd.set_Cursor(0, 1);
              lcd.print(clear_line);

              lcd.set_Cursor(0, 1);
              lcd.print((tempo[0]) + 256);
          }

          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
      lcd.clear();
}

void  adress(void)
{
    int8_t  bt1, bt2, bt3;
    char    tempo[32];
    char    text[32];
    
    unsigned char old_terminal_adress = terminal_adress;

    text[0]         = '\0';
    lcd.clear();
    lcd.set_Cursor(0,0);
    lcd.print("terminal_adress");
    lcd.set_Cursor(0,1);
    lcd.print(terminal_adress);

    while (!(bt3))
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
          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
    lcd.clear();
}
