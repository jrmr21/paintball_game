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

  while (va_arg(arg, unsigned char*)[0] != END_COMMAND)
  {                                   // count number of arguments
    i++;
  }
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
}

void str_to_trame(trame_t* trame, unsigned char* str)
{
    int i = 3;
    int number_command = 0;
  
    trame->adress = str[0];
    trame->adress_to = str[1];
      
    trame->size_trame = str[2];
          
    while(str[i] != '\0')
    {
        trame->data[number_command][0] = str[i];
        i++;
        trame->data[number_command][1] = str[i]; 
        i++;
        trame->data[number_command][2] = str[i];
        i++;
        
        number_command++;
    }

    trame->data[number_command][0] = '\0';
    
    trame->number_command = number_command;     
}
