#include<stdio.h> 
#include<math.h>
#include<string.h>
#include<time.h>
#include<malloc.h>
#include<pthread.h>
//#include<ctime.h>
//#define DEGUB 1
int TrackFlag, OutTrack, InfoFlag; 
float ElOffset, AzOffset;   // deg
float RArate, DECrate, Timrate;
float Latitude, Longitude, RArad, DECrad; 
double Elevation, Azimuth, Mjd;
time_t LastTrk;
int TrkCount; 
const int TIMEOUTDATA = 3;
const int TIMEOUTOPE = 7;
const int TRKINTERVAL = 10;

void Run();
void NewTrkCmd();
int TrkCmd(int* trkcnt_ptr);
void SendTrkCmd(struct tm localtm);
double GetHA(struct tm localtm, double rightAscension);
void GetSrcCoord(double *ra, double *dec, struct tm localtm);
double MjdCal(struct tm localtm) ;
double Lmst(double time) ;
void ConvertAng(double angle,unsigned char *param, int az);
void *servo(void* parameters);

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
void printservocmd(servocmd *c1);
void printservocmd(servocmd *c1)
{
   int i;
        printf("we wrote on the socket %d %s %s %s\n",c1->seq,c1->timestamp,c1->system_name,c1->op_name);
       
        for(i=0;i<c1->number_param;i++)
        {
          printf("%s %s\n",c1->para_name[i],c1->para_value[i]);
        } 
        printf(" Size of Struct is ######## %d\n",sizeof(servocmd));
     
}

void *servo(void* parameters)
{
   while(1)
  {
    Run();
    sleep(5);
   
  }
 } 
/******** RUN() ****/

void Run()
{
  printf("##### RUN() #####\n");
  if (TrackFlag == 1)
    {
      if (TrkCount == -1)
         {
           NewTrkCmd(); // First Time when we send TRACK On command from Online.
           TrkCount++;  // After New Trk command TrkCount became 0.
         }
        if (TrkCmd(&TrkCount) < 0) // If TrkCmd() retrun less than Zero (0), then Tracking is stopped.
          {
             TrackFlag = 2; 
             fprintf(stderr,"Wrong source (EL<0)\n");
          }
   }
  else if ((TrackFlag == 0) && (TrkCount >= 0)) TrkCount = -1;
}

/******* RUN() ENDS HERE ****/

/******* NEW TRACK () ***/

void NewTrkCmd()
{
  time_t t0;
  struct tm localtm0;
  printf("##### =============================> NewTrkCmd() ==============>#####\n");
 
  time(&t0); localtime_r(&t0, &localtm0);
  Mjd = MjdCal(localtm0);            //routine for midnight crossing?
  printf(" MJD calculation ===> %1f\n",Mjd);
  LastTrk = -1;
 fprintf(stderr,"New Trck mode: send Hold to Both AXIS\n");
}
/******* END HERE ******/
/***************MJD cal ****/
double MjdCal(struct tm localtm) 
{
  int year, month, day;
  double Mjd;

  year = 1900 + localtm.tm_year;
  // This line of code added from astro_cal.c of gpu corr 
   if(year < 1900) /* Y2K (!) */
    {if (year < 70)year += 2000; else year +=1900;}
  // End here 
  month = 1 + localtm.tm_mon;
  day = localtm.tm_mday;
  Mjd = (double) ((year - (12 - month) / 10 + 4712L) * 1461L / 4 +
    ((month + 9) % 12 * 306L + 5) / 10 -
    (year - (12 - month) / 10 + 4900L) / 100 * 3 / 4 +
    day - 2399904L);
  Mjd -= 5.5/24.0 ;  // to correspond to 0h IST on the given date

  return Mjd;
}
/***************MJD END ***/


