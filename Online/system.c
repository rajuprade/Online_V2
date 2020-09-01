
#include"system.h"

/******* Sentinel *******/
void sentinel(ANT_CMD *a1)
{
   int op;
 /*  char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(a1->CMD->timestamp,tstamp);*/
  // strcpy(a1->CMD->timestamp,stamp1);
     if(!strcasecmp(a1->CMD.op_name,"mon"))
        { op = 0; }
      else if(!strcasecmp(a1->CMD.op_name,"set"))
        { op = 1; }
    else if(!strcasecmp(a1->CMD.op_name,"init"))
        { op = 2; }
      else if(!strcasecmp(a1->CMD.op_name,"reset"))
        { op = 3; }
     else fprintf(stderr," Operation not permitted\n");
   /* printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op); 
    op =1; */
    switch(op)
    {
      case 0:  a1->CMD.seq= 10;
               strcpy( a1->CMD.op_name,"mon");
               a1->CMD.number_param=0;
               break;
      case 1:  a1->CMD.seq= 11;
               strcpy(a1->CMD.op_name,"set");
               a1->CMD.number_param=1;
               strcpy(a1->CMD.parameter_name[0],"dmask");
               strcpy(a1->CMD.Argument_Ch1[0],"ffff");
               strcpy(a1->CMD.Argument_Ch2[0],"5555"); 
               break;
      case 2:  a1->CMD.seq= 12;
               strcpy(a1->CMD.op_name,"init");
               a1->CMD.number_param=0;
               break;
      case 3:  a1->CMD.seq= 13;
               strcpy(a1->CMD.op_name,"reset");
               a1->CMD.number_param=0;
               break;   
    }
     
}

/*********** sentinel ******/


/******* fiber_optics *******/
void fiber_optics(ANT_CMD *a1)
{
   int op;
 /*  time_t t1;
   char stamp1[26];
   time(&t1);
   ctime_r(&t1,stamp1);
   strcpy(a1->CMD->timestamp,stamp1); */
  /*  char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(a1->CMD->timestamp,tstamp);*/
   /* strcpy(a1->CMD.system_name,"fiber_optics");

    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op); */

     if(!strcasecmp(a1->CMD.op_name,"mon"))
        { op = 0; }
      else if(!strcasecmp(a1->CMD.op_name,"set"))
        { op = 1; }
    else if(!strcasecmp(a1->CMD.op_name,"init"))
        { op = 2; }
      else if(!strcasecmp(a1->CMD.op_name,"reset"))
        { op = 3; }
     else fprintf(stderr," Operation not permitted\n");
    switch(op)
    {
      case 0:  a1->CMD.seq= 10;
               strcpy(a1->CMD.op_name,"mon");
               a1->CMD.number_param=0;
               break;

      case 1:  a1->CMD.seq= 11;
               strcpy(a1->CMD.op_name,"set");
               a1->CMD.number_param=1;
               strcpy(a1->CMD.parameter_name[0],"rf_attn");
               strcpy(a1->CMD.Argument_Ch1[0],"25");
               strcpy(a1->CMD.Argument_Ch2[0],"35"); 
               break;

      case 2:  a1->CMD.seq= 12;
               strcpy(a1->CMD.op_name,"init");      
               a1->CMD.number_param=0;
               break;

      case 3:  a1->CMD.seq= 13;
               strcpy(a1->CMD.op_name,"reset");
               a1->CMD.number_param=0;
               break;   
    }
     
}

/************** fiber_optics *****/

