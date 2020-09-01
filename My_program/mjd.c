#include<stdio.h>
#include<time.h>
#include<math.h>
//double Mjd;
double MjdCal(struct tm localtm);
double lmst(double time,double Mjd);
double MjdCal(struct tm localtm) 
{
  int year, month, day;
  double Mjd;

  year = 1900 + localtm.tm_year;
  month = 1 + localtm.tm_mon;
  day = localtm.tm_mday;
  Mjd = (double) ((year - (12 - month) / 10 + 4712L) * 1461L / 4 +
    ((month + 9) % 12 * 306L + 5) / 10 -
    (year - (12 - month) / 10 + 4900L) / 100 * 3 / 4 +
    day - 2399904L);
  Mjd -= 5.5/24.0 ;  // to correspond to 0h IST on the given date

  return Mjd;
}

double lmst(double time,double Mjd)  //local mean sideral time
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


int main(void)
{
   double Mjd;
   time_t t0;
   struct tm localtm0;
   double lst, time1,tmp;
   struct tm localtm;
   int lstH[3];
   time(&t0); 
 //  localtime_r(&t0, &localtm0);
   localtime_r(&t0,&localtm);
   Mjd = MjdCal(localtm);            //routine for midnight crossing?
   printf(" MJD calculation ===> %1f\n",Mjd);

   time1 = (localtm.tm_hour + localtm.tm_min/60.0 + localtm.tm_sec/3600.0)/24.0;
   lst = lmst(time1,Mjd);
   printf(" LST calculation ===> %1f\n",lst);
    tmp = lst*12/M_PI;
    lstH[0] = (int)tmp;
    tmp = 60*(tmp - (int)tmp);
    lstH[1] = (int)tmp;
    tmp = 60*(tmp - (int)tmp);
    lstH[2] = (int)tmp;
   printf("LST calculation ===> lstH[%d],lstH[%d],lstH[%d]\n",lstH[0],lstH[1],lstH[2]);
  
   return 0;
}
