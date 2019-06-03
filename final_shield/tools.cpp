#include "core_header.h"

// On encode un int (en base 10) en un nombre en base 255
// On stocke ce nombre dans un tableau de char pour le dans une trame
unsigned char* compress_char(unsigned int a)
{
  unsigned char res[2];
  float f;

  // Calcul de res[0]
    f = a / 255;
    // Arrondissement a l'inferieur du float
  f = ((int)f > f) ? (int) f - 1 : (int) f;

  res[0] = (int)f;
  res[1] = a % 255;

    return res;
}

// On decode deux char (en base 255) en un int (en base 10)
unsigned int decompress_char(unsigned char a[2])
{
    unsigned int res;

    res = a[0] * 255;
    res += a[1];

    printf("res = %d", res);
    return res;
}

int  create_trame(trame_t *t, unsigned char network[4], ...)    // work in progress...
{
  int8_t             i;
  unsigned char      *data;
  va_list            arg;                 // create list arg
  va_start(arg, network);            // init start pointer arg_list to *p pointer 
  t->adress     = network[0];
  t->adress_to  = network[1];
  i             = 0;
  data          = "  \0";
  
  while (va_arg(arg, unsigned char*)[0] != END_COMMAND)                                  // count number of arguments
    i++;

  if (i > 10)
    return (1);   // bugs
    
  va_end(arg);
  
  t->number_command = i;
  t->size_trame     = 3 + (t->number_command * 3);
  va_start(arg, network);
  for( i = 0; i < t->number_command; i++)
  {    
      strcpy(t->data[i], va_arg(arg, unsigned char*));
      if (t->data[i][3] != '\0')  t->data[i][3] = '\0';       // check '\0' is present or not
  }
  va_end(arg);
  return (0);       // no bugs
}

void  debug_trame(trame_t *trame)
{
      Serial.print("adress ");
      Serial.println(trame->adress);
      Serial.print("adress_to ");
      Serial.println(trame->adress_to);
      Serial.print("number_command ");
      Serial.println(trame->number_command);
      Serial.print("size trame ");
      Serial.println(trame->size_trame);

      Serial.println("***********************************************************");
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
}

void  print_str(unsigned char* str)
{
  for (int i = 0; i < strlen(str); i++)
    Serial.print((char)str[i]);
}

int  trame_to_str(trame_t *t, unsigned char* str)    // work in PROGESS !!!!
{         
  str[0]  = t->adress;
  str[1]  = t->adress_to;                     // protocol
  str[2]  = t->size_trame;

  for (int8_t i = 0; (i < t->number_command) ; ++i)
  {
    str[(i*3)]      = t->data[i][0];
    str[(i*3) + 1]  = t->data[i][1];
    str[(i*3) + 2]  = t->data[i][2];
  }
  
  str[(3 + (t->number_command * 3)) + 1] = '\0';
  return (0);
}
