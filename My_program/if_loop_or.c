#include <stdio.h>


void do_loop(int n) {
  int val;
  

  val = 0;

 

  printf("Value of Val => %d\n", ++val);

  if ((val != n) || (val > 20) )
  fprintf(stderr,"$$$$$$$$$$$$$$\n");
    
}

int main() {
  do_loop(10);
  return 0;
}
