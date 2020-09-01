#include"server.h"
#include"high_user.h"
#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)


int main(int argc, char *argv[])
{
     int n,i;
     int socfd[30];
     pthread_t first_antenna,second_antenna;
     pthread_attr_t custom_attr_fifo;	
     int fifo_max_prio;	
     struct sched_param fifo_param;	
     pthread_t high,low;
     
    pthread_create(&high ,NULL,&highuser,NULL);
  
    pthread_create(&low,NULL ,&lowuser,NULL);

    pthread_attr_init(&custom_attr_fifo);	
    pthread_attr_setschedpolicy(&custom_attr_fifo, SCHED_FIFO);	
    fifo_param.sched_priority = sched_get_priority_max(SCHED_FIFO);	
    pthread_attr_setschedparam(&custom_attr_fifo, &fifo_param); 
	
   /*  setdata *set;  
     set = (setdata *)malloc(sizeof(setdata)); */
      
      ANS *an;
      an = malloc(sizeof(ANS));
     
    /*  printf("Enter 0 for file input and 1 for user input\n");
      scanf("%d",&n);
      exec(set,n);
      write_us_shm(set); */
    
       pthread_create(&high ,NULL,&highuser,NULL);
  
       pthread_create(&low,NULL ,&lowuser,NULL);
       
      
     if(init_server()== ERROR)
     {
       fprintf(stderr," ####### ERROR Opening Socket ##########\n");
     }
    clilen = sizeof(cli_addr); 
        while(1)
       {  
            i=0;
           fprintf(stderr,"############# SERVER WANTING FOR CLIENT CONNECTION #####\n");
           socfd[i] = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen); 
           //fprintf(stderr,"DISPATCHER Connected ===> %s on Port %d ####\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port));
             if(!strcmp(inet_ntoa(cli_addr.sin_addr),C00_IP))
              {
                 an->sockfd=socfd[i];
                if( pthread_create( &first_antenna ,&custom_attr_fifo,connection_handler,(void*) an) < 0)
                {
                  perror("could not create thread");
                  return 1;
                }
              } 
               else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C01_IP))
              {
                 an->sockfd=socfd[i];
                if( pthread_create( &second_antenna ,&custom_attr_fifo,C01_handler,(void*) an) < 0)
                {
                  perror("could not create thread");
                  return 1;
                }
              } 
          i++;
         }  
  pthread_join(first_antenna,NULL);
  pthread_join(second_antenna,NULL);
  pthread_join(high,NULL);	
  pthread_join(low,NULL); 
     return 0; 
}
#else
int main(void) {
    fprintf(stderr, "server2 support not compiled in\n");
    exit(1);
}
#endif

