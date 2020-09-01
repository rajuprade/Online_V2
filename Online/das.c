#include"das.h"


void showMessage(char *message)
{
  struct tm *tst;
  time_t t;
  t=time(NULL);
  tst=localtime(&t);
  fprintf( stdout, "%.2d/%.2d/%.4d %.2d:%.2d:%.2d",tst->tm_mday,tst->tm_mon+1,tst->tm_year+1900,tst->tm_hour,tst->tm_min,tst->tm_sec);
  //fprintf( stdout, " Sub %d", subArray) ;
  fprintf( stdout, " %s.\n", message);
  fflush( stdout );
}

int create_msgq_()
{
       /*  int msgid;
	    if((msgid = msgget(KEY, 0600 | IPC_CREAT)) < 0) {
	       fprintf(stderr," unable to get msgid %d\n",msgid);
	    }
        return (msgid); */

    int msqid;
    int msgflg = IPC_CREAT | 0600;
    key_t key;
   // message_buf sbuf;
  //  message_buf  rbuf;
    size_t buf_length;
    int ii;
    /*
     * Get the message queue id for the
     * "name" 1234, which was created by
     * the server.
     */
    key = 201;

(void) fprintf(stderr, "\nmsgget: Calling msgget(%#lx,\
%#o)\n",
key, msgflg);

    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        exit(1);
    }
    else 
     (void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);

    return(msqid);


}

int sndmsgq_(message_buf *sbuf)
{
   int ii,j,k,qwait,await;
    message_buf  rbuf;
    size_t buf_length;
    char dmsg[20];
    sbuf->mtype = 1;
    ii=sbuf->mtype+1;
    sbuf->mtype = 1;
    k=128;
    buf_length = strlen(sbuf->mtext) + 1 ;
    /* fprintf(stderr,"MSEESAGE ID %d\n",msgID); 
    fprintf(stderr,"IN sendMSG => %s\n",sbuf.mtext); */
    
   
     while(msgrcv(msgID,(void *)&rbuf,k,ii,IPC_NOWAIT)>0);
      k=strlen(sbuf->mtext);
     if(msgsnd(msgID,sbuf, k+1,IPC_NOWAIT) < 0){
       fprintf(stderr," unable to send  mesg \n");
       return(-1);
     }
     else 
     printf("Message Sent=>%s\n", sbuf->mtext); 
     await=10;
     j=0;
     k=128;
     while(msgrcv(msgID,(void *)&rbuf,k,ii,IPC_NOWAIT)<0){
       fprintf(stderr,"waiting for ack id %d\n",ii);
       sleep(1);
       j++;
       if(j==await) {
	  fprintf(stderr,"abort:waiting for ack\n");
	  return(-2);
       }
    }
    fprintf(stderr,"ACK Got from DASSERVER : %s\n",rbuf.mtext);
    strcpy(dmsg,rbuf.mtext);
    showMessage(dmsg);
    write_shm_das(dmsg);
    qwait=10;
    j=0;
    while(msgrcv(msgID,(void *)&rbuf,k,ii,IPC_NOWAIT)<0){
       fprintf(stderr,"waiting for success is %d \n",ii);
       sleep(1);
       j++;
       if(j==qwait) {
	  fprintf(stderr,"abort:waiting for success\n");
	  return(-3);
       }
    }
    fprintf(stderr,"%s\n",rbuf.mtext); 
    strcpy(dmsg,rbuf.mtext);
    showMessage(dmsg); write_shm_das(dmsg);
    return(0);
}


int wrt_hdr(int flag)
{
   FILE *file, * file1;
   fprintf(stderr,"File size of ProjectType structure is %d\n",sizeof(ProjectType));
   fprintf(stderr,"File size of SourceType structure is %d\n",sizeof(SourceParType));
   ProjectType proj;
   SourceParType source;
   strcpy(proj.code,"TEST");
   strcpy(proj.observer,"");
   strcpy(proj.title,"");
   proj.antmask = 0x7ffffffe;
   proj.bandmask = 003;
   proj.seq =1;
   
   strcpy(source.object,"OFFCASA");
   source.flux.i=1;
   source.flux.q=1;
   source.flux.u=1;
   source.flux.v=1;
   source.mjd0=56755.000000;
   source.ra_app = 330.217665;
   source.dec_app= 57.690950;
   source.ra_date= 330.217665;
   source.dec_date= 57.690950;
   source.dra= 0.000000;
   source.ddec= 0.000000;
   source.freq[0]= 591000000.000000;
   source.freq[1]= 591000000.000000;
   source.first_lo[0]=540000000.000000 ;
   source.first_lo[1]= 540000000.000000; 
   source.bb_lo[0]=510000000.000000 ;
   source.bb_lo[1]= 510000000.000000;  

   source.rest_freq[0]=0.000000;
   source.rest_freq[1]=0.000000;

   source.lsrvel[0]=0.000000;
   source.lsrvel[1]=0.000000;
   source.ch_width=0.000000; 
   source.id = 1;
   source.net_sign[0]= 1;
   source.net_sign[1]= 0; 
   source.net_sign[2]= -1; 
   source.net_sign[3]= 0;

    source.mode=1;
    source.dum1=1;
    source.antmask = 0x7ffffffe;
    source.bandmask = 003;
    source.dum2=1;

    source.calcode = 0;
    source.qual=0;
 
    if(flag)
    {
     file = fopen("/home/raj/teleset/Desktop/proj.hdr","wb");
     fwrite(&proj,sizeof(ProjectType),1,file);
     fprintf(stderr,"Created Proj file\n");
    }
   else
   {
   file1 = fopen("/home/raj/teleset/Desktop/scan.hdr","wb");
   //fwrite(buffer,lSize,1,scan);
   fwrite(&source,sizeof(SourceParType),1,file1);
      fprintf(stderr,"Created Scan file\n");
   }

  if(flag)
  {
   fclose(file);
  }
  else
  {
  fclose(file1);
  }
  return 0;

}


/* int wrt_scan_hdr_(char *filename,ScanInfoType *scan_hdr,int *ityp)
{
    FILE *file;
    int stat;

    file=fopen(filename,"wb");
    if(file==0){
       fprintf(stderr,"Error opening file %s\n",filename);
       return(-1);
    }
    if(*ityp==0){
      stat=fwrite(&(scan_hdr->source),sizeof(SourceParType),1,file);
    } else if(*ityp==1){
      stat=fwrite(&(scan_hdr->proj),sizeof(ProjectType),1,file);
    }
    if(stat!=1){
       fprintf(stderr,"Error writing into %s\n",filename);
       fclose(file);
       return(-2);
    }
    fclose(file);
    return(0);

} */

