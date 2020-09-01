#include<stdio.h>
#include<string.h>

#define BASE 16
#define DIGITS 2

int main()
{
  int cmd = 44; char c;
  fprintf(stderr,"%c\n",(unsigned char)cmd);
  sprintf(c,"%x",(unsigned char)cmd);
  fprintf(stderr,"%d\n",(unsigned char)c);
}


