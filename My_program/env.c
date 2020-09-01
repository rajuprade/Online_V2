#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ABC_ADDR 5
int main()
{
  char *envptr;
  int abcaddr;
  
   if((envptr = (char *) getenv("ABC_ADDR")) != NULL )
    {
     // strcpy(abcaddr,envptr);
        abcaddr= atoi(envptr);
    }
    else 
    {
      
     //  strcpy(abcaddr,ABC_ADDR);
         abcaddr= ABC_ADDR;
    }
   
    printf(" ABC ADDRESS is %d\n", abcaddr);
    return 0;
}
   
