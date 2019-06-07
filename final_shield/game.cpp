#include "core_header.h"


extern unsigned char terminal_adress;

void   game_master(void)
{
    trame_t   trame;
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
    terminal_adress = 255;
          
    lcd.clear();
    
    lcd.set_Cursor(0,0);
    lcd.print(" *** MASTER ***");

    radio_init_receive("00001");
    while (i)
    {
        key_loop(&bt1, &bt2, &bt3);
        //radio_receive(tempo);

  
        if (bt3) 
        {
          i = 0;
        }
        lcd.backlight();    // set light ON (in loop, shit code..)  
    }
    lcd.clear();
}

void    game_slave(void)
{
	  int i = 1; // variable de fin de connexion
	  uint32_t  mili = millis();
    uint8_t  bt1, bt2, bt3;
	
	  trame_t trame_send;
	  trame_t trame_receive;
	
	  // Affichage de l'écran
	  lcd.clear();
    lcd.set_Cursor(0,0);
    lcd.print(" *** SLAVE ***");
    
    trame_t trame_send;
    trame_t trame_receive;

    trame.adress = terminal_adress;

    char network[4] = {terminal_adress, ADRESS_MASTER, 6,'\0'};
    create_trame(&trame_send, network, JOIN_REQUEST, END_COMMAND);
    
	  while(i)
  	{   
  	    // Test du bouton de retour arrière
        key_loop(&bt1, &bt2, &bt3);		
        if (bt3) 
            i = 0;

        if ((millis() - mili) > 500)
		    {
            radio_init_sender();
            radio_send(&trame_send);
		    }

        radio_init_receive();
        radio_receive(&trame_receive);
        if (trame_receive.adress == ADRESS_MASTER)
        {
          //if (trame_receive.data)
        }


        
    }   
}
