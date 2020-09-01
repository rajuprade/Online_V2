#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#define MAX_LOOP 2
#define MAX_ANT 4

pthread_mutex_t lock; 
typedef struct 
{
  int seq;
  char timestamp[64];
  char system_name[16];
  char op_name[16];
  short int number_param;
  char parameter_name[32][16];
  char Argument_Ch1[32][16];
  char Argument_Ch2[32][16];
 } Cmd;

typedef struct
{
  char antenna_name[30][6];
  Cmd  CMD[10];
} ANT_CMD;

typedef struct
{
   int sub_num;
   int num_in_sub;
   char ant_name[32][8];
 }sub;

typedef struct
{
   int usernb;
   sub s_a[4];
   char timestamp[26];
} user;

typedef struct
{
   user Tx[4];

} setdata;


static char at_name[32][8] = {"C00","C01","C02","C03","C04","C05","C06","C08","C10","C11","C12","C13","C14","E02"
           ,"E03","E04","E05","E06","S01","S02","S03","S04","S06","W01","W02","W03","W04","W05","W06"}; 

typedef enum { C00,C01,C02,C03,C04,C05,C06,C08,C10,C11,C12,C13,C14,E02,E03,E04,E05,E06,S01,S02,S03,S04,
                S06,W01,W02,W03,W04,W05,W06,END } ant_name;

char *us[]={ "create","add","cmd2sub","delete","showuser"};
typedef enum { create,add,cmd2sub,delete,showuser,UEND} udef;

char *das[]={"dasinit","Addp","delprj","startscan","stopscan"};

typedef enum {dasinit,addp,delprj,startscan,stopscan,DEND} dastype;
int ret=0,no_element;
char *name;
char *token;
char *del = " ";
char cmd[10][10];

 
void antenna(int i);

void userdef(int k, setdata *set);
void dasdef( int r);

void antenna(int i)
{
   int j;
   switch(i)
   {
     case C00: printf("C00 ANTENNA\n");break;
     case C01: printf("C01 ANTENNA\n");break;
     case C02: printf("C02 ANTENNA\n");break;
     case C03: printf("C03 ANTENNA\n");break;
     case C04: printf("C04 Antenna \n");break;
     case C05: printf("C05 ANTENNA\n");break;
     case C06: printf("C06 Antenna \n");break;
     case C08: printf("C08 ANTENNA\n");break;
     case C10: printf("C10 ANTENNA\n");break;
     case C11: printf("C11ANTENNA\n");break;
     case C12: printf("C12 ANTENNA\n");break;
     case C13: printf("C13 Antenna \n");break;
     case C14: printf("C14 ANTENNA\n");break;
     case E02: printf("E02 Antenna \n");break;
     case E03: printf("E03 Antenna \n");break;
     case E04: printf("E04 Antenna \n");break;
     case E05: printf("E05 Antenna \n");break;
     case E06: printf("E06 Antenna \n");break;
     case S01: printf("S01 Antenna \n");break;
     case S02: printf("S02 Antenna \n");break;
     case S03: printf("S03 Antenna \n");break;
     case S04: printf("S04 Antenna \n");break;
     case S06: printf("S06 Antenna \n");break;
     case W01: printf("W01 Antenna \n");break;
     case W02: printf("W02 Antenna \n");break;
     case W03: printf("W03 Antenna \n");break;
     case W04: printf("W04 Antenna \n");break;
     case W05: printf("W05 Antenna \n");break;
     case W06: printf("W06 Antenna \n");break;
     default : break;
   }
}

