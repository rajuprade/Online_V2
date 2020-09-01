#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int main()
{
      char *del = " ",*token, *buf;
      buf = malloc(100);
      char line[50],command[5][10];
      char cmd[10][10];
      int i=0,j=0;
      fprintf(stderr," Enter the command\n");
      fgets(buf,100,stdin);
      fprintf(stderr," ######### %s Entered command\n",buf);
      token=strtok(buf,del);
       while(token !=NULL)
        { 
          strcpy(cmd[i],token);
          fprintf(stderr," CMD[%d] => %s\n",i,cmd[i]);
          i++; 
          token =  strtok(NULL," ");
        } 
return 0;
}
