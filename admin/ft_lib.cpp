# include "ft_lib.h"
# include <stdlib.h>

char  *ft_strncpy(char *dest, char *src, unsigned int n)
{
  unsigned int i;

  i = 0;
  while (i < n && src[i] != '\0')
  {
    dest[i] = src[i];
    i++;
  }
  while (i < n)
  {
    dest[i] = '\0';
    i++;
  }
  return (dest);
}

int    ft_strlen(char *str)
{
  int out;

  out = 0;
  while (*str++)
    out++;
  return (out);
}

char  *ft_realloc(char *str, int siz)
{
  char  *tmp;
  int   i;

  i = ft_strlen(str);
  tmp = (char*)malloc(sizeof(char) * i);
  if (tmp != NULL)
  {
    ft_strncpy(tmp, str, i);
    free(str);
  }
  str = (char*)malloc(sizeof(char) * i + siz + 1);
  if (str != NULL)
  {
    ft_strncpy(str, tmp, i);
    free(tmp);
  }
  str[i + siz + 1] = '\0';
  return (str);
}

int    ft_atoi(char *str)
{
  int   i;
  char  out;
  int   sortie;

  i = 0;
  sortie = 0;
  out = 1;
  while (str[i] == '\n' || str[i] == '\r' || str[i] == '\v' ||
      str[i] == ' ' || str[i] == '\f' || str[i] == '\t')
    i++;
  if (str[i] == '-')
  {
    i++;
    out = -1;
  }
  else if (str[i] == '+')
    i++;
  while ((str[i] > 47) && (str[i] < 58))
  {
    sortie *= 10;
    sortie += (str[i] - 48);
    i++;
  }
  return (sortie * out);
}
