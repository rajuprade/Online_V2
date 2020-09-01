#include <stdio.h>
#include <setjmp.h>

void do_loop(int n) {
  int val;
  jmp_buf env;

  val = 0;

  setjmp(env);

  printf("Value of Val => %d\n", ++val);

  if (val != n)
    longjmp(env, 0);  
}

int main() {
  do_loop(10);
  return 0;
}
