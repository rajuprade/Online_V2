#include<stdio.h>

int main()
{
  char str[128];
  int n,i;
  FILE *f;
  int user_number,sub_num,no_of_antenna;
  char ant1[10],ant2[10],ant3[10],ant4[10];
  char ant_name[10][10];
  if((f = fopen("/home/teleset/Online_v2/teleset/input1.txt","rt")) == NULL) return;

   while(fgets(str,128,f))
  {
    if(*str =='#')continue;
     // sscanf(str,"%d %d %d",&user_number,&sub_num,&no_of_antenna);
      sscanf(str,"%d %d %d %s %s %s %s",&user_number,&sub_num,&no_of_antenna,ant1,ant2,ant3,ant4);
     fprintf(stderr," USER NUMBER -> %d\n",user_number);
     fprintf(stderr," SUB ARRAY NUMBER -> %d\n",sub_num);
     fprintf(stderr," NUMBER of Antenna -> %d\n",no_of_antenna);
     fprintf(stderr," Antenna -> %s %s %s %s\n",ant1,ant2,ant3,ant4); 
  }
    
 return 0;
}
