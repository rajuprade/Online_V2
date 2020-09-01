#include<stdio.h>

int main()
{
  char buf[10];
  sprintf(buf,"%s","Raj");
  fprintf(stderr,"Name is ## %s\n",buf);
  return 0;
}
