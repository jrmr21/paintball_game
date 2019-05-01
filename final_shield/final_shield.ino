#include    "core_header.h"

void  setup() 
{
  int8_t  pos     = 2;    // option select
  int8_t  frame   = 1;    // frame lvl
  
  init_pin();
  init_lcd();
  lcd.clear();
        
  int8_t bt1, bt2, bt3;

  frame1(&frame);                      // default frame
  lcd.set_Cursor(posX_arrow, 0);
  lcd.printstr(arrow);
  
  while (1)
  {
    key_loop(&bt1, &bt2, &bt3);       // GO TO THE DOC 
 
    if (bt1)
    {     
        if (pos > MIN_frame)
        {
            pos--;
            
            if ((pos <= 2) && (frame != 1)) 
              frame1(&frame);
        } 
        update_mouse(pos);
    }
    else if (bt2)
    {
      if (pos < MAX_frame)
      {
        pos++;  
        
        if ((pos >= 3) && (frame != 2))
          frame2(&frame);
      }
      
      update_mouse(pos);
    }
    else if (bt3)
    {
                            //     call option selected
      switch(pos)
      { 
        case 1 :  radio_recerve();         //  "-recerve data"; 
                  frame1(&frame);         //  replay the last frame
                  break;
        case 2 :  radio_sender();         //  "-send data";  
                  frame1(&frame);
                  break;      
                    
        case 3 :  opt_demo();             //  "-game"; 
                  frame2(&frame);
                  break;
        case 4 :  opt_demo();             // "-snd, rcv";  
                  frame2(&frame);
                  break;
                  
        default : break;
      }

      Serial.println(pos);
      update_mouse(pos);
    }
    lcd.backlight();    // set light ON (in loop, shit code..)  
  }
}

void  update_mouse(int8_t select)
{
    lcd.set_Cursor(posX_arrow, ((select-1) % 2));   // clear
    lcd.printstr(clear_arrow);                      //  ((select-1) % 2) WHAT IS SHIT ??!!!
                                                    // GO TO THE DOC 
    lcd.set_Cursor(posX_arrow, (select % 2));
    lcd.printstr(arrow);  
}