/******* back_end *******/
void back_end(ANT_CMD *a1)
{
   int op;
 /*  time_t t1;
   char stamp1[26];
   time(&t1);
   ctime_r(&t1,stamp1);
   strcpy(a1->CMD->timestamp,stamp1); */
  /* char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(a1->CMD->timestamp,tstamp);*/
  /*  strcpy(a1->CMD.system_name,"back_end");

    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op); */
//    op =1;
      if(!strcasecmp(a1->CMD.op_name,"mon"))
        { op = 0; }
      else if(!strcasecmp(a1->CMD.op_name,"set"))
        { op = 1; }
    else if(!strcasecmp(a1->CMD.op_name,"init"))
        { op = 2; }
      else if(!strcasecmp(a1->CMD.op_name,"reset"))
        { op = 3; }
     else fprintf(stderr," Operation not permitted\n");
    switch(op)
    {
      case 0:  a1->CMD.seq= 10;
               strcpy(a1->CMD.op_name,"mon");
               a1->CMD.number_param=0;
               break;

      case 1:  a1->CMD.seq= 11;
               strcpy(a1->CMD.op_name,"set");
               a1->CMD.number_param=9;
                       strcpy(a1->CMD.parameter_name[0],"reflo");
                       strcpy(a1->CMD.parameter_name[1],"lo");
                      // strcpy(a1->CMD.parameter_name[1],"reflo");
                       strcpy(a1->CMD.parameter_name[2],"attn");
                       strcpy(a1->CMD.parameter_name[3],"filter");
                       strcpy(a1->CMD.parameter_name[4],"lpf");
                       strcpy(a1->CMD.parameter_name[5],"source");
                       strcpy(a1->CMD.parameter_name[6],"signal");
                       strcpy(a1->CMD.parameter_name[7],"path");
                       strcpy(a1->CMD.parameter_name[8],"channel");

                       strcpy(a1->CMD.Argument_Ch1[0],"10");
                       strcpy(a1->CMD.Argument_Ch1[1],"800000");
                       strcpy(a1->CMD.Argument_Ch1[2],"10");
                       strcpy(a1->CMD.Argument_Ch1[3],"8");
                       strcpy(a1->CMD.Argument_Ch1[4],"0");
                       strcpy(a1->CMD.Argument_Ch1[5],"siggen");
                       strcpy(a1->CMD.Argument_Ch1[6],"antenna");
                       strcpy(a1->CMD.Argument_Ch1[7],"direct");
                       strcpy(a1->CMD.Argument_Ch1[8],"1");
    
                       strcpy(a1->CMD.Argument_Ch2[0],"10"); 
                       strcpy(a1->CMD.Argument_Ch2[1],"800000");
                       strcpy(a1->CMD.Argument_Ch2[2],"12");
                       strcpy(a1->CMD.Argument_Ch2[3],"6");
                       strcpy(a1->CMD.Argument_Ch2[4],"1");
                       strcpy(a1->CMD.Argument_Ch2[5],"synthesizer");
                       strcpy(a1->CMD.Argument_Ch2[6],"noise");
                       strcpy(a1->CMD.Argument_Ch2[7],"mixer");
                       strcpy(a1->CMD.Argument_Ch2[8],"2");
               break;

      case 2:  a1->CMD.seq= 12;
               strcpy(a1->CMD.op_name,"init");      
               a1->CMD.number_param=0;
               break;

      case 3:  a1->CMD.seq= 13;
               strcpy(a1->CMD.op_name,"reset");
               a1->CMD.number_param=0;
               break;   
    }
     
}

/************** back_end *****/

