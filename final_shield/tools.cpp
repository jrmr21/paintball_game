#include "core_header.h"

void create_command(unsigned char data, unsigned int a, unsigned char p[4])
{
  p[0]  = data;
  
  compress_char(a, p+1);
  p[3]  = '\0';
  
}

// On encode un int (en base 10) en un nombre en base 255
// On stocke ce nombre dans un tableau de char pour le dans une trame
void compress_char(unsigned int a, unsigned char data[2])
{
  float f;

  // Calcul de res[0]
    f = a / 255;
    // Arrondissement a l'inferieur du float
  f = ((int)f > f) ? (int) f - 1 : (int) f;

  data[0] = (int)f;
  data[1] = a % 255;

}

// On decode deux char (en base 255) en un int (en base 10)
unsigned int decompress_char(unsigned char a[2])
{
    unsigned int res;

    res = a[0] * 255;
    res += a[1];

    return res;
}

int  create_trame(trame_t *t, unsigned char network[4], ...)    // work in progress...
{
  int8_t             i;
  va_list            arg;                 // create list arg
  char*              tmp_data;
  
  va_start(arg, network);            // init start pointer arg_list to *p pointer
   
  t->adress     = network[0];
  t->adress_to  = network[1];
  i             = 0;
  
  while (va_arg(arg, unsigned char*)[0] != END_COMMAND)                                  // count number of arguments
    i++;

  if (i > 10)
    return (1);   // bugs
    
  va_end(arg);
  
  t->number_command = i;
  t->size_trame     = 4 + (t->number_command * 3);
  t->secure         = 1;
  
  va_start(arg, network);
  for( i = 0; i < t->number_command; i++)
  {    
      //strncpy(t->data[i], va_arg(arg, unsigned char*), 4);
      
      tmp_data = va_arg(arg, unsigned char*);
      
      t->data[i][0] = tmp_data[0];
      t->data[i][1] = tmp_data[1];      // FUCK YOU STRCPY AND STRNCPY, YOU CAN'T WRITE unsigned char with 0 decimal value 
      t->data[i][2] = tmp_data[2];              // FUUUUUUCKK !!!!!!!!!!!
      t->data[i][3] = '\0';       // check '\0' is present or not
      
      //Serial.println(decompress_char(t->data[i][2]));
  }
  va_end(arg);
  return (0);       // no bugs
}

void str_to_trame(trame_t* trame, unsigned char* str)
{
    int i = 4;
    int number_command = 0;

    trame->adress     = str[0];
    trame->adress_to  = str[1];
    trame->size_trame = str[2];
    trame->secure     = str[3];
    
    while(str[i] != '\0')
    {
        trame->data[number_command][0] = str[i];
        i++;
        trame->data[number_command][1] = str[i]; 
        i++;
        trame->data[number_command][2] = str[i];
        i++;
        trame->data[number_command][3] = '\0';

        number_command++;
    }

    trame->data[number_command][0]  = '\0';
    trame->number_command           = number_command;   
}

void            debug_trame(trame_t *trame)
{
      Serial.println("************************** TRAME ****************************");
      Serial.print("adress ");
      Serial.println(trame->adress);
      Serial.print("adress_to ");
      Serial.println(trame->adress_to);
      Serial.print("number_command ");
      Serial.println(trame->number_command);
      Serial.print("size trame ");
      Serial.println(trame->size_trame);
      Serial.print("secure: ");
      Serial.println(trame->secure);

      for (int i = 0; i < trame->number_command; i++)
      {
        Serial.print((char)trame->data[i][0]);
        Serial.print((char)trame->data[i][1]);
        Serial.print((char)trame->data[i][2]);
        Serial.println("");
      }
      
      Serial.println("adress: ");
      Serial.println((long) &trame->data, DEC);
      Serial.println("***********************************************************");
      Serial.println(" ");
}

void  print_str(unsigned char* str)
{
    for (int i = 0; (i < strlen(str)) || (str[i] != '\0'); i++)
      Serial.print((char)str[i]);
    Serial.println(" ");
}

int  trame_to_str(trame_t *t, unsigned char str[50])
{     
  str[0]  = t->adress;  
  str[1]  = t->adress_to;                     // protocol
  str[2]  = t->size_trame;
  str[3]  = t->secure;

  for (int8_t i = 1; (i < t->number_command + 1) ; i++)
  {
    str[(i * 3) + 1]  = t->data[i - 1][0];
    str[(i * 3) + 2]  = t->data[i - 1][1];
    str[(i * 3) + 3]  = t->data[i - 1][2];
  }
  
  str[(4 + (t->number_command * 3)) + 1] = '\0';
  return (0);  
}
