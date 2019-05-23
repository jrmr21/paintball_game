/*

OPTION MENU SELECT :      /!\ POTENTIAL FAIL WITH SPAM SELECTION /!\ 
===================


    "-send data";             //  2
    "-receirve data";         //  1
    "-snd, rcv";              //  4
    "-game";                  //  3
    "- led";                  //  6
    "- adress";               //  5



((select-1) % 2) WHAT IS SHIT ??!!!
====================================


    basic command:
  lcd.set_Cursor(posX_arrow, ((select-1) % 2));  


(select-1) = is last selection (that is "-1") and you take "modulo" of your selection 
             for example you are 3 your Y is 1 position
             but you are 4 your Y is 0 position


FRAME AND ITEM SCHEMATIC :
=========================

  frame 1
    ----------
    |
    | item 2
    | item 1
    ----------
   frame 2
    ----------
    |
    | item 4
    | item 3
    ----------
  frame 3
    ----------
    |
    | item 6
    | item 5
    ----------


DEFAULT ITEM :
==============

void  game(void)
{
      int8_t i;
      int8_t bt1, bt2, bt3;
      uint32_t  mili; 
      
      i     = 1;
      mili  = millis();
      lcd.clear();
      lcd.print(" it's a demo ");
      
      while (i)
      {
          key_loop(&bt1, &bt2, &bt3);

          //  if ((millis() - mili) > 1500)    // evry 1s
          //  {
          //    mili  = millis();               // example to use millis function
          //  }

          if (bt3)  i = 0;
          lcd.backlight();    // set light ON (in loop, shit code..)  
      }
      lcd.clear();
}

NETWORK DATA :
==============


  | unsigned char adress | 10 unsigned char data |
   ______________________________________________

adress : 0 to 254 (255 is reserved)
data   : 1 to 255 (0 is empty data)

 */
