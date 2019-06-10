#include  "core_header.h"

void    key_loop(int8_t *bt1, int8_t *bt2, int8_t *bt3)
{
    static int8_t btn_1 = 0;   // click is DOWN
    static int8_t btn_2 = 0;
    static int8_t btn_3 = 0;

    *bt1 = 0;   // set default return is all button are false
    *bt2 = 0;
    *bt3 = 0;   
    
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

<<<<<<< HEAD

void    key_time_loop(int *bt1, int *bt2, int *bt3)
{
    static uint8_t btn_1 = 0;   // click is DOWN
    static uint8_t btn_2 = 0;
    static uint8_t btn_3 = 0;

    static uint32_t t1  = 0;
    static uint32_t t2  = 0;
    static uint32_t t3  = 0;

    *bt1 = 0;   // set default return is all button are false
    *bt2 = 0;
    *bt3 = 0;

    
    if (btn_1 && (digitalRead(btn1))) 
    {
        *bt1  = ((int)((millis() - t1)) / 1000);
    }
    else if (digitalRead(btn1) && (!btn_1))
=======
void    key_time_loop(int *bt1, int *bt2, int *bt3)
{
    static int8_t btn_1 = 0;   // click is DOWN
    static int8_t btn_2 = 0;
    static int8_t btn_3 = 0;

    static int32_t  t1  = 0;
    static int32_t  t2  = 0;
    static int32_t  t3  = 0;

    *bt1 = 0;   // set default return is all button are false
    *bt2 = 0;
    *bt3 = 0;   
    
    if (digitalRead(btn1) && (!btn_1))
>>>>>>> 790c1263d8e43cee77ec800320ac0bf8cb3f64d2
    {
      btn_1 = 1;
      t1    = millis();
    }
<<<<<<< HEAD
    else
      btn_1 = 0;   // reset, click is UP

    
    
    if (btn_2 && (digitalRead(btn2))) 
    {
        *bt2  = ((int)((millis() - t2)) / 1000);
    }
    else if (digitalRead(btn2) && (!btn_2))
    {
      btn_2 = 1;
      t2    = millis();
    }
    else
      btn_2 = 0;   // reset, click is UP


    
    if ((btn_3 == 1) && (digitalRead(btn3))) 
    {
        *bt3  = ((int)((millis() - t3)) / 1000);
        //Serial.println((int)((millis() - t3)) / 1000);
    }
    else if (digitalRead(btn3) && btn_3 == 0)
=======
    else if ((btn_1) && digitalRead(btn1)) 
    {
        *bt1 = (((uint32_t)(millis() - t1) / 1000) < 63000 )? ((millis() - t1) / 1000) : 63000;
    }
    else
        btn_1 = 0;   // reset, click is UP

    if (digitalRead(btn2) && (!btn_2))
    {
      btn_2 = 1;
      t1    = millis();
    }
    else if ((btn_2) && digitalRead(btn2)) 
    {
        *bt2 = (((uint32_t)(millis() - t2) / 1000) < 63000 )? ((millis() - t2) / 1000) : 63000;
    }
    else
        btn_2 = 0;   // reset, click is UP

    if (digitalRead(btn3) && (!btn_3))
>>>>>>> 790c1263d8e43cee77ec800320ac0bf8cb3f64d2
    {
      btn_3 = 1;
      t3    = millis();
    }
<<<<<<< HEAD
    else
      btn_3 = 0;   // reset, click is UP
=======
    else if ((btn_3) && digitalRead(btn3)) 
    {
        *bt3 = (((uint32_t)(millis() - t3) / 1000) < 63000 )? ((millis() - t3) / 1000) : 63000;
    }
    else
        btn_3 = 0;   // reset, click is UP
    
>>>>>>> 790c1263d8e43cee77ec800320ac0bf8cb3f64d2
}
