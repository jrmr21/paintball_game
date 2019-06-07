#include  "core_header.h"

unsigned char terminal_adress = 5;

void  opt_demo(void)
{
      int8_t bt1, bt2, bt3;
      
      lcd.clear();
      lcd.print(" it's a demo ");
      do
      {
          key_loop(&bt1, &bt2, &bt3);
          
          
          lcd.backlight();    // set light ON (in loop, shit code..)  
      } while (!bt3);
      lcd.clear();
}

void  led(void)
{
      int8_t bt1, bt2, bt3;
      uint32_t  mili; 
      
      mili  = millis();
      lcd.clear();
      lcd.print(" it's a demo ");
      
      do
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
          
          lcd.backlight();    // set light ON (in loop, shit code..)  
      } while (!bt3);
      
      digitalWrite(R, 0);
      digitalWrite(G, 0);
      digitalWrite(B, 0);
      lcd.clear();
}

void  demo_sender(void)
{
      int8_t    flag;
      int8_t    bt1, bt2, bt3;
      uint32_t  mili;            // same "unsigned long" but we don't like write ARDUINO shit
      trame_t   trame;
      char      network[4];

      flag  = 0;
      bt3   = 0;
      mili  = millis();
      terminal_adress   = ADRESS_MASTER;
      network[0]        = terminal_adress;
      network[1]        = ADRESS_BRODCAST;          // default guy
      network[2]        = '\0';
      
      lcd.clear();
      lcd.set_Cursor(0,0);                // X, Y
      lcd.print("it's a SENDER demo ");
      
      lcd.set_Cursor(0,1);
      lcd.print("SEND");
      radio_init_sender("00001");
      
      do
      {
          key_loop(&bt1, &bt2, &bt3);

          if ((millis() - mili) > 1000)      //  send 1hz 
          {             
              (flag)? create_trame(&trame, network, TIME_GET, TIME_GET, TIME_GET, TIME_START, TIME_START, END_COMMAND) : create_trame(&trame, network, TIME_STOP, TIME_GET, END_COMMAND);
              radio_send(&trame);

              flag = !flag;
              mili = millis();
              lcd.set_Cursor(5, 1);
              lcd.print("=>>");
          }
          else if ((millis() - mili) > 500)
          {
             lcd.set_Cursor(5, 1);
             lcd.print("=||");
          }    
          lcd.backlight();    // set light ON (in loop, shit code..)  
      
      } while (!bt3);
      
      terminal_adress = 5;    // restart default adress
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
      do
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
      while (!bt3);
      
      lcd.clear();
}

void  demo_receive(void)
{
      int8_t    bt1, bt2, bt3;
      char      tmp[4];
      trame_t   trame;

      trame.data[0][0]  = '\0';
      tmp[0]            = '\0';
      
      lcd.clear();
      lcd.set_Cursor(0,0);
      lcd.print("receive demo ");
      radio_init_receive("00001");
      
      do
      {
          key_loop(&bt1, &bt2, &bt3);
          radio_receive(&trame);
          
          if (trame.data[0][0] != '\0')
          { 
            //  debug_trame(&trame);
            if ((strcmp( tmp, trame.data[0]) != 0) && (trame.adress_to == ADRESS_BRODCAST))
            {
              strcpy(tmp, trame.data[0]);
            }
          }
          
          lcd.set_Cursor(0, 1);
          lcd.printstr(tmp);
          
          lcd.backlight();    // set light ON (in loop, shit code..)  
      } while (!bt3);
      
      lcd.clear();
}

void  adress(void)
{
    int8_t  bt1, bt2, bt3;  
    unsigned char old_terminal_adress = terminal_adress;

    lcd.clear();
    lcd.set_Cursor(0,0);
    lcd.print("terminal_adress");
    lcd.set_Cursor(0,1);
    lcd.print(terminal_adress);

    do
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
          terminal_adress++;
        
        if (bt2)
          terminal_adress--;

        if (terminal_adress > 253)
          terminal_adress = 5;
        else if (terminal_adress < 5)
          terminal_adress = 253;
          
          lcd.backlight();    // set light ON (in loop, shit code..)  
      } while (!bt3);
    lcd.clear();
}
