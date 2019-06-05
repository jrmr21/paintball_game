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
	
	trame_t trame_send;
	trame_t trame_receive;
	
	lcd.clear();
    
    lcd.set_Cursor(0,0);
    lcd.print(" *** SLAVE ***");

  trame_t t;
	//str_to_trame(t, "013J11F22U33\0");
  const char *tmp = "013J11F22U33\0";
  //const char *tmp = "111111111111\0";
  //str_to_trame(&t, tmp);
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