/************ TRACK COMMAND *****/
int TrkCmd(int* trkcnt_ptr)
{
  time_t t1;
  struct tm localtm;
  double hourAngle, rightAscension, declinaison;
  
  printf("##### TrkCmd() #####\n");

  if (*trkcnt_ptr == 0) {
    time(&t1); LastTrk = t1;
    t1 += TRKINTERVAL;
   fprintf(stderr,"1st Trk op \n");
  }
  else if (*trkcnt_ptr == 1) {
    t1 = LastTrk;
    t1 += 2*TRKINTERVAL;
   fprintf(stderr,"2nd Trk op \n");
  }
  else {
    time(&t1);
    if ((t1-LastTrk) < TRKINTERVAL) return 0;
    LastTrk = t1;
    t1 += 2*TRKINTERVAL;
    fprintf(stderr,"next trk op\n");
  }
  localtime_r(&t1, &localtm);

  GetSrcCoord(&rightAscension, &declinaison, localtm); 
  fprintf(stderr,"ra ##### %1f  dec######### %1f \n",rightAscension ,declinaison);
  hourAngle = GetHA(localtm, rightAscension);
  Elevation = asin(sin(Latitude)*sin(declinaison) + cos(Latitude)*cos(declinaison)*cos(hourAngle));

  // atan2 and not atan for proper [-Pi, Pi] value, keep proper numerator sign
  Azimuth = atan2(-cos(declinaison)*sin(hourAngle), -sin(Latitude)*cos(declinaison)*cos(hourAngle) + cos(Latitude)*sin(declinaison));
  //Astro Az -> Ant Az:
  Azimuth += M_PI;
  if (Azimuth > + 3.*M_PI/2.) Azimuth -= +2.*M_PI;
  if ((Azimuth > M_PI/2.) && (OutTrack == 0)) Azimuth -= 2.*M_PI;          //go to inner
  else if ((Azimuth < -M_PI/2.) && (OutTrack == 1)) Azimuth += 2.*M_PI;      //go to outter

   fprintf(stderr,"Az=> %1f  El=>%1f\n",Azimuth,Elevation);
  if (Elevation < 0)
   {
     fprintf(stderr,"Wrong source (EL<0)\n"); 
     return -1;
   }
  SendTrkCmd(localtm);
  (*trkcnt_ptr)++;
  return 1;
}

/************TRACK END HERE *******/

/**************** GET SOURCE ****/
void GetSrcCoord(double *raptr, double *decptr, struct tm localtm)
{
  float time;
  time = localtm.tm_hour + localtm.tm_min/60.0 + localtm.tm_sec/3600.0;   
  *raptr = RArad + RArate*M_PI/180.*(time-Timrate);
  *decptr = DECrad + DECrate*M_PI/180.*(time-Timrate);
   fprintf(stderr,"RAPTR=> %1f  DECPTR=>%1f\n",*raptr,*decptr);
}
/*****************GET SOURCE END HERE ****/

/*********** GET HA *****/
double GetHA(struct tm localtm, double rightAscension) 
{
  double lst, time, tmp;
  int lstH[3];

  time = (localtm.tm_hour + localtm.tm_min/60.0 + localtm.tm_sec/3600.0)/24.0;
  lst = Lmst(time);
 fprintf(stderr,"##### LST %1f\n",lst);
  tmp = lst*12/M_PI;
  lstH[0] = (int)tmp;
  tmp = 60*(tmp - (int)tmp);
  lstH[1] = (int)tmp;
  tmp = 60*(tmp - (int)tmp);
  lstH[2] = (int)tmp;

  printf("LST calculation ===> lstH[%d],lstH[%d],lstH[%d]\n",lstH[0],lstH[1],lstH[2]);
  return (lst - rightAscension);
}

/*********************** GET HA END HERE *******/


