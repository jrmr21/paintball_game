#include  "core_header.h"

void    key_loop(int8_t *bt1, int8_t *bt2, int8_t *bt3)
{
    static int8_t btn_1 = 0;   // click is DOWN
    static int8_t btn_2 = 0;
    static int8_t btn_3 = 0;

    *bt1 = 0;   // set default return is all button are false
    *bt2 = 0;
    *bt3 = 0;   
    
    /*
      Serial.print("btn1: "); Serial.print(digitalRead(btn1));
      Serial.print(" btn2: "); Serial.print(digitalRead(btn2));
      Serial.print(" btn3: "); Serial.println(digitalRead(btn3));  
    */
    
    if (digitalRead(btn1))  btn_1 = 1;
    else if (btn_1) 
    {
        *bt1 = 1;
        btn_1 = 0;   // reset, click is UP
    }
    
    if (digitalRead(btn2))  btn_2 = 1;
    else if (btn_2) 
    {
        *bt2 = 1;
        btn_2 = 0;   // reset, click is UP
    }

    if (digitalRead(btn3))  btn_3 = 1;
    else if (btn_3) 
    {
        *bt3 = 1;
        btn_3 = 0;   // reset, click is UP
    }
}
