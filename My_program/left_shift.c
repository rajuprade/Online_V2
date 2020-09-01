#include<stdio.h>

int main()
{
  int x = 3; // 0 0 1 1 
  int y ,n;

  y = x << 2; // left shift by two digit => Result of this operation should come as 12 
  
  n = x >> 2; // right shift by two digit => result of this operation should come as 0

  fprintf(stderr," Value of Y is ### %d\n",y);

  fprintf(stderr," Value of N is ### %d\n",n);
  
return 0;

}
