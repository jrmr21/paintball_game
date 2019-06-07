/*

OPTION MENU SELECT :      /!\ POTENTIAL FAIL WITH SPAM SELECTION /!\ 
===================


    "- send data";             //  2
    "- receive data";         //  1
    "- snd, rcv";              //  4
    "- game";                  //  3
    "- led";                   //  6
    "- adress";                //  5



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

trame:

  | unsigned char adress | unsigned char adress  |  unsigned char size  |   data...   |
   __________________________________________________________________________________

   (  who i am  | who i send  | size trame (without end '\0') | data... | )
   

adress : 5 to 253 (other are reserved)
data   : 
          | command |  unsigned char data |  unsigned char data|
           _____________________________________________________


DEMO COMPRESS CHAR AND READ :
============================

    unsigned char pt[4];
    create_command(SCORE, 2050, pt);
    Serial.println(decompress_char(pt + 1));


*/

 //          WARNING NUCLEAR BOMB !!!!!!!!!
/*int  create_trame(trame_t *t, unsigned char network[4], ...)    // work in progress...
{
  int8_t             i;
  unsigned char      *data;
  va_list            arg;                 // create list arg

  va_start(arg, network);            // init start pointer arg_list to *p pointer 
  t->adress     = network[0];
  t->adress_to  = network[1];
  i             = 0;

  while (va_arg(arg, unsigned char*)[0] != END_COMMAND)
  {                                   // count number of arguments
    i++;
  }
  va_end(arg);
  
  Serial.println("step 1");
  
  t->size_trame     = 3 + (i * 3);

  if (t->data == NULL)
  {
    if (t->data = (unsigned char**) calloc(i, sizeof(t->data)));      // malloc numbers of line in tab;
  }
  else if (t->number_command != i)
  {
    t->number_command = i;
    if (t->data = (unsigned char**) realloc(i, sizeof(t->data)));
  }

  Serial.println("step 2");
  
  va_start(arg, network);
     
  for( i = 0; i < t->number_command; i++)
  {    
    if (t->data[i] == NULL)
    {
      if (t->data[i] = (unsigned char*) calloc(4, sizeof(t->data[i])));    // malloc columns of line (4 cases per lines)
    }
    else
    {
      if (t->data[i] = (unsigned char*) realloc(4, sizeof(t->data[i])));
    }
    
    strcpy(t->data[i], va_arg(arg, unsigned char*));  
    if (t->data[i][3] != '\0')  t->data[i][3] = '\0';       // check '\0' is present or not
  }
  va_end(arg);
}*/
