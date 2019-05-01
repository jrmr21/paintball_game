/*

OPTION MENU SELECT :      /!\ POTENTIAL FAIL WITH SPAM SELECTION /!\ 
===================


    "-send data";             //  2
    "-recerve data";          //  1
    "-snd, rcv";              //  4
    "-game";                  //  3



((select-1) % 2) WHAT IS SHIT ??!!!
====================================


    basic command:
  lcd.set_Cursor(posX_arrow, ((select-1) % 2));  


(select-1) = is last selection (that is "-1") and you take "modulo" of your selection 
             for example you are 3 your Y is 1 position
             but you are 4 your Y is 0 position


 */