void userdef(int p, setdata *set)
{
   //int k;
    int i=0,j,k,m,n,a,b,flag=0,op,un=0,sn=0;
   char cmmd[10][10];
 /*   setdata *set;  
   set = (setdata *)malloc(sizeof(setdata)); */
   time_t *t1;
   t1 = (time_t *)malloc((time_t)sizeof(time_t));
   time(t1);
   switch(p)
   {
     case create:  printf("CREATE USER\n"); 
                    for(i=0;i<MAX_LOOP;i++)
                    {
                      printf("Enter usernb\n");
                      scanf("%d",&set->Tx[i].usernb); 
                     for(k=0;k<MAX_LOOP;k++)
                       {
                         printf("Enter Sub ARRAy Number\n");
                         scanf("%d",&set->Tx[i].s_a[k].sub_num); 
                         printf("Enter number of Antenna You want in your sub array  for observation\n");
                         scanf("%d",&set->Tx[i].s_a[k].num_in_sub); 
                         printf("Enter the Antenna names which you want in your sub Array\n");
                         for(j=0;j<set->Tx[i].s_a[k].num_in_sub;j++)
                        {
                          scanf("%s",set->Tx[i].s_a[k].ant_name[j]);
                        }             
                      }
                      ctime_r(t1,set->Tx[i].timestamp);
                    }
                   break;
     case add: printf(" ADD USER\n");break;
     case cmd2sub : fprintf(stderr," Enter the user number & Subarray number\n");
                     scanf("%d %d",&un,&sn);
                    fprintf(stderr,"user number %d & Subarray number %d\n",un,sn);
                     for(i=0;i<MAX_LOOP;i++)
                     {
                       if(i==un)
                      {
                        fprintf(stderr,"### usernb is %d I= %d un=%d\n",set->Tx[i].usernb,i,un);
                        for(k=0;k<MAX_LOOP;k++)
                       { 
                          if(k==sn)
                        {
                          fprintf(stderr,"## Sub array Number %d I=%d K=%d SN=%d\n",set->Tx[i].s_a[k].sub_num,i,k,sn);
                          fprintf(stderr,"The Antenna names in your sub Array\n");
                           for(j=0;j<set->Tx[i].s_a[k].num_in_sub;j++)
                           {
                               fprintf(stderr,"#### => %s\n",set->Tx[i].s_a[k].ant_name[j]);
                                strcpy(cmmd[j],set->Tx[i].s_a[k].ant_name[j]);
                                 
                          }
                        }             
                      } 
                      fprintf(stderr," Timestamp=> %s\n",set->Tx[i].timestamp); 
                     }
                   }
                                      for(m=0;m<32;m++)
                                     {
                                       for (n = 0; n < END; n++) 
                                      {
                                        if (!strcasecmp(cmmd[m], at_name[n]))
                                          {
                                            antenna(n);
                                         }
                                       }
                                     }
                                     break;
     case delete: printf("REMOVE USER\n");break;
     case showuser : fprintf(stderr,"Show user\n");
                     for(i=0;i<MAX_LOOP;i++)
                    {
                      fprintf(stderr,"usernb is %d\n",set->Tx[i].usernb);
                       for(k=0;k<MAX_LOOP;k++)
                      {
                        fprintf(stderr,"Sub ARRAy Number %d\n",set->Tx[i].s_a[k].sub_num);
                        fprintf(stderr,"The Antenna names in your sub Array\n");
                        for(j=0;j<set->Tx[i].s_a[k].num_in_sub;j++)
                         {
                          fprintf(stderr,"%s\n",set->Tx[i].s_a[k].ant_name[j]);
                         }             
                       } 
                     fprintf(stderr," Timestamp=> %s\n",set->Tx[i].timestamp); 
                   }
                    break;
     
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
   int i=0;
   
    setdata *set;  
    set = (setdata *)malloc(sizeof(setdata));
   while((name=readline("\n >> "))!=NULL)
    {
      if (strcmp(name,"stop")==0)
      continue;
      printf("\n");
      if(name)
      {
        pthread_mutex_lock(&lock);
        ret=1;
         token=strtok(name,del);
         while(token !=NULL)
         { 
           i=0;
          strcpy(cmd[i],token);
          fprintf(stderr," CMD[%d] => %s\n",i,cmd[i]);
          i++; 
          no_element = i;
          //fprintf(stderr," Number of Element is %d\n",no_element);
          token =  strtok(NULL," ");
         }
            for(i=0;i<UEND;i++)
          {
            if (!strcasecmp(cmd[0], us[i]))
            {
              fprintf(stderr,"####### STRING is %s %d\n",cmd[0],i);
              userdef(i,set);
              bzero(cmd,sizeof(cmd));
            }
          }
         bzero(name,sizeof(name));
        pthread_mutex_unlock(&lock);
       }
       else
        { ret=0; }
      //usleep(10000);
       if (name[0]!=0)
            add_history(name);
     }
   free(name);
   return NULL;
}
void* lowuser( void* parameters)
{
  int i,j;

  for(;;)
  { 
     pthread_mutex_lock(&lock);
      if(ret){
      i = 0;
      ret=0;
    //  fprintf(stderr,"HIGH USER INPUT ===>%s\n",name);
      token=strtok(name,del);
       while(token !=NULL)
        { 
          strcpy(cmd[i],token);
          fprintf(stderr," CMD[%d] => %s\n",i,cmd[i]);
          i++; 
          no_element = i;
          //fprintf(stderr," Number of Element is %d\n",no_element);
          token =  strtok(NULL," ");
        } 
        for(j=0;j<32;j++)
        {
         for (i = 0; i < END; i++) 
         {
           if (!strcasecmp(cmd[j], at_name[i]))
            {
             //fprintf(stderr,"####### STRING is %s %d\n",cmd[0],i);
              antenna(i);
            }
         }
        }
       
           for(i=0;i<DEND;i++)
         {
            if (!strcasecmp(cmd[0], das[i]))
            {
             //fprintf(stderr,"####### STRING is %s %d\n",cmd[0],i);
              dasdef(i);
            }
          } 
        
     //   pthread_mutex_unlock(&lock);
      
      // usleep(500);
      }
      
      bzero(cmd,sizeof(cmd));
     pthread_mutex_unlock(&lock);
    
   }
   return NULL;
}

int main()
{
  pthread_t high,low;
     
  pthread_create(&high ,NULL,&highuser,NULL);
  
  pthread_create(&low,NULL ,&lowuser,NULL);
   
  pthread_join(high,NULL);	
  pthread_join(low,NULL); 
 
  printf(" ALL THREAD CLOSED\n");
  return 0;
} 
