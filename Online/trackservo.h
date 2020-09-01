#ifndef H_TRACKSERVO_H
#define H_TRACKSERVO_H
#include<pthread.h>
// Variables & function for SERVO tracking
#define TRKINTERVAL 30
int TrackFlag, OutTrack, InfoFlag; 
float ElOffset, AzOffset;   // deg
float RArate, DECrate, Timrate;
float Latitude, Longitude, RArad, DECrad; 
double Elevation, Azimuth, Mjd;
time_t LastTrk;
int TrkCount; 

/* extern int TIMEOUTDATA;
extern int TIMEOUTOPE;
extern int TRKINTERVAL;*/

void tracksetpara();
void *trackingservo(void* parameters);
void Run();
void NewTrkCmd();
int TrkCmd(int* trkcnt_ptr);
void SendTrkCmd(struct tm localtm);
double GetHA(struct tm localtm, double rightAscension);
void GetSrcCoord(double *ra, double *dec, struct tm localtm);
double MjdCal(struct tm localtm) ;
double Lmst(double time) ;
void ConvertAng(double angle,unsigned char *param, int az);

#endif //H_SERVO_H