/******* front_end *******/
void front_end(ANT_CMD *a1)
{
   int op,x,i;
 /*  time_t t1;
   char stamp1[26];
   time(&t1);
   ctime_r(&t1,stamp1);
   strcpy(a1->CMD->timestamp,stamp1); */
  /*  char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(a1->CMD->timestamp,tstamp);*/
    /* strcpy(a1->CMD.system_name,"front_end");
    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op); */
    if(!strcasecmp(a1->CMD.op_name,"mon"))
        { op = 0; }
      else if(!strcasecmp(a1->CMD.op_name,"set"))
        { op = 1; }
    else if(!strcasecmp(a1->CMD.op_name,"init"))
        { op = 2; }
      else if(!strcasecmp(a1->CMD.op_name,"reset"))
        { op = 3; }
     else fprintf(stderr," Operation not permitted\n");
    switch(op)
    {
      case 0:  a1->CMD.seq= 10;
               strcpy(a1->CMD.op_name,"mon");
               a1->CMD.number_param=1;
               strcpy(a1->CMD.parameter_name[0],"fe_box");
                        fprintf(stderr,"Enter FE BOX Number\n");
                        scanf("%d",&x);
                        sprintf(a1->CMD.Argument_Ch1[0],"%d",x);
                        sprintf(a1->CMD.Argument_Ch2[0],"%d",x); 
                 
        for(i=0;i<a1->CMD.number_param;i++)
        {
          printf("%s %s %s\n",a1->CMD.parameter_name[i],a1->CMD.Argument_Ch1[i],a1->CMD.Argument_Ch2[i]);
        } 
               break;

      case 1:  a1->CMD.seq= 11;
               strcpy(a1->CMD.op_name,"set");
               a1->CMD.number_param=8; // changes done as told by NMS => Dt 28/08/2014

                       strcpy(a1->CMD.parameter_name[0],"band_sel");
                       strcpy(a1->CMD.parameter_name[1],"slr_attn");
                       strcpy(a1->CMD.parameter_name[2],"channel");
                       strcpy(a1->CMD.parameter_name[3],"sub_band_sel");
                       strcpy(a1->CMD.parameter_name[4],"rf");
                       strcpy(a1->CMD.parameter_name[5],"cal_ns");
                       strcpy(a1->CMD.parameter_name[6],"walsh");                   
                       strcpy(a1->CMD.parameter_name[7],"wal_val");                  

                       strcpy(a1->CMD.Argument_Ch1[0],"327 MHz");
                       strcpy(a1->CMD.Argument_Ch1[1],"14 dB");
                       strcpy(a1->CMD.Argument_Ch1[2],"SWAP");
                       strcpy(a1->CMD.Argument_Ch1[3],"1060");
                       strcpy(a1->CMD.Argument_Ch1[4],"ON");
                       strcpy(a1->CMD.Argument_Ch1[5],"LOW");
                       strcpy(a1->CMD.Argument_Ch1[6],"ENABLE");   // 1 for walsh enabled 0 => disable                   
                       strcpy(a1->CMD.Argument_Ch1[7],"HIGH");   // 1 => High   0 => Low

                       strcpy(a1->CMD.Argument_Ch2[0],"327 MHz"); 
                       strcpy(a1->CMD.Argument_Ch2[1],"14 dB");
                       strcpy(a1->CMD.Argument_Ch2[2],"UNSWAP");
                       strcpy(a1->CMD.Argument_Ch2[3],"1170");
                       strcpy(a1->CMD.Argument_Ch2[4],"OFF");
                       strcpy(a1->CMD.Argument_Ch2[5],"MED");
                       strcpy(a1->CMD.Argument_Ch2[6],"DISABLE");   // 1 for walsh enabled 0 => disable                   
                       strcpy(a1->CMD.Argument_Ch2[7],"LOW");   // 1 => High   0 => Low
                      
                      
               break;

      case 2:  a1->CMD.seq= 12;
               strcpy(a1->CMD.op_name,"init");      
               a1->CMD.number_param=0;
               break;

      case 3:  a1->CMD.seq= 13;
               strcpy(a1->CMD.op_name,"reset");
               a1->CMD.number_param=0;
               break;   
    }
     
}

/************** front_end *****/

/***************self_test **********/
void self_test(ANT_CMD *a1)
{
   int op;
 /*  time_t t1;
   char stamp1[26];
   time(&t1);
   ctime_r(&t1,stamp1);
   strcpy(a1->CMD->timestamp,stamp1); */
 /*   char *tstamp;
   tstamp = malloc(25);
   tstamp = tp(tstamp);
   strcpy(a1->CMD->timestamp,tstamp); */
   /* strcpy(a1->CMD.system_name,"self_test");

    printf(" Enter operation number 0:mon 1:set 2:init 3:reset\n");
    scanf("%d",&op); */
    if(!strcasecmp(a1->CMD.op_name,"mon"))
        { op = 0; }
      else if(!strcasecmp(a1->CMD.op_name,"set"))
        { op = 1; }
    else if(!strcasecmp(a1->CMD.op_name,"init"))
        { op = 2; }
      else if(!strcasecmp(a1->CMD.op_name,"reset"))
        { op = 3; }
     else fprintf(stderr," Operation not permitted\n");
    switch(op)
    {
      case 0:  a1->CMD.seq= 10;
               strcpy(a1->CMD.op_name,"mon");
               a1->CMD.number_param=0;
               break;

      case 1:  a1->CMD.seq= 11;
               strcpy(a1->CMD.op_name,"set");
               a1->CMD.number_param=3;
               strcpy(a1->CMD.parameter_name[0],"ss");// set spectrum spreader
               strcpy(a1->CMD.Argument_Ch1[0],"0");   // Range : 0,1,2,3
               strcpy(a1->CMD.parameter_name[1],"fdb");// set frequency doubler
               strcpy(a1->CMD.Argument_Ch1[0],"1");   // Range 0 or 1 
               strcpy(a1->CMD.parameter_name[2],"fdv");// set frequency divider
               strcpy(a1->CMD.Argument_Ch1[0],"2");   // Range 1,2,4,6,8   
               break;

      case 2:  a1->CMD.seq= 12;
               strcpy(a1->CMD.op_name,"init");      
               a1->CMD.number_param=0;
               break;

      case 3:  a1->CMD.seq= 13;
               strcpy(a1->CMD.op_name,"reset");
               a1->CMD.number_param=0;
               break;   
    }
     
}


/**************self_test **********/


