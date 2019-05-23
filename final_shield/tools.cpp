#include "core_header.h"

char*   compress_char(int a)
{
    
  
}

int   decompress_char(char a[2])
{
  
  
}

void  config_trame(trame_t *t, char* buf)
{

  
}

void  create_trame(trame_t *t, char* buf)
{
  buf     = malloc(sizeof(char*) * (3 + (t->number_command * 3)) + 1);

  buf[0]  = t->adress;
  buf[1]  = t->adress_to;                     // protocol
  buf[2]  = 3 + (t->number_command * 3);

  for (int8_t i = 0; (i < t->number_command) ; i += 1)
  {
    buf[ (i + 1) * 3]      = t->data[i][0];     // [((i+1) * 3) + 1] it's start wirte to 3 case and move +3 every loop
    buf[((i + 1) * 3) + 1] = t->data[i][1];     // t->data[i][0]; "i" is line of command 
    buf[((i + 1) * 3) + 2] = t->data[i][2];
  }

  buf[(3 + (t->number_command * 3)) + 1] = '\0';
}

int  read_trame(trame_s *t, char* buf)
{
  
}
