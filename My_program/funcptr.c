/* Function Pointer example */
#include<stdio.h>

void sayhello();
void sayhello()
{
  fprintf(stderr,"Hello Raj..How is Sheetal Gaharwar\n");
}

int main()
{
  sayhello();
 
  void (*fptr)();
 
  fptr = sayhello;

  (*fptr)();
  return 0;
}
