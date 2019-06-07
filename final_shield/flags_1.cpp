#include "core_header.h"

extern unsigned char terminal_adress;

void    game_flag_master(unsigned char players[10], int8_t cpt_players)
{
    trame_t   trameS;
    trame_t   trameR;

    int8_t            bt1, bt2, bt3;
    int               t_bt1, t_bt2, t_bt3;
    uint32_t          t;
    char              network[4];
    unsigned char     time_game[4];
    
    unsigned char     time_r[4];
    unsigned char     time_b[4];
    unsigned char     time_g[4];
    
    create_command(TIME, 600, time_game);    // 10 mins time of game duration
    
    trameR.data[0][0]   = '\0';
    terminal_adress     = ADRESS_MASTER;
    network[0]          = terminal_adress;
    network[1]          = ADRESS_BRODCAST;          // default guy
    network[2]          = '\0';

    lcd.clear();
    lcd.set_Cursor(0,0);
    lcd.print("** FLAGS GAME **");
    lcd.set_Cursor(0, 1);
    lcd.printstr(" none ");

    radio_init_sender("00001");           // change mode sender
    delay(10);
    
    create_trame(&trameS, network, GAME_FLAGS_SELECT, time_game, END_COMMAND);
    radio_send(&trameS);                // send trame
    radio_send(&trameS);                // send trame

    t = millis();
    do
    {
        key_loop(&bt1, &bt2, &bt3);
        key_time_loop(&t_bt1, &t_bt2, &t_bt3);

          // PROUT PROUT

        
        lcd.backlight();    // set light ON (in loop, shit code..)
            
    } while (( millis() - t) < ( 600 * 1000));  // 10 mins verry bad write 
    lcd.clear();
}

void    game_flag_slave()
{
  
}
