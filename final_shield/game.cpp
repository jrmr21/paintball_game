#include "core_header.h"

extern unsigned char terminal_adress;

void  game_lobby(const unsigned char  players[10])
{
    int8_t  bt1, bt2, bt3;
    
    lcd.clear();
    
    lcd.set_Cursor(0,0);
    lcd.print("  *** LOBBY *** ");

    lcd.set_Cursor(0,1);
    lcd.print("  FLAG | BOMB   ");
    
    do
    { 
        key_loop(&bt1, &bt2, &bt3);
    
        if (bt2)
        {
          game_flag_master( players );
          lcd.set_Cursor(0,0);
          lcd.print("  *** LOBBY *** ");
      
          lcd.set_Cursor(0,1);
          lcd.print("  FLAG | BOMB   ");
        }
        else if (bt1)
        {
          //game_bomb_master();
          lcd.set_Cursor(0,0);
          lcd.print("  *** LOBBY *** ");
      
          lcd.set_Cursor(0,1);
          lcd.print("  FLAG | BOMB   ");
        }
        lcd.backlight();    // set light ON (in loop, shit code..)      
    }
    while (!bt3);
    
    lcd.clear();
}

void   game_master(void)                // add gamers in room
{
    trame_t   trameS;
    trame_t   trameR;

    int8_t            bt1, bt2, bt3;
    int8_t            cpt_players, kill_trame;
    char              network[4];
    unsigned char     players[10] = {0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0};     // 10 adress of players

    players[0]          = ADRESS_MASTER;
    cpt_players         = 1;    // master is a player too
    kill_trame          = 0;
    
    trameR.data[0][0]   = '\0';
    terminal_adress     = ADRESS_MASTER;
    network[0]          = terminal_adress;
    network[1]          = ADRESS_BRODCAST;          // default guy
    network[2]          = '\0';
          
    lcd.clear();
    lcd.set_Cursor(0,0);
    lcd.print(" *** MASTER ***");
    lcd.set_Cursor(0, 1);
    lcd.printstr("players: ");
    lcd.set_Cursor(10, 1);
    lcd.print(cpt_players);
          
    radio_init_receive("00001");
    do
    {
        key_loop(&bt1, &bt2, &bt3);
        radio_receive(&trameR);
          
        if (trameR.data[0][0] != '\0')        // we have a data
        { 
          if ((strcmp( JOIN_REQUEST, trameR.data[0]) == 0))   // we have a join request 
          {
              radio_init_sender("00001");           // change mode sender
              delay(5);
              network[1] = trameR.adress;
            
               for (int8_t b = 0; b < 10; b++)
               {
                  if (trameR.adress == players[b] || cpt_players > 10)   // error player
                  {                                                     // send conflit adress...
                    kill_trame = 1;
                    create_trame(&trameS, network, CONFLIT_ADRESS, END_COMMAND);
                  }
               }
             
               if (!kill_trame)                                     // if we have no problem
               {                                                    // accept request
                  players[cpt_players++] = trameR.adress;           
                  create_trame(&trameS, network, JOIN_VALIDATION, END_COMMAND);
               }
               else
                kill_trame = 0;                   // reset kill accept

              delay(5);
              radio_send(&trameS);                // send trame
              radio_send(&trameS);                // send trame
          }
          trameR.data[0][0]  = '\0';      // reset trame receive
          lcd.set_Cursor(0, 1);
          lcd.printstr("players: ");
          lcd.set_Cursor(10, 1);
          lcd.print(cpt_players);
          radio_init_receive("00001");        // change mode receive
        }
        else if (bt2 || bt1)
        {
          game_lobby(players);
          
          lcd.set_Cursor(0,0);
          lcd.print(" *** MASTER ***");
          lcd.set_Cursor(0, 1);
          lcd.printstr("players: ");
          lcd.set_Cursor(10, 1);
          lcd.print(cpt_players);
        }
        
        lcd.backlight();    // set light ON (in loop, shit code..)    
    } while (!bt3);
    
    terminal_adress = 5;    // restart default adress
    lcd.clear();
}

void    game_slave(void)
{
	  trame_t   trameS;
    trame_t   trameR;

    int8_t            bt1, bt2, bt3;
    uint8_t           connection;
    char              network[4];

    connection          = 0;
    trameR.data[0][0]   = '\0';
    network[0]          = terminal_adress;
    network[1]          = ADRESS_MASTER;          // default guy
    network[2]          = '\0';

    digitalWrite(R, 1);
    digitalWrite(G, 1);
    digitalWrite(B, 0);
            
    lcd.clear();
    lcd.set_Cursor(0,0);
    lcd.print(" *** SLAVE ***");
    lcd.set_Cursor(0, 1);
    lcd.printstr("no connected..");

    do
    {
        key_loop(&bt1, &bt2, &bt3);

        if (bt2 && (!connection))                     // if you are connected you can't connect again
        {
            radio_init_sender("00001");                                   // change mode sender
            create_trame(&trameS, network, JOIN_REQUEST, END_COMMAND);
            radio_send(&trameS);

            delay(10);
            radio_init_receive("00001");                          // change mode receive
            delay(10);
            
            lcd.set_Cursor(0, 1);
            lcd.print(clear_line);
            lcd.set_Cursor(0, 1);
            lcd.print("try connection..");

            for (uint8_t j = 0; (j < 200) && (!connection); j++)                     // wait receive data 200ms with 200 try
            {
              radio_receive(&trameR);
              
              if (trameR.data[0][0] != '\0')                          // we have a data
              {
                if ((strcmp( JOIN_VALIDATION, trameR.data[0]) == 0))   // we have a join accept
                {
                  connection = 1;
                  digitalWrite(R, 0);
                  digitalWrite(G, 0);
                  digitalWrite(B, 1);
                  radio_init_receive("00001");                          // change mode receive
                }
              }
              delay(1);
            }
            lcd.set_Cursor(0, 1);
            lcd.print(clear_line);
            lcd.set_Cursor(0, 1);
            lcd.print((!connection)? "FAIL connect...": " CONNECTED");
            trameR.data[0][0] = '\0';
        }
        else if (connection) 
        {   
          radio_receive(&trameR);

          if (trameR.data[0][0] != '\0')
          {
         
            if ((strcmp( GAME_FLAGS_SELECT, trameR.data[0]) == 0) && (TIME == trameR.data[1][0]))
            {
              int game_time = decompress_char(trameR.data[1] + 1);    // Second

              game_flag_slave(game_time);
              trameR.data[0][0] = '\0';
            }
            else if ((strcmp( GAME_BOM_SELECT, trameR.data[0]) == 0) && (TIME == trameR.data[1][0]))
            {
                // BOMB GAME ADD HERE
            }

            lcd.set_Cursor(0,0);
            lcd.print(" *** SLAVE ***");
            lcd.set_Cursor(0, 1);
            lcd.printstr(" CONNECTED *");
          }
        }

        lcd.backlight();    // set light ON (in loop, shit code..)    
    } while (!bt3);

    digitalWrite(R, 0);
    digitalWrite(G, 0);
    digitalWrite(B, 0);
    lcd.clear();	
    
}