/******* Feed positioning System *******/
/*
void fps(ANT_CMD *a1)
{
   int op;
     if(!strcasecmp(a1->CMD.op_name,"mon"))
        { op = 0; }
      else if(!strcasecmp(a1->CMD.op_name,"set"))
        { op = 1; }
    else if(!strcasecmp(a1->CMD.op_name,"init"))
        { op = 2; }
      else if(!strcasecmp(a1->CMD.op_name,"reset"))
        { op = 3; }
     else fprintf(stderr," Operation not permitted\n");
    switch(op)
    {
      case 0:  a1->CMD.seq= 10;
               strcpy(a1->CMD.op_name,"mon");
               a1->CMD.number_param=10;
               strcpy(a1->CMD.parameter_name[0],"read_tpoint");  // Read turning point
               strcpy(a1->CMD.parameter_name[1],"read_rampdcnt"); //Read ramp down count
               strcpy(a1->CMD.parameter_name[2],"read_low_rpm");  // Read lower rpm limit
               strcpy(a1->CMD.parameter_name[3],"read_Brake_dd");  // Read brake down diff
               strcpy(a1->CMD.parameter_name[4],"read_rampupcnt");  //Read ramp up count
               strcpy(a1->CMD.parameter_name[5],"read_stoptimecnt");  //Read  stop time count
               strcpy(a1->CMD.parameter_name[6],"read_Max_pwm_cnt"); //Read  MAX PWM count
               strcpy(a1->CMD.parameter_name[7],"read_Max_angle");  // Read MAX angle
               strcpy(a1->CMD.parameter_name[8],"read_Max_angle");  //Read  MIN angle
               strcpy(a1->CMD.parameter_name[9],"read_version");   //Read  version
               break;

      case 1:  a1->CMD.seq= 11;
               strcpy(a1->CMD.op_name,"set");
               a1->CMD.number_param=9;

                       strcpy(a1->CMD.parameter_name[0],"set_tpoint");// set turning point
                       strcpy(a1->CMD.parameter_name[1],"set_rampdcnt");//set ramp down count
                       strcpy(a1->CMD.parameter_name[2],"set_low_rpm");// set lower rpm limit
                       strcpy(a1->CMD.parameter_name[3],"set_Brake_dd");//set brake down diff
                       strcpy(a1->CMD.parameter_name[4],"set_rampupcnt");// set ramp up count
                       strcpy(a1->CMD.parameter_name[5],"set_stoptimecnt");// set stop time count
                       strcpy(a1->CMD.parameter_name[6],"set_Max_pwm_cnt");// set MAX PWM count
                       strcpy(a1->CMD.parameter_name[7],"set_Max_angle");// set MAX angle
                       strcpy(a1->CMD.parameter_name[8],"set_Min_angle");// set MIN angle

                       strcpy(a1->CMD.Argument_Ch1[0],"LO");
                       strcpy(a1->CMD.Argument_Ch1[1],"on");
                       strcpy(a1->CMD.Argument_Ch1[2],"1");
                       strcpy(a1->CMD.Argument_Ch1[3],"1060");
                       strcpy(a1->CMD.Argument_Ch1[4],"50");
                       strcpy(a1->CMD.Argument_Ch1[5],"44");
                       strcpy(a1->CMD.Argument_Ch1[6],"swap");
                       
    
                       strcpy(a1->CMD.Argument_Ch2[0],"Medium"); 
                       strcpy(a1->CMD.Argument_Ch2[1],"off");
                       strcpy(a1->CMD.Argument_Ch2[2],"4");
                       strcpy(a1->CMD.Argument_Ch2[3],"1170");
                       strcpy(a1->CMD.Argument_Ch2[4],"150");
                       strcpy(a1->CMD.Argument_Ch2[5],"30");
                       strcpy(a1->CMD.Argument_Ch2[6],"unswap");
                      
               break;

      case 2:  a1->CMD.seq= 12;
               strcpy(a1->CMD.op_name,"init");      
               a1->CMD.number_param=0;
               break;

      case 3:  a1->CMD.seq= 13;
               strcpy(a1->CMD.op_name,"reset");
               a1->CMD.number_param=0;
               break;   
    }
     
}

*/


/* void exec_cmd(int n,ANT_CMD *a1)
{

   switch(n)
   { 
     case 0:sentinel(a1); break;
     case 1:front_end(a1); break;
     case 2:fiber_optics(a1); break;
     case 3:back_end(a1); break;
     case 4:self_test(a1); break;
     default: break;
   }
} */

