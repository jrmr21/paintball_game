#include "core_header.h"

extern unsigned char terminal_adress;

void  game_flag_master(const unsigned char players[10])
{
    trame_t   trameS;
    trame_t   trameR;

    int               t1,  t2,  t3;       // time press buttoms
    int8_t            bt1, bt2, bt3;      // buttoms press true or !true
    char              network[4];
    unsigned char     GAME_TIME[4]  = {'F'};
    uint32_t          milli;
    uint32_t          second;
    uint8_t           i;
    int               res[3] = {0};
    
    create_command(TIME, 120, GAME_TIME);
    
    trameR.data[0][0]   = '\0';
    terminal_adress     = ADRESS_MASTER;
    network[0]          = terminal_adress;
    network[1]          = ADRESS_BRODCAST;          // default guy
    network[2]          = '\0';
        
    radio_init_sender("00001");           // change mode sender
    delay(10);

    create_trame(&trameS, network, GAME_FLAGS_SELECT, GAME_TIME, END_COMMAND);
    radio_send(&trameS);                // send trame

    game_flag(120, res);
    i                 =    1;         // master is 0
    
          // ++++++++++++++++++++ go to stop all game

    while ((players[i] != 0) && (i < 11))
    {
      radio_init_sender("00001");           // change mode sender
      delay(10);

      network[1]          = players[i];
      create_trame(&trameS, network, SCORE, END_COMMAND);

      delay(5);
      radio_send(&trameS);                // send
      radio_send(&trameS);                // send
      
      trameR.data[0][0] = '\0'; 
      radio_init_receive("00001");
      
      for (uint8_t j = 0; (j < 200) && (trameR.data[0][0] == '\0'); j++)
      {
          radio_receive(&trameR);

          if (trameR.data[0][0] != '\0')
            debug_trame(&trameR);
            
          if (((trameR.data[0][0]) == TEAM_RED) && ((trameR.data[1][0]) == TEAM_GREEN) && ((trameR.data[2][0]) == TEAM_BLUE))
          {
            res[0] += decompress_char(trameR.data[0] + 1);
            res[1] += decompress_char(trameR.data[1] + 1);
            res[2] += decompress_char(trameR.data[2] + 1);
            
          }
          else
            trameR.data[0][0] = '\0'; 
          delay(1);
      }
      i++;
    }


    lcd.set_Cursor(0,0);
    lcd.print("WINER IS :");

    if (res[0] > (res[1] && res[2]))
    { 
      lcd.set_Cursor(0, 1);
      lcd.printstr("RED :");
      
      lcd.set_Cursor(10, 1);
      lcd.print(res[0]);
    }
    else if (res[1] > (res[0] && res[2]))
    {
      lcd.set_Cursor(0, 1);
      lcd.printstr("GREEN :");
      
      lcd.set_Cursor(10, 1);
      lcd.print(res[1]);      
    }
    else if (res[2] > (res[0] && res[1]))
    {
      lcd.set_Cursor(0, 1);
      lcd.printstr("BLUE :");
      
      lcd.set_Cursor(10, 1);
      lcd.print(res[2]);
    }
    else
    {
      lcd.set_Cursor(0, 1);
      lcd.printstr("GAME_OVER");
    }
    
    
    lcd.backlight();    // set light ON (in loop, shit code..)  
    delay(5000);
    lcd.clear();  
}


void  game_flag_slave(int game_time)
{
    trame_t   trameS;
    trame_t   trameR;

    int res[3] = {0};
    int i      = 0;

    unsigned char     SC_R[4]  = {'F'};
    unsigned char     SC_G[4]  = {'F'};
    unsigned char     SC_B[4]  = {'F'};
    char              network[4];

    network[0]          = terminal_adress;
    network[1]          = ADRESS_MASTER;          // default guy
    network[2]          = '\0';
    trameR.data[0][0]   = '\0'; 
    
    game_flag(game_time, res[3]);
    
    radio_init_receive("00001");

    create_command(TEAM_RED , res[0], SC_R);
    create_command(TEAM_GREEN, res[1], SC_G);
    create_command(TEAM_BLUE, res[2], SC_B);
      
    for (i; (i < 2000); i++)
    {
        radio_receive(&trameR);
          
        if (((trameR.data[0][0]) == SCORE))
        {
          create_trame(&trameS, network, SC_R, SC_G, SC_B, END_COMMAND);
          radio_init_sender("00001");           // change mode sender
          delay(20);
            
          radio_send(&trameS);                // send
          radio_send(&trameS);                // send
        }
        else
          trameR.data[0][0] = '\0'; 
        
        delay(1);
    }

    lcd.clear();  
}

void  game_flag(int game_time, int res[3])
{
    int               t1,  t2,  t3;       // time press buttoms
    int8_t            bt1, bt2, bt3;      // buttoms press true or !true
    uint32_t          milli;
    uint32_t          second;
    int8_t            team;             // 1 = R, 2 = G, 3 = B, 0 = NONE

      // Pour renvoyer les résultats dans un tableau [R,G,B]
    res[0] = 0;
    res[1] = 0;
    res[2] = 0;
    
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


      if ((millis() - second) > 1000)      //  send 1hz 
      {  
        second = millis();
        lcd.set_Cursor(0,0);
        lcd.print("FLAGS_GAME");
        lcd.set_Cursor(12,0);
        lcd.print("    ");
        lcd.set_Cursor(12,0);
        lcd.print((int)game_time - ((uint32_t) (millis() - milli) / 1000));

        switch (team)
        {
          case 1: 
                  res[0]++;    // RED
                  break;
          case 2: 
                  res[1]++;    // GREEN
                  break;
          case 3: 
                  res[2]++;    // BLUE
                  break;
          default : break;
        }
      }

      if ((t1 > 9) && (team != 1))
      {
        team = 1;
        lcd.set_Cursor(10, 1);
        lcd.print("    ");
        lcd.set_Cursor(12, 1);
        lcd.print("RED");
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
        lcd.print("GREEN");
        digitalWrite(R, 0);
        digitalWrite(G, 1);
        digitalWrite(B, 0);
      }
      else if ((t3 > 9) && (team != 3))
      {
        team = 3;
        lcd.set_Cursor(10, 1);
        lcd.print("     ");
        lcd.set_Cursor(11, 1);
        lcd.print("BLUE");
        digitalWrite(R, 0);
        digitalWrite(G, 0);
        digitalWrite(B, 1);
      }
      
      
      lcd.backlight();    // set light ON (in loop, shit code..)  
    }
} 
