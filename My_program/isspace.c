#include <stddef.h>
#include <ctype.h>
#include<stdio.h>
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
 // char line[] = "this is a test";
   char line[20];
  int i,nwords;
  char *words[20];
  fgets(line,20,stdin);
  nwords = getwords(line, words,20);
  for(i = 0; i < nwords; i++)
  printf("%s\n", words[i]);
  return 0;
}
