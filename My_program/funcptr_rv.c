/* A Function Pointer with Parameters and Return Value */

#include <stdio.h>
 

int subtract(int x, int y);
 

int subtract(int x, int y) {
  return x - y;
}
 

int main() {
  int (*subtractPtr)(int, int) = subtract;
 
  int y = (*subtractPtr)(10, 2);
  printf("Subtract gives: %d\n", y);
 
  int z = subtractPtr(10, 2);
  printf("Subtract gives: %d\n", z);
}

