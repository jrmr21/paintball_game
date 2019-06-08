#include "core_header.h"

extern unsigned char terminal_adress;

void  game_flag_master(const unsigned char players[10])
{
    trame_t   trameS;
    trame_t   trameR;

    int               t1,  t2,  t3;       // time press buttoms
    int8_t            bt1, bt2, bt3;      // buttoms press true or !true
    char              network[4];
    unsigned char     GAME_TIME[4];
    uint32_t          milli;
    uint32_t          second;
    

    create_command(TIME, 600, GAME_TIME);
    trameR.data[0][0]   = '\0';
    terminal_adress     = ADRESS_MASTER;
    network[0]          = terminal_adress;
    network[1]          = ADRESS_BRODCAST;          // default guy
    network[2]          = '\0';
          
    lcd.clear();

    lcd.set_Cursor(0,0);
    lcd.print("FLAGS_GAME");
        
    radio_init_sender("00001");           // change mode sender
    delay(5);
              
    create_trame(&trameS, network, GAME_FLAGS_SELECT, GAME_TIME, END_COMMAND);
    radio_send(&trameS);                // send trame
    radio_send(&trameS);                // send trame

    milli   = millis();
    second  = milli;
    do
    {
      
      key_time_loop(&t1, &t2, &t3);
      key_loop(&bt1, &bt2, &bt3);       // GO TO THE DOC 

      if ((millis() - second) > 1000)      //  send 1hz 
      {  
        second = millis();
        lcd.set_Cursor(0,0);
        lcd.print("FLAGS_GAME");
        lcd.set_Cursor(14,0);
        lcd.print((int) (millis() - milli) / 1000);
        
        /*lcd.set_Cursor(0, 1);
        lcd.printstr("players: ");
        lcd.set_Cursor(10, 1);
        lcd.print(" NONE ...");
        */
        
      }
      
      lcd.backlight();    // set light ON (in loop, shit code..)  
    } while ((millis() - milli) < 600000);
    lcd.clear();  
}


void  game_flag_slave(int game_time, int res[3])
{
      trame_t   trameS;
    trame_t   trameR;

    int               t1,  t2,  t3;       // time press buttoms
    int8_t            bt1, bt2, bt3;      // buttoms press true or !true
      uint32_t          milli;
    uint32_t          second;
    
    lcd.clear();
    lcd.set_Cursor(0,0);
    lcd.print(" *** FLAGS_GAME ***");
    lcd.set_Cursor(0, 1);
    lcd.printstr("players: ");
    lcd.set_Cursor(10, 1);
    lcd.print(" NONE ...");

    milli   = millis();
    second  = milli;
    do
    {
      
      key_time_loop(&t1, &t2, &t3);
      key_loop(&bt1, &bt2, &bt3);       // GO TO THE DOC 

      if ((millis() - second) > 1000)      //  send 1hz 
      {  
        second = millis();
        lcd.set_Cursor(0,0);
        lcd.print("FLAGS_GAME");
        lcd.set_Cursor(14,0);
        lcd.print((int) (millis() - milli) / 1000);
        
        /*lcd.set_Cursor(0, 1);
        lcd.printstr("players: ");
        lcd.set_Cursor(10, 1);
        lcd.print(" NONE ...");
        */
        
      }
      
      lcd.backlight();    // set light ON (in loop, shit code..)  
    } while ((millis() - milli) < 600000);
    lcd.clear();  
}

void  game_flag(int game_time, int res[3])
{
  int       time = 0;

  int       time_r = 0, time_g = 0, time_b = 0;
  int8_t         r = 0,      g = 0,      b = 0;

  uint32_t  mili = millis();
  int8_t    bt1, bt2, bt3;
  
  
  
  while(time <= game_time)
  {
      key_loop(&bt1, &bt2, &bt3);
      
      if ((millis() - mili) > 1000)
      {
        
        mili = millis();
        
        lcd.clear();
        lcd.backlight();
        lcd.set_Cursor(0,0);
        lcd.print("Flag   ");
        lcd.print(time);    
        
        if (r)
        {
              lcd.set_Cursor(0, 1);
                lcd.print("Rouge  ");       
          lcd.print(time_r);
          
          time_r++;
        }
        else if (g)
        {
              lcd.set_Cursor(0, 1);
                lcd.print("Vert   ");     
          lcd.print(time_g);
        
          time_g++;
        }
        else if (b)
        {
              lcd.set_Cursor(0, 1);
                lcd.print("Bleu   ");     
          lcd.print(time_b);
          
          time_b++;
        }
      
      time++;
      } 
      
        if (bt3)
      {
          r = 1;
        g = 0;
        b = 0;
      
      digitalWrite(R, 1);
            digitalWrite(G, 0);
            digitalWrite(B, 0);
      }
      else if (bt2)
      {
          r = 0;
        g = 1;
        b = 0;

      digitalWrite(R, 0);
            digitalWrite(G, 1);
            digitalWrite(B, 0);
      }
      else if (bt1)
      {
          r = 0;
        g = 0;
        b = 1;
      
        digitalWrite(R, 0);
            digitalWrite(G, 0);
            digitalWrite(B, 1);
      }
  
  }
  
  // On renvoie les résultats dans un tableau [R,G,B]
  res[0] = time_r;
  res[1] = time_g;
  res[2] = time_b;
} 
