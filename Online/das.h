#ifndef H_DAS_H
#define H_DAS_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include <string.h>
#include"shm.h"
#define MSGSZ     128
#define KEY 201        // Message Queue ID
#define MAX_DAS_SUB 6

int msgID;

typedef struct msgbuf
{
   long    mtype;
   char    mtext[256*4];
} message_buf;

int create_msgq_();

int sndmsgq_(message_buf *msg);

void showMessage(char *message);

//int wrt_scan_hdr_(char *filename,ScanInfoType *scan_hdr,int *ityp);

int wrt_hdr(int);

// online.h structure used in DAS project file & scan file. Date 25/02/2014

typedef struct {
        float i;
        float q;
        float u;
        float v;
}    		POL_FLUX;


typedef struct { 
  char object[32];
  POL_FLUX flux;
  double mjd0;
  double ra_app, dec_app, ra_date, dec_date, dra,ddec; /* rad, rad/s */
  double freq[2];
  double first_lo[2];
  double bb_lo[2];
  double rest_freq[2];
  double lsrvel[2];  /* Hz, km/s  */
  double ch_width;  /* Hz */
  int id; 
  int net_sign[4]; 
  int mode;
  int dum1;
  unsigned int antmask;
  unsigned short bandmask,dum2;
  short calcode, qual;
} SourceParType;                      // sizeof(SourceParType) to be written in scan.hdr.


typedef struct {
  char code[8];
  char observer[32];
  char title[32];
  unsigned int antmask;
  unsigned short bandmask,seq;
} ProjectType;                      // sizeof(ProjectType) to be written in Proj.hdr.

typedef struct {
  int status;
  float t;  /* program dependent meaning ! */
  ProjectType proj;
  SourceParType source;
} ScanInfoType;



typedef struct {
        char datafile[80];
        int  das_sub_state;
        int  cmd_no;
        ScanInfoType cntl;
}		DAS_SUB_CNTL;


typedef struct {
        char   config_file[80];
        int    msg_id;
        int    das_state;
        int    das_sub_state[MAX_DAS_SUB];
        DAS_SUB_CNTL sub_cntl[MAX_DAS_SUB];
}               DAS_CNTL;

#endif //H_DAS_H
