#ifndef _HIGHUSER_H
#define _HIGHUSER_H

#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void* highuser( void* parameters);
void* lowuser( void* parameters);
typedef enum { C00,C01,C02,C03,C04,END } ant_name;
typedef enum { create,add,delete,UEND} udef;
typedef enum {dasinit,addp,delprj,startscan,stopscan,DEND} dastype;

int ret,no_element;
char *name;
char *token;
char cmd1[10][32];
void antenna(int i);

void userdef(int k);
void dasdef( int r);

#endif