/********************** LST ********/
double Lmst(double time)  //local mean sideral time
{
  double ut, tu, res, lmstime;
  float Longitude = -74;
  ut = Mjd + time;
  tu = (ut - 51544.5) / 36525.;  // centuries since J2000
  res = ut - Longitude/360. ; res = res - floor(res) ;     //longitude

  lmstime = res + (((0.093104 - tu * 6.2e-6) * tu
                  + 8640184.812866) * tu + 24110.54841)/86400.0 ;
  lmstime = (lmstime - floor(lmstime))*2.0 * M_PI ;
  return lmstime;
}
/*********************** LST END HERE *****/


/*********************** SEND TARCk COMMAND *****/
void SendTrkCmd(struct tm localtm)
{
  char *buf,*buf1,*tbuf;
  servocmd *a1;
  a1 = malloc(sizeof(servocmd));
  buf = (char *)malloc(sizeof(200));
  buf1= (char *)malloc(sizeof(200));
  tbuf= (char *)malloc(sizeof(200));

  sprintf((char *)tbuf,"%02d:%02d:%02d", localtm.tm_hour, localtm.tm_min, localtm.tm_sec);
  // Form command here in a buffer which will look like TRACK command to servo like Ax,time,ang1,ang2
  ConvertAng(Azimuth,buf,1);
  ConvertAng(Elevation,buf1,0);

  a1->seq= 11;
  strcpy(a1->system_name,"servo"); 
  strcpy(a1->op_name,"track"); 
  //  sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x44");// Command ID 44
  a1->number_param=4;
  strcpy(a1->para_name[0],"ax");
  strcpy(a1->para_value[0],"B");
                  
                   strcpy(a1->para_name[1],"time"); // Duration for tracking the source
                   strcpy(a1->para_value[1],tbuf);
                  
                   strcpy(a1->para_name[2],"ang1");
                   strcpy(a1->para_value[2],buf);
                   strcpy(a1->para_name[3],"ang2");
                   strcpy(a1->para_value[3],buf1);
                   //fprintf(stderr,"********** %s\n",a1->SRVCMD.op_name);  
  #ifdef DEBUG 
		printservocmd(a1);
  #endif

 //fprintf(stderr,"Trck mode: send\n");   
}
/************************ END HERE ***********/

/**** CONVERRT ANGLE for Adding the offset *****/

