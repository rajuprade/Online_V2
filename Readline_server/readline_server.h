#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include<signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMSZ1 sizeof(cmd)
#define SHMSZ2 sizeof(resp) 
#include <readline/readline.h>
#include <readline/history.h>
 
#define PORT 5000
#define ERROR -1
extern int sockfd;
int sockfd;
socklen_t clilen;
struct sockaddr_in serv_addr, cli_addr;
extern int done;
int done = 0;
int sfd;
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
 char Mon_sum[32][64];   // Future we will make it [32][64]
 short int num_resp_msg;
 char response_message[32][64];  // Future we will make it [32][64]
} resp;

#pragma pack(pop)

extern int init_server(void);
extern char* tp(char *tstamp);
void exec_cmd(int n,cmd *c1);
extern void write_read(int newsockfd,cmd *c1, resp *r1);
extern void write_shm(cmd *c1, resp *r1);
extern int readable_timeo(int fd, int sec);
extern void printcmd(cmd *c1);
extern void printresp(resp *r1);

