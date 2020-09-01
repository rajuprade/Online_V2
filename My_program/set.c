#include<stdio.h>

int main(void)
{
  char buf[56];
   
  setbuf(stdin,buf);
  printf("Hello,World!\n");
  
  printf("%s\n",buf);
  return 0;
}
