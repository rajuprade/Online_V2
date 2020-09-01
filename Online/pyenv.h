#ifndef _PYENV_H
#define _PYENV_H

#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include <stdlib.h>

#define PORT_PYENV 7100

typedef struct
{ 
  char ant_name[20];
  char sys_name[20];
} PYACK;

//main structure to communicate with python environment
/*
typedef struct { 
   int  user_no;
   int  cmd_no;
   int  array ;
   int  no_of_antennas;
   char antenna_list[32][4];
   char system_name[16];
   char cmd_name[24];
   //testcmd command;
} PYS;

*/
typedef struct {
    int  user_no;
    int  cmd_no;
    int  array ;
    int  no_of_antennas;
    char antenna_list[32][4];
    char system_name[16];
    char buffer_cmd[1640];
 } PYS;


void* pyenv_interface( void* parameters);

#endif
