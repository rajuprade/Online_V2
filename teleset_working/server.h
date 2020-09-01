#ifndef H_SERVER_H
#define H_SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<time.h>
#include<malloc.h>
#include <math.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#define SHMSZ1 sizeof(cmd)
#define SHMSZ2 sizeof(resp) 
//#define SHMSZ 400
#define PORT 6000
#define MAX_LOOP 2
#define MAX_ANT 4

#define ERROR -1 
extern int sockfd;
int sockfd;
socklen_t clilen;
struct sockaddr_in serv_addr, cli_addr;
/*static char at_name[32][8] = {"C00","C01","C02","C03","C04","C05","C06","C08","C10","C11","C12","C13","C00","C14","E02"
           ,"E03","E04","E05","E06","S01","S02","S03","S04","S06","W01","W02","W03","W04","W05","W06"}; */

#pragma pack(push,1)

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
 } cmd;

typedef struct
{ 
 int response_type;
 int seq;
 char timestamp[64];
 char system_name[16];
 char Mon_raw[64][8];
 char Mon_sum[32][64];   
 short int num_resp_msg;
 char response_message[32][64];  
} resp;

#pragma pack(pop)

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

typedef struct
{
  char antenna_name[10];
  cmd  CMD[10];
  resp RESP[10];
}ANT;

extern void write_us_shm(setdata *set);
extern void load_data(char fname[200],setdata *set);
extern void file_input(setdata *set);
extern void user_input(setdata *set);
extern void exec(setdata *set,int n);
extern char* tp(char *tstamp);
void exec_cmd(int n,cmd *c1);
extern void write_read(int newsockfd,cmd *c1, resp *r1);
extern void write_shm(cmd *c1, resp *r1);
extern int readable_timeo(int fd, int sec);
extern void write_command_xml(cmd *c2);
extern void write_response_xml(resp *r2);
extern void printcmd(cmd *c1);
extern void printresp(resp *r1);
extern void write_shm(cmd *c1, resp *r1);
extern int readable_timeo(int fd, int sec);
extern int init_server(void);

#endif //H_SERVER_H
