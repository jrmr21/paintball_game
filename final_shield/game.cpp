#include "core_header.h"

extern unsigned char terminal_adress;

void   game_master(void)                // add gamers in room
{
    trame_t   trameS;
    trame_t   trameR;

    int8_t            bt1, bt2, bt3;
    int8_t            cpt_players, kill_trame;
    char              network[4];
    unsigned char     players[10];     // 10 adress of players

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
              radio_send(&trameS);                // send trame
              radio_init_receive("00001");        // change mode receive
          }
          
          trameR.data[0][0]  = '\0';      // reset trame receive
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
	int i = 1; // variable de fin de connexion
	uint32_t  mili = millis();
	
	trame_t trame_send;
	trame_t trame_receive;
	
	lcd.clear();
    
    lcd.set_Cursor(0,0);
    lcd.print(" *** SLAVE ***");

  trame_t t;
	//str_to_trame(t, "013J11F22U33\0");
  const char *tmp = "013J11F22U33\0";
  //const char *tmp = "111111111111\0";
  str_to_trame(&t, tmp);
/*
    trame_t trame;
    radio_receive(&trame);

    trame.adress = terminal_adress;
    trame.adress_to = 255;
    trame.size_trame = 6;

    trame.data[0][0] = 'J';
    trame.data[0][0] = '0';
    trame.data[0][0] = ' ';
    
	while(i)
	{
        // Test du bouton de retour arrière
        key_loop(&bt1, &bt2, &bt3);		
        if (bt3) 
            i = 0;

        if ((millis() - mili) > 500)
		{
            radio_send(trame);            
		}
	}   
*/	
}
