#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main ()
{
  char * pPath;
  char p[200];
  pPath = (char *)getenv ("PATH");
  strcpy(p,pPath);
  if (pPath!=NULL)
    printf ("The current path is: %s",p);
  return 0;
}
