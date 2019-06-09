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
    int               res[3] = {0};
    

    create_command(TIME, 600, GAME_TIME);
    trameR.data[0][0]   = '\0';
    terminal_adress     = ADRESS_MASTER;
    network[0]          = terminal_adress;
    network[1]          = ADRESS_BRODCAST;          // default guy
    network[2]          = '\0';

        
    radio_init_sender("00001");           // change mode sender
    delay(5);
    create_trame(&trameS, network, GAME_FLAGS_SELECT, GAME_TIME, END_COMMAND);
    radio_send(&trameS);                // send trame

    
    game_flag(600, res);

      
    lcd.clear();  
}


void  game_flag_slave(int game_time)
{
    trame_t   trameS;
    trame_t   trameR;

    int res[3] = {0};

    game_flag(game_time, res[3]);


    Serial.println("END GAME");
    lcd.clear();  
}

void  game_flag(int game_time, int res[3])
{
    int               t1,  t2,  t3;       // time press buttoms
    int8_t            bt1, bt2, bt3;      // buttoms press true or !true
    uint32_t          milli;
    uint32_t          second;
    int8_t            team;             // 1 = R, 2 = G, 3 = B, 0 = NONE
    
    milli   = millis();
    second  = milli;
    team    = 0;

    digitalWrite(R, 0);
    digitalWrite(G, 0);
    digitalWrite(B, 0);
        
    lcd.clear();
    lcd.set_Cursor(0,0);
    lcd.print("FLAGS_GAME");
    lcd.set_Cursor(0, 1);
    lcd.printstr("players: ");
    lcd.set_Cursor(10, 1);
    lcd.print(" NONE ...");
    
    while ((uint32_t)((millis() - milli) / 1000) <  game_time)
    {
      
      key_time_loop(&t1, &t2, &t3);
      key_loop(&bt1, &bt2, &bt3);

      Serial.println(t1);

      if ((millis() - second) > 1000)      //  send 1hz 
      {  
        second = millis();
        lcd.set_Cursor(0,0);
        lcd.print("FLAGS_GAME");
        lcd.set_Cursor(12,0);
        lcd.print("    ");
        lcd.set_Cursor(12,0);
        lcd.print((int)game_time - ((uint32_t) (millis() - milli) / 1000));
      }

      if ((t1 > 9) && (team != 1))
      {
        team = 1;
        lcd.set_Cursor(10, 1);
        lcd.print("    ");
        lcd.set_Cursor(10, 1);
        lcd.print("ROUGE");
        digitalWrite(R, 1);
        digitalWrite(G, 0);
        digitalWrite(B, 0);
      }
      else if ((t2 > 9) && (team != 2))
      {
        team = 2;
        lcd.set_Cursor(10, 1);
        lcd.print("     ");
        lcd.set_Cursor(10, 1);
        lcd.print(" VERT");
        digitalWrite(R, 0);
        digitalWrite(G, 1);
        digitalWrite(B, 0);
      }
      else if ((t3 > 9) && (team != 3))
      {
        team = 3;
        lcd.set_Cursor(10, 1);
        lcd.print("     ");
        lcd.set_Cursor(10, 1);
        lcd.print("BLEUE");
        digitalWrite(R, 0);
        digitalWrite(G, 0);
        digitalWrite(B, 1);
      }
      
      
      lcd.backlight();    // set light ON (in loop, shit code..)  
    }
  
  // On renvoie les résultats dans un tableau [R,G,B]
  res[0] = 0;
  res[1] = 0;
  res[2] = 0;
} 
