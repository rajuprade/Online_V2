#include"server.h"


#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)

int main(int argc, char *argv[])
{
     int sockfd, newsockfd,yes=1;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     char argname[32][32];
  //   time_t t1;
    
      char *tstamp;
     tstamp = malloc(25);
      cmd *c1;
      c1 = malloc(sizeof(cmd));
      resp *r1;
      r1 = malloc(sizeof(resp));


  /****** Socket opening code *****/ 
 /*    sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
       fprintf(stderr,"ERROR opening socket\n");
    if(setsockopt(sockfd, SOL_SOCKET , SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
          error(" Error\n");
    } 
     bzero((char *) &serv_addr, sizeof(serv_addr));
    // portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT);

     if (bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
              { 
               fprintf(stderr,"ERROR binding socket\n");
              }

     listen(sockfd,5);

     clilen = sizeof(cli_addr);
     
     fprintf(stderr,"############# SERVER WANTING FOR CLIENT CONNECTION #####\n");
   while(1)
  {
    newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen); */





    /* printf("Enter CH1 bandwidth\n");
     scanf("%s", &argdata); */
     printf("Enter system name:sentinal/front_end/fibre_optics/back_end/self_test\n");
     scanf("%s", argname[0]);
     printf(" Enter operation name which you want to perform on system: set/mon/init/reset\n");
     scanf("%s", argname[1]);

    
     c1->seq= 10;

 /******* BACK END CONTRAOl and Monitor start Here *****************************/
  
    if(!strcmp(argname[0],"back_end"))
      {
           // strcpy(c1->system_name,"back_end");
              strcpy(c1->system_name,argname[0]);
            if(!strcmp(argname[1],"mon"))
              {
                   strcpy(c1->op_name,"mon");
                   c1->number_param=0;
                /*   strcpy(c1->parameter_name,"'\0'");
                   strcpy(c1->Argument_Ch1,"'\0'");
                   strcpy(c1->Argument_Ch2,"'\0'"); */
               }
        else if(!strcmp(argname[1],"set"))
                 {  
                       strcpy(c1->op_name,"set");      
                       c1->number_param=8;

                       strcpy(c1->parameter_name[0],"lo");
                       strcpy(c1->parameter_name[1],"attn");
                       strcpy(c1->parameter_name[2],"filter");
                       strcpy(c1->parameter_name[3],"lpf");
                       strcpy(c1->parameter_name[4],"source");
                       strcpy(c1->parameter_name[5],"ant_ns");
                       strcpy(c1->parameter_name[6],"drct_mxr");
                       strcpy(c1->parameter_name[7],"channel");

                       strcpy(c1->Argument_Ch1[0],"1800000");
                       strcpy(c1->Argument_Ch1[1],"12");
                       strcpy(c1->Argument_Ch1[2],"10");
                       strcpy(c1->Argument_Ch1[3],"0");
                       strcpy(c1->Argument_Ch1[4],"siggen");
                       strcpy(c1->Argument_Ch1[5],"antenna");
                       strcpy(c1->Argument_Ch1[6],"direct");
                       strcpy(c1->Argument_Ch1[7],"1");
    
                       strcpy(c1->Argument_Ch2[0],"2000000"); 
                       strcpy(c1->Argument_Ch2[1],"15");
                       strcpy(c1->Argument_Ch2[2],"6");
                       strcpy(c1->Argument_Ch2[3],"1");
                       strcpy(c1->Argument_Ch2[4],"synthesizer");
                       strcpy(c1->Argument_Ch2[5],"noise");
                       strcpy(c1->Argument_Ch2[6],"mixer");
                       strcpy(c1->Argument_Ch2[7],"2");
                 }
             else if(!strcmp(argname[1],"init"))
                 {  
                       strcpy(c1->op_name,"init");      
                       c1->number_param=0;
                 }  
           else if(!strcmp(argname[1],"reset"))
                 {  
                       strcpy(c1->op_name,"reset");      
                       c1->number_param=0;
                 }  
           else
           { fprintf(stderr," No input\n"); }
        }
 /******* BACK END CONTRAOl and Monitor end Here *****************************/        
 
/**********************FRONT END CONTROL AND MONITOR START HERE ******************/

else if(!strcmp(argname[0],"front_end"))
      {
           // strcpy(c1->system_name,"back_end");
              strcpy(c1->system_name,argname[0]);
            if(!strcmp(argname[1],"mon"))
              {
                   strcpy(c1->op_name,"mon");
                   c1->number_param=0;
                /*   strcpy(c1->parameter_name,"'\0'");
                   strcpy(c1->Argument_Ch1,"'\0'");
                   strcpy(c1->Argument_Ch2,"'\0'"); */
               }
        else if(!strcmp(argname[1],"set"))
                 {  
                       strcpy(c1->op_name,"set");      
                       c1->number_param=7;

                       strcpy(c1->parameter_name[0],"cal_ns");
                       strcpy(c1->parameter_name[1],"rf");
                       strcpy(c1->parameter_name[2],"filter");
                       strcpy(c1->parameter_name[3],"fltr_bnd");
                       strcpy(c1->parameter_name[4],"band_sel");
                       strcpy(c1->parameter_name[5],"slr_attn");
                       strcpy(c1->parameter_name[6],"channel");

                       strcpy(c1->Argument_Ch1[0],"LO");
                       strcpy(c1->Argument_Ch1[1],"on");
                       strcpy(c1->Argument_Ch1[2],"1");
                       strcpy(c1->Argument_Ch1[3],"1060");
                       strcpy(c1->Argument_Ch1[4],"50");
                       strcpy(c1->Argument_Ch1[5],"44");
                       strcpy(c1->Argument_Ch1[6],"swap");
                       
    
                       strcpy(c1->Argument_Ch2[0],"Medium"); 
                       strcpy(c1->Argument_Ch2[1],"off");
                       strcpy(c1->Argument_Ch2[2],"4");
                       strcpy(c1->Argument_Ch2[3],"1170");
                       strcpy(c1->Argument_Ch2[4],"150");
                       strcpy(c1->Argument_Ch2[5],"30");
                       strcpy(c1->Argument_Ch2[6],"unswap");
                      
                 }
            else if(!strcmp(argname[1],"init"))
                 {  
                       strcpy(c1->op_name,"init");      
                       c1->number_param=0;
                 }  
           else if(!strcmp(argname[1],"reset"))
                 {  
                       strcpy(c1->op_name,"reset");      
                       c1->number_param=0;
                 }  
           else
           { fprintf(stderr," No input\n"); }
        }
/********************* fRONT END CONTROL AND MONITOR END HERE ********************/ 

/*********************Sentinal control and monitor start here ********************/
else if(!strcmp(argname[0],"sentinel"))
      {
           // strcpy(c1->system_name,"back_end");
              strcpy(c1->system_name,argname[0]);
            if(!strcmp(argname[1],"mon"))
              {
                   strcpy(c1->op_name,"mon");
                   c1->number_param=0;
                /*   strcpy(c1->parameter_name,"'\0'");
                   strcpy(c1->Argument_Ch1,"'\0'");
                   strcpy(c1->Argument_Ch2,"'\0'"); */
               }
        else if(!strcmp(argname[1],"set"))
                 {  
                       strcpy(c1->op_name,"set");      
                       c1->number_param=1;
                       strcpy(c1->parameter_name[0],"dmask");
                       strcpy(c1->Argument_Ch1[0],"ffff");
                       strcpy(c1->Argument_Ch2[0],"0000"); 
                  }
          else if(!strcmp(argname[1],"init"))
                 {  
                       strcpy(c1->op_name,"init");      
                       c1->number_param=0;
                 }  
           else if(!strcmp(argname[1],"reset"))
                 {  
                       strcpy(c1->op_name,"reset");      
                       c1->number_param=0;
                 }  
           else
           { fprintf(stderr," No input\n"); }
        }
/**********************sentinal control and monitor end here *********************/

/*********************Fibre_optics Control and monitor start here ***************/

else if(!strcmp(argname[0],"fiber_optics"))
      {
           // strcpy(c1->system_name,"back_end");
              strcpy(c1->system_name,argname[0]);
            if(!strcmp(argname[1],"mon"))
              {
                   strcpy(c1->op_name,"mon");
                   c1->number_param=0;
                /*   strcpy(c1->parameter_name,"'\0'");
                   strcpy(c1->Argument_Ch1,"'\0'");
                   strcpy(c1->Argument_Ch2,"'\0'"); */
               }
        else if(!strcmp(argname[1],"set"))
                 {  
                       strcpy(c1->op_name,"set");      
                       c1->number_param=1;
                       strcpy(c1->parameter_name[0],"rf_attn");
                       strcpy(c1->Argument_Ch1[0],"25");
                       strcpy(c1->Argument_Ch2[0],"35"); 
                  }
          else if(!strcmp(argname[1],"init"))
                 {  
                       strcpy(c1->op_name,"init");      
                       c1->number_param=0;
                 }  
           else if(!strcmp(argname[1],"reset"))
                 {  
                       strcpy(c1->op_name,"reset");      
                       c1->number_param=0;
                 }  
           else
           { fprintf(stderr," No input\n"); }
        }
/******************* Fibre_optics Control and monitor end here  ****************/

/********************self Test system ***************/
else if (!strcmp(argname[0],"self_test"))
      {
           // strcpy(c1->system_name,"back_end");
              strcpy(c1->system_name,argname[0]);
             if(!strcmp(argname[1],"mon"))
              {
                   strcpy(c1->op_name,"mon");
                   c1->number_param=0;
                /*   strcpy(c1->parameter_name,"'\0'");
                   strcpy(c1->Argument_Ch1,"'\0'");
                   strcpy(c1->Argument_Ch2,"'\0'"); */
               }
        else if(!strcmp(argname[1],"set"))
                 {  
                       strcpy(c1->op_name,"set");      
                       c1->number_param=3;
                       strcpy(c1->parameter_name[0],"ss");// set spectrum spreader
                       strcpy(c1->Argument_Ch1[0],"0");   // Range : 0,1,2,3
                       strcpy(c1->parameter_name[1],"fdb");// set frequency doubler
                       strcpy(c1->Argument_Ch1[1],"1");   // Range 0 or 1 
                       strcpy(c1->parameter_name[2],"fdv");// set frequency divider
                       strcpy(c1->Argument_Ch1[2],"1");   // Range 1,2,4,6,8                  
                
                  }
          else if(!strcmp(argname[1],"init"))
                 {  
                       strcpy(c1->op_name,"init");      
                       c1->number_param=0;
                 }  
           else if(!strcmp(argname[1],"reset"))
                 {  
                       strcpy(c1->op_name,"reset");      
                       c1->number_param=0;
                 }  
           else
           { fprintf(stderr," No input\n"); }
        }
/*******************self test system ***************/


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
       fprintf(stderr,"ERROR opening socket\n");
    if(setsockopt(sockfd, SOL_SOCKET , SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
          fprintf(stderr," Error\n");
    } 
     bzero((char *) &serv_addr, sizeof(serv_addr));
    // portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT);

     if (bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
              { 
               fprintf(stderr,"ERROR binding socket\n");
              }

     listen(sockfd,5);
  //again:
  for(;;)
  {
     clilen = sizeof(cli_addr);
     
     fprintf(stderr,"############# SERVER WANTING FOR CLIENT CONNECTION #####\n");

    newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen); 
while(1)
{
       // newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
        if (newsockfd < 0) 
           fprintf(stderr,"ERROR Accept socket\n");
           fprintf(stderr,"\n Now Writing on Socket\n");
          /*  time(&t1);
            ctime_r(&t1,stamp1);*/
             
            tstamp = tp(tstamp);
            strcpy(c1->timestamp,tstamp);

           write(newsockfd,c1,sizeof(cmd));
       
          sleep(2);
         fprintf(stderr,"\nNow Reading on Socket\n"); 
         if (readable_timeo(newsockfd, 5) == 0)
          {
               fprintf(stderr, "SOCKET TIMEOUT\n");
               close(newsockfd);
               //goto again;
              // continue;
                 break;
         }
         else
         {
           read(newsockfd,r1,sizeof(resp));
            write_shm(c1,r1); // writing all data to shared memory 
            printcmd(c1);
            printresp(r1);
            write_command_xml(c1);
            write_response_xml(r1);
         }
        
          
       }
 } 
     
     return 0; 

}
#else
int main(void) {
    fprintf(stderr, "server2 support not compiled in\n");
    exit(1);
}
#endif

