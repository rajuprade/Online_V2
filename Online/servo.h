#ifndef H_SERVO_H
#define H_SERVO_H
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<time.h>
#include <math.h>
#include <unistd.h>
#define PORT_SERVO 5500

typedef enum {COLDSTART,TRACK,HOLD,POSITION,STOP,CLOSE,STOW,STOWRELEASE,ABORT,RESETHW,
                 READANGLES,READANAVAR,READDIGVAR,READSETPARA,READANTSTATUS,READVERSION,SEND} SERVOCMD;

#pragma pack(push,1)
typedef struct 
{
  int seq;
  char timestamp[64];
  char system_name[16]; // Not required in servo communication
 // char cmd_code[4];
  char op_name[16];
  short int number_param;
  char para_name[32][16];
  char para_value[32][16];
 // // Not required in servo communication
 } servocmd;

typedef struct
{ 
 int seq;
 char timestamp[64];
 char system_name[16];
 int response_code; // immediate =1 ( ACK or NAK ) event=3 & final =2  data mon = 4
 int response_type;// success =1 or failure = 2
 char response_msg[50];  //Accepted ,not accepted, sysntax error, irrelvant command,incomplete,unknown + Event
 short int num_resp_msg;
 char para_name[32][32];
 char para_value[32][32]; 
} servoresp;


typedef struct
{
  char antenna_name[10];
  servocmd  SRVCMD;
} SRVANT_CMD;

#pragma pack(pop)

void printservocmd(servocmd *s1);
void printservoresp(servoresp *sr1);
void servo_cmd_list(int i,SRVANT_CMD *s1);
void* servosystem( void* parameters);

void AskAx(SRVANT_CMD *a1);
void AskAng(SRVANT_CMD *a1);
void AskTime(SRVANT_CMD *a1);


#endif //H_SERVO_H
