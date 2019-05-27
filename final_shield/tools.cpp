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


void  create_trame(trame_t *t, unsigned char network[4], ...)    // work in progress...
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

  if (t->data = (unsigned char**) malloc(i*(sizeof(unsigned char*))))   // malloc numbers of line in tab;
  {
        // realloc zone
        free(t->data);
        t->data = (unsigned char**)realloc(t->data, i*(sizeof(unsigned char*)));
  }

  va_start(arg, network);
  //Serial.print("list: ");
  //Serial.println((int)t->number_command);
     
  for( i = 0; i < t->number_command; i++)
  {    
     if (t->data[i] = (unsigned char*) malloc(4*(sizeof(unsigned char))))  // malloc columns of line (4 cases per lines)
     {
          // realloc zone
          free(t->data[i]);
          t->data[i] = (unsigned char*)realloc(t->data, (4*(sizeof(unsigned char))));
     }
      t->data[i] = va_arg(arg, unsigned char*);
      
      if (t->data[i][3] != '\0')  t->data[i][3] = '\0';       // check '\0' is present or not
  }
  
  va_end(arg);
}

void  trame_to_str(trame_t *t, unsigned char* str)    // work in PROGESS !!!!
{
            /*Serial.println(" ");
            for (int b = 0; b < 3; b++)
              Serial.print((char)t->data[1][b]);

            Serial.print(" size trame: ");
            Serial.println(t->size_trame);
            Serial.print(" command send: ");*/
            
  
  if (str = (unsigned char*)malloc(sizeof(unsigned char*) * (3 + (t->number_command * 3)) + 1))
  {
    free(str);
    str = (unsigned char*)realloc(str, (sizeof(unsigned char*) * (3 + (t->number_command * 3)) + 1));
  }

  str[0]  = t->adress;
  str[1]  = t->adress_to;                     // protocol
  str[2]  = t->size_trame;

  for (int8_t i = 0; (i < t->number_command) ; i += 1)
  {
    /*str[ (i + 1) * 3]      = t->data[i][0];     // [((i+1) * 3) + 1] it's start wirte to 3 case and move +3 every loop
    str[((i + 1) * 3) + 1] = t->data[i][1];     // t->data[i][0]; "i" is line of command 
    str[((i + 1) * 3) + 2] = t->data[i][2];*/

    // strncpy HERE !!!!!
  }

  str[(3 + (t->number_command * 3)) + 1] = '\0';
  
  Serial.println(" --send: ");
  for (int b = 0; b < str[2]; b++)
              Serial.print((char)str[b]);
  Serial.println(" --end send");
  
}

int  read_trame(trame_s *t, unsigned char* buf)
{
  
}
