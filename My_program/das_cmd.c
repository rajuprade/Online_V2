#include<stdio.h>
#include<string.h>
int main()
{
  int sub_number,seq,cmode;
  char sys[4];
  char cmd[10];
  char antmask[10];
  char fname[25];
  char stext[250];
  bzero(stext,250);
  sub_number = 0;
  seq=1;
  cmode=8;
  strcpy(sys,"das");
  strcpy(cmd,"init");
  
  strcpy(antmask,"7EEEEEEE");

  strcpy(fname,"/home/teleset.gsb.hdr");
  
 
 
  sprintf(stext,"%d %d %s %s %d %s %s",sub_number,seq,sys,cmd,cmode,antmask,fname);

  fprintf(stderr,"=> %s\n",stext);
  return 0;
}
