#include"high_user.h"
#include"server.h"
#include"queue.h"
void antenna(int i)
{
  
   int j;
   ANT_CMD *c1;
   c1= malloc(sizeof(ANT_CMD));
   switch(i)
   {
     case C00:  printf("Command for C00 ANTENNA\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1); }
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); }
                 q_store(*c1);
                 break;
     case C01: printf("Command for C01 ANTENNA\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1); }
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); }
                 fprintf(stderr," Storing in Queue #####\n");
                 q1_store(*c1);
               break;
     case C02: printf("C02 ANTENNA\n");break;
     case C03: printf("C03 ANTENNA\n");break;
     case C04:printf("C04 Antenna \n");break;
     default : break;
   }
}

void userdef(int k)
{
   //int k;
    setdata *set;  
    set = (setdata *)malloc(sizeof(setdata)); 
   switch(k)
   {
     case create: {printf("CREATE USER\n"); exec(set,k);write_us_shm(set);} break;
     case add: printf(" ADD USER\n");break;
     case delete: printf("REMOVE USER\n");break;
     
     default : break;
   }
}

void dasdef(int r)
{
  // int r;
   switch(r)
   {
     case dasinit:printf("DAS INIT\n"); break;
     case addp: printf(" ADD Project\n");break;
     case delprj: printf("DElete Project\n");break;
     case startscan: printf("DAS START SCAN\n");break;
     case stopscan: printf("DAS STOP SCAN\n");break;
     default : break;
   }
}

void* highuser( void* parameters)
{
   //ret= 0;
   while((name=readline("\n >> "))!=NULL)
    {
      if (strcmp(name,"stop")==0)
      continue;
      printf("\n");
      if(name)
      {ret=1;}
       else
        { ret=0; }
      usleep(10000);
       if (name[0]!=0)
            add_history(name);
     }
   free(name);
   return NULL;
}
void* lowuser( void* parameters)
{
  char *del = " ";

  char *antn[]= {"C00","C01","C02","C03","C04"};
  char *user1[]={ "create","add","delete"};
  char *das[]={"dasinit","Addp","delprj","startscan","stopscan"};



  int i;

  for(;;)
  {
      if(ret){
      i = 0;
       ret=0;
    //  fprintf(stderr,"HIGH USER INPUT ===>%s\n",name);
      token=strtok(name,del);
       while(token !=NULL)
        { 
          strcpy(cmd1[i],token);
          fprintf(stderr," CMD[%d] => %s\n",i,cmd1[i]);
          i++; 
          no_element = i;
          //fprintf(stderr," Number of Element is %d\n",no_element);
          token =  strtok(NULL," ");
        } 
        for (i = 0; i < END; i++) 
        {
           if (!strcasecmp(cmd1[0], antn[i]))
            {
             //fprintf(stderr,"####### STRING is %s %d\n",cmd[0],i);
              antenna(i);
            }
         }
         for(i=0;i<UEND;i++)
         {
            if (!strcasecmp(cmd1[0], user1[i]))
            {
             //fprintf(stderr,"####### STRING is %s %d\n",cmd[0],i);
              userdef(i);
            }
          }
           for(i=0;i<DEND;i++)
         {
            if (!strcasecmp(cmd1[0], das[i]))
            {
             //fprintf(stderr,"####### STRING is %s %d\n",cmd[0],i);
              dasdef(i);
            }
          } 
        
       
      // ret =0;
      //usleep(500);
      }
      
   }
   return NULL;
}
