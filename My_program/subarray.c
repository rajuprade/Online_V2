/* Program for Sub array selction & mapping of Antenna name & Command sending. */

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMSZ 6000
#define MAX_LOOP 2
#define MAX_ANT 4

static char at_name[32][8] = {"C00","C01","C02","C03","C04","C05","C06","C08","C10","C11","C12","C13","C14","E02"
           ,"E03","E04","E05","E06","S01","S02","S03","S04","S06","W01","W02","W03","W04","W05","W06"}; 

typedef enum { C00,C01,C02,C03,C04,C05,C06,C08,C10,C11,C12,C13,C14,E02,E03,E04,E05,E06,S01,S02,S03,S04,
                S06,W01,W02,W03,W04,W05,W06,END } ant_name;
void antenna(int i,char cmd[][10]);

void antenna(int i, char cmd[][10])
{
   int j;
   switch(i)
   {
     case C00: printf("C00 ANTENNA\n");
               fprintf(stderr,"ANTENNA %s\n",cmd[0]);
               fprintf(stderr,"System  %s\n",cmd[1]);
               fprintf(stderr,"Operation name  %s\n",cmd[2]);
               break;
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

int main()
{
  int i=0,j,k,m,n,a,b,flag=0,op,un,sn;
   char cmd[10][10];
   setdata *set;  
   set = (setdata *)malloc(sizeof(setdata));
   time_t *t1;
   t1 = (time_t *)malloc((time_t)sizeof(time_t));
   time(t1);
   
    while(1)
    {
     fprintf(stderr," Enter Option\n");
    fprintf(stderr," Enter 0 : Create USER\n"); 
    fprintf(stderr,"Enter  1 : Sending command to user/Subarray\n"); 
    fprintf(stderr,"Enter  2 : Displaying user/Subarray\n"); 
    scanf("%d",&op);

    switch(op)
    {
       case 0:  // LOOP for taking USER INPUT 
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

        case 1: fprintf(stderr," Enter the user number & Subarray number\n");
                scanf("%d %d",&un,&sn);
                fprintf(stderr,"user number %d & Subarray number %d\n",un,sn);
                fprintf(stderr,"Enter the system name & Operation name\n");
                 scanf("%s %s",cmd[1],cmd[2]);
                fprintf(stderr,"system name %s & Operation name %s\n",cmd[1],cmd[2]);
                 for(i=0;i<MAX_LOOP;i++)
                 {
                   if(i==un)
                   {
                     fprintf(stderr,"usernb is %d\n",set->Tx[i].usernb);
                     for(k=0;k<MAX_LOOP;k++)
                      { 
                        if(k==sn)
                        {
                         // fprintf(stderr,"Sub ARRAy Number %d\n",set->Tx[i].s_a[k].sub_num);
                         // fprintf(stderr,"The Antenna names in your sub Array\n");
                           for(j=0;j<set->Tx[i].s_a[k].num_in_sub;j++)
                           {
                               fprintf(stderr,"#### => %s\n",set->Tx[i].s_a[k].ant_name[j]);
                                strcpy(cmd[j],set->Tx[i].s_a[k].ant_name[j]);
                                 
                          }
                        }             
                     } 
                   // fprintf(stderr," Timestamp=> %s\n",set->Tx[i].timestamp); 
                  }
                }
                                      for(m=0;m<32;m++)
                                     {
                                       for (n = 0; n < END; n++) 
                                      {
                                        if (!strcasecmp(cmd[m], at_name[n]))
                                          {
                                            antenna(n,cmd);
                                        }
                                      }
                                    }
                break;

        case 2:   // LOOP for priting USER INPUT   
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
     return 0;
}
