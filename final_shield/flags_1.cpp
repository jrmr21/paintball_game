#include "core_header.h"

extern unsigned char terminal_adress;

void  game_flag_slave(int game_time)
{
	int res[3];
	
	// On fait la partie
    res = game_flag(int game_time);
	
	// On envoie les résultats
}

void  game_flag_master(void)
{
  
}

// Tronc commun pour la partie jeu (partagé par les slaves et le master)
int[] game_flag(int game_time)
{
    int       time = 0;
	
	int       time_r = 0, time_g = 0, time_b = 0;
	int8_t         r = 0,      g = 0,      b = 0;
	
	uint32_t  mili = millis();
	int8_t    bt1, bt2, bt3;
	
	int res[3];
	
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
	
	return res;
}	
