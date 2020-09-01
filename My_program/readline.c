#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
 getwords(char *line, char *words[], int maxwords)
{
char *p = line;
int nwords = 0;

while(1)
	{
	while(isspace(*p))
		p++;

	if(*p == '\0')
		return nwords;

	words[nwords++] = p;

	while(!isspace(*p) && *p != '\0')
		p++;

	if(*p == '\0')
		return nwords;

	*p++ = '\0';

	if(nwords >= maxwords)
		return nwords;
	}
}
int main()
{
     char *buf,*token;
    int i,nwords;
    char *words[20];
    rl_bind_key('\t',rl_abort);//disable auto-complete
   
    /* char *del = " ";
     char line[50] ="Raj loves program";
     token=strtok(line,del);
     while(token !=NULL)
     { 
      fprintf(stderr," STRTOK retrun %d %s\n",strlen(line),token); 
      token =  strtok(NULL," ");
     } */

    while((buf = readline("\n >> "))!=NULL)
    {
           /* token=strtok(buf,del); // It works as per our expectation 
             while(token !=NULL)
             { 
               fprintf(stderr," STRTOK retrun %d %s\n",strlen(line),token); 
               token =  strtok(NULL," ");
             } */                  
        if (strcmp(buf,"stop")==0)
            break;
         else
         {
            // if(strcmp(buf,"start")==0)
             printf("[%s]\n",buf);
             nwords = getwords(buf,words,20);
             for(i = 0; i < nwords; i++)
            printf("%s\n", words[i]);  
                    
         }
 
        if (buf[0]!=0)
            add_history(buf);
    }
 
    free(buf);
 
    return 0;
}