void ConvertAng(double angle, unsigned char *param, int az)
{
  int sgn=0, var[3];

  angle *= 180./M_PI; 
  if (az) {
    angle += AzOffset; 
    fprintf(stderr,"trk az %1f\n",angle);
    //fprintf(stderr," AFter tRK ######\n");
   }
  else {
       // fprintf(stderr," in EL LOOP ######\n");
     angle += ElOffset;
     fprintf(stderr,"trk EL %1f\n",angle); 
  }
  if (angle < 0) {sgn = 1; angle = -angle;}
  var[0] = (int) angle;
  angle = (angle - var[0])*60.;
  var[1] = (int) angle;
  angle = (angle - var[1])*60.;
  var[2] = (int) angle;

  if (sgn == 0) sprintf((char *)param, "+%03d:%02d:%02d", var[0], var[1], var[2]);
  else sprintf((char *)param, "-%03d:%02d:%02d", var[0], var[1], var[2]);
  return;
}
/**************************** END hERE ****/
int main()
{

 // char ra0[20]="05h31m30.00s", dec0[20]="-21d58'0.00", buff[200];
   // TRKON routine to calculate RA/DEC from Source 
   pthread_t servo_th;
   char ra0[20]="123h48m27.45s", dec0[20]="+64d23'37.0";
   float ra[3], dec[3], rarad, decrad;
  sscanf(ra0, "%fh%fm%fs", &ra[0], &ra[1], &ra[2]);
  sscanf(dec0, "%fd%f\'%f\"", &dec[0], &dec[1], &dec[2]);
  //cout << "test: " << ra0 << " " << dec0 << endl;
  rarad = (ra[0] + ra[1]/60. + ra[2]/3600.)*M_PI/12.;           // 12 h - PI rad - 180 deg
  decrad = (dec[0] + dec[1]/60. + dec[2]/3600.)*M_PI/180.;
 fprintf(stderr,"RD DEC values %f %f\n",rarad,decrad);
  RArad = rarad;
  DECrad = decrad;
/* TRK RATE ROUTINE */
   char buf[10], str[5];
   float fbuf;
   int i;
fprintf(stderr," RA rate ('/m):");
    scanf("%f", &fbuf);  
  
  fbuf *= 60;  // deg/hour
fprintf(stderr,"RA in deg is %f\n",fbuf);
   RArate=fbuf;
  fprintf(stderr," DEC rate ('/m):");
     scanf("%f",&fbuf); 
 
  fbuf *= 60;
 fprintf(stderr,"DEC in deg is %f\n",fbuf);
    DECrate=fbuf;
fprintf(stderr,"Time ref t0 (hh:mm:ss):");
 scanf("%s",buf);
 
  for (i=0;i<2;i++) str[i] = buf[i];
  str[3] = '\0'; fbuf = atol(str);
 // fprintf(stderr,"TIME REF in HR %f\n",fbuf);
  for (i=0;i<2;i++) str[i] = buf[i+3];
  str[3] = '\0'; fbuf += atol(str)/60;
  //fprintf(stderr,"TIME REF In MIN %f\n",fbuf);
  for (i=0;i<2;i++) str[i] = buf[i+6];
  str[3] = '\0'; fbuf += atol(str)/3600;
  fprintf(stderr,"TIME REF in %f\n",fbuf);
  Timrate = fbuf;

 /* TRKSET ROUTINE *****/ 

  char buff[200],buffer[200];  
  int var[3], ant, antbuf;
  float ffbuf;
  strcpy(buff,"+000:00:00");
  sscanf(buff, "%d:%d:%d", &var[0], &var[1], &var[2]);     // az offset (+/-ddd:mm:ss)
  if (var[0] < 0) {var[1] = -var[1]; var[2] = -var[2];}
  ffbuf = var[0] + var[1]/60. + var[2]/3600.;
  fprintf(stderr,"AZ offset =>%f\n",ffbuf);
  AzOffset = ffbuf;
  strcpy(buff,"+000:00:00");
  sscanf(buff, "%d:%d:%d", &var[0], &var[1], &var[2]);     // el offset (+/-ddd:mm:ss)
  if (var[0] < 0) {var[1] = -var[1]; var[2] = -var[2];}
  ffbuf = var[0] + var[1]/60. + var[2]/3600.;
   fprintf(stderr,"EL offset =>%f\n",ffbuf);
    ElOffset = ffbuf;
   ffbuf=19.0927;
  ffbuf = ffbuf * M_PI / 180.;     // latitude in rad
  fprintf(stderr,"LATITUDE in RAD  =>%f\n",ffbuf);
   Latitude = ffbuf;
   ffbuf=-74.0536;      // longitude        
  fprintf(stderr,"LONGTITUDE  =>%f\n",ffbuf);
  Longitude = ffbuf;


  Mjd = Elevation = Azimuth = 0;
  TrkCount = -1;  
  TrackFlag = 0; // Servo track on or off // Track on & Track off by this value.
  OutTrack = 0;  // Inner Track or Outer track 

  pthread_create(&servo_th,NULL,&servo,NULL); 

  while(1)
  {
     fprintf(stderr,"Enter command\n");
      scanf("%s",buffer);
     if(!strcasecmp(buffer,"trkon"))
       {TrackFlag=1;}
    else if(!strcasecmp(buffer,"trkoff"))
       {TrackFlag=0;}
    else if(!strcasecmp(buffer,"goin"))
        {OutTrack=0;}
    else if(!strcasecmp(buffer,"goout"))
        {OutTrack=1;} 
    else
     fprintf(stderr,"NOT RELEVANT Command\n");
   }

 return 0;
}

