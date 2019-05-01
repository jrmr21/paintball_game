#include    "core_header.h"

void  setup() 
{
  int8_t  y       = 0;    // mouse pos
  int8_t  pos     = 1;    // option select  (0 to 4)
  int8_t  frame   = 1;    // frame lvl      (0 to 2)
  int8_t  bt1;            
  int8_t  bt2;            // bt select (0 or 1)
  int8_t  bt3;
  
  init_pin();
  init_lcd();
  lcd.clear();

  frame1(&frame);                  // default frame
  lcd.set_Cursor(posX_arrow, y);
  lcd.printstr(arrow);
  
  while (1)
  {
    key_loop(&bt1, &bt2, &bt3);
 
    if (bt1)     // move arrow down
    {     
        if (pos > MIN_frame)
        {
            pos--;
            if ((pos <= 2) && (frame != 1)) 
              frame1(&frame);
        } 
        update_mouse(pos, &y);
    }
    else if (bt2)     // move arrow up
    {
      if (pos < MAX_frame)
      {
        pos++;  
        if ((pos >= 3) && (frame != 2))
          frame2(&frame);
      }
      update_mouse(pos, &y);
    }
    else if (bt3)       // validation button
    {
                       //  call option selected
      switch(pos)
      {
        case 2 :  opt_demo();
                  frame1(&frame);   // replay the last frame
                  break;
        default : break;
      }
      lcd.set_Cursor(posX_arrow, y);
      lcd.printstr(arrow); 
    }
    
    lcd.backlight();    // set light ON (in loop, shit code..)  
  }
}

void  update_mouse(int8_t select, int8_t *y)
{
    lcd.set_Cursor(posX_arrow, *y);  // clear
    lcd.printstr(clear_arrow);
    
    *y = select % 2;    // to move the mouse with genius power
                        // you can move your selection at 1 to 4 and we hav 2 line to display the mouse
                        // so if you a %2 you are display at 0 posY else at 1posY
                        //  I LIKE THAT
                        
    lcd.set_Cursor(posX_arrow, *y);
    lcd.printstr(arrow);  
}
