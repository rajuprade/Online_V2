#include"server.h"

#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)


int main(int argc, char *argv[])
{
     int n,i;
     int socfd[30];
     pthread_t first_antenna[30];
     pthread_attr_t custom_attr_fifo;	
     int fifo_max_prio;	
     struct sched_param fifo_param;	

   pthread_attr_init(&custom_attr_fifo);	
   pthread_attr_setschedpolicy(&custom_attr_fifo, SCHED_FIFO);	
   fifo_param.sched_priority = sched_get_priority_max(SCHED_FIFO);	
   pthread_attr_setschedparam(&custom_attr_fifo, &fifo_param); 
	
     setdata *set;  
     set = (setdata *)malloc(sizeof(setdata));
      
      ANS *an;
      an = malloc(sizeof(ANS));
     
      printf("Enter 0 for file input and 1 for user input\n");
      scanf("%d",&n);
      exec(set,n);
      write_us_shm(set);

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
           fprintf(stderr,"DISPATCHER Connected ===> %s on Port %d ####\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port));

           strcpy(an->aname,set->Tx[0].s_a[0].ant_name[i]); // copy the first antenna name from file/user input
           fprintf(stderr,"######## Number of Antenna in sub array [[[%d]]]\n",set->Tx[0].s_a[0].num_in_sub); 
           an->sockfd=socfd[i];
           if( pthread_create( &first_antenna[i] ,&custom_attr_fifo,connection_handler , (void*) an) < 0)
            {
              perror("could not create thread");
              return 1;
           }
          i++;
         }  
 pthread_join(first_antenna[i],NULL);
     return 0; 
}
#else
int main(void) {
    fprintf(stderr, "server2 support not compiled in\n");
    exit(1);
}
#endif

