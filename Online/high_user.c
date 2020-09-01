#include"high_user.h"
#include"server.h"
#include"system.h"
#include"queue.h"
#include"servo.h"
#include"servo_queue.h"
#include"trackservo.h"
#include"das.h"
#include"fps.h"
void antenna_list(int i)
{
  
   switch(i)
   {
     case C00: printf("C00 ANTENNA\n");break;
     case C01: printf("C01 ANTENNA\n");break;
     case C02: printf("C02 ANTENNA\n");break;
     case C03: printf("C03 ANTENNA\n");break;
     case C04: printf("C04 Antenna \n");break;
     case C05: printf("C05 ANTENNA\n");break;
     case C06: printf("C06 Antenna \n");break;
     case C08: printf("C08 ANTENNA\n");break;
     case C09: printf("C09 Antenna\n");break;
     case C10: printf("C10 ANTENNA\n");break;
     case C11: printf("C11ANTENNA\n");break;
     case C12: printf("C12 ANTENNA\n");break;
     case C13: printf("C13 Antenna \n");break;
     case C14: printf("C14 ANTENNA\n");break;
     case E02: printf("E02 Antenna \n");break;
     case E03: printf("E03 Antenna \n");break;
     case E04: printf("E04 Antenna \n");break;
     case E05: printf("E05 Antenna \n");break;
     case E06: printf("E06 Antenna \n");break;
     case S01: printf("S01 Antenna \n");break;
     case S02: printf("S02 Antenna \n");break;
     case S03: printf("S03 Antenna \n");break;
     case S04: printf("S04 Antenna \n");break;
     case S06: printf("S06 Antenna \n");break;
     case W01: printf("W01 Antenna \n");break;
     case W02: printf("W02 Antenna \n");break;
     case W03: printf("W03 Antenna \n");break;
     case W04: printf("W04 Antenna \n");break;
     case W05: printf("W05 Antenna \n");break;
     case W06: printf("W06 Antenna \n");break;
     default : break;
   }
} 

void antenna(int i,char cmd1[][20])
{
   
   ANT_CMD *c1;
   c1= malloc(sizeof(ANT_CMD));

   cmd *a1;
   a1 = malloc(sizeof(cmd));

   SRVANT_CMD *s1;
   s1 = malloc(sizeof(SRVANT_CMD));
   int x, y, pos,setparam,angle;

   static char *servocmd[]={"coldstart","track","hold","position","stop","close","stow","stow_release","abort","resethw",
                          "readangles","readanavar","readdigvar","readsetpara","readantstatus","readversion"};

   static char *fpssyscmd[]= {/* "fpsinit ",*/"loadparam",/*"mvpos",*/"fpsnull","set_tpoint","set_rampdcnt","set_low_rpm",
                              "set_brake_dd","set_rampupcnt", "set_stoptimecnt","set_max_pwm_cnt","set_max_angle",
                             "set_min_angle","read_tpoint","read_rampdcnt","read_low_rpm","read_brake_dd","read_rampupcnt",
                              "read_stoptimecnt","read_max_pwm_cnt","read_max_angle","read_min_angle","read_version",
                        "run_to_cal","free_run_tow","run_to_preset","run_fine_tune","password_run","reboot","fpsstop"};
   switch(i)
   {
     case C00:  fprintf(stderr,"Command for C00 ANTENNA\n");
                strcpy(c1->antenna_name,cmd1[0]);
                fprintf(stderr,"ANTENNA %s %s\n",c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                 fprintf(stderr,"System  %s\n",c1->CMD.system_name);
                 strcpy(c1->CMD.op_name,cmd1[2]);
                 fprintf(stderr,"OP NAME  %s\n",c1->CMD.op_name);
                //if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);
                     }
                     else
                     { fiber_optics(c1); }
                    // pthread_mutex_lock(&lock);
                     senq_store(*c1);
                    // pthread_mutex_unlock(&lock);
                  }        
                   
                /* else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { 
                     fiber_optics(c1);
                     //pthread_mutex_lock(&lock);
                     fiberq_store(*c1);
                    // pthread_mutex_unlock(&lock);
                  } */
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { 
                       front_end(c1);
                      // pthread_mutex_lock(&lock);
                       frontq_store(*c1);
                       //pthread_mutex_unlock(&lock);
                 }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { 
                      back_end(c1);
                      //pthread_mutex_lock(&lock);
                      backq_store(*c1);
                      //pthread_mutex_unlock(&lock); 
                  }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { 
                     self_test(c1); 
                     //pthread_mutex_lock(&lock);
                     selfq_store(*c1);
                     //pthread_mutex_lock(&lock); 
                 }
                  else if(!strcasecmp(c1->CMD.system_name,"fps"))
                 { 
                    for (i = 0; i < FPSEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],fpssyscmd[i]))
                        {
                          strcpy(c1->CMD.system_name,"fps");
                          fps_cmd_list(i,c1,a1);
                          fpsq_store(*c1);
                        }
                      }
                      /* if(!strcasecmp(cmd1[2],"loadparam"))
                        {
                           // Read the FPS.dat file to load param for all 4 feed
                            loadparam();
                          fprintf(stderr,"#### HIGH USER 4 feed =>  %d %d %d %d \n",loadpara[0],loadpara[1],loadpara[2],loadpara[3]);
                        } */
                       if(!strcasecmp(cmd1[2],"mvpos"))
                        {
                           fprintf(stderr,"Enter the feed 610/150/1420/325\n");
                            scanf("%d",&setparam);
                            if(setparam==610)
                           { pos = loadpara[0];} 
                           else if(setparam == 150)
                            {pos = loadpara[1];}
                           else if(setparam == 1420)
                            {pos = loadpara[2];}
                           else if(setparam == 325)
                            {pos = loadpara[3]; }
                              fprintf(stderr,"Selected pos is %d\n",pos);
                             c1->CMD.seq= 32;
                            strcpy(c1->CMD.op_name,"run_to_preset");
                            c1->CMD.number_param=1;
                             strcpy(c1->CMD.parameter_name[0],"tar_encr_v");
                              x = pos/2;
                              y = x & 0x00ff;
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",y);  
                                 x = x >> 8;
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",x);  
                               a1 = &c1->CMD;
                               printcmd(a1);
                               fpsq_store(*c1);
                           } 
                         else if (!strcasecmp(cmd1[2],"fpsinit"))    
                         {
                              c1->CMD.seq= 25;
                              strcpy(c1->CMD.op_name,"read_version"); 
                              c1->CMD.number_param=0; 
                              a1=&c1->CMD;
                              printcmd(a1);          //read version // Insert in the Queue
                              fpsq_store(*c1);

                               angle = 1000/2;                 //counts!
                               x= angle & 0x00ff;
                               y= angle>>8;
                               c1->CMD.seq= 19;
                               c1->CMD.number_param=1;
                               strcpy(c1->CMD.op_name,"set_min_angle");
                               strcpy(c1->CMD.parameter_name[0],"set_min_angle");      //set min angle -16 deg
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                               a1=&c1->CMD;
                               printcmd(a1);  // Insert in the Queue
                               fpsq_store(*c1);

                                angle = 17000/2;
                                c1->CMD.seq= 18;
                                c1->CMD.number_param=1;
                                strcpy(c1->CMD.op_name,"set_Max_angle");
                                strcpy(c1->CMD.parameter_name[0],"set_Max_angle");    //set max angle 270 deg
                                x = angle & 0x00ff;
                                y = angle >> 8;
                                sprintf(c1->CMD.Argument_Ch1[0],"%d",x);                           
                                sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                                a1=&c1->CMD;
                                printcmd(a1);  // Insert in the Queue
                                fpsq_store(*c1);

                               x = 550; y = 0;
                               c1->CMD.seq= 13;
                               strcpy(c1->CMD.op_name,"set_low_rpm"); 
                               c1->CMD.number_param=1;
                               x=(x/5);
                               y= ((int) (y*0.2048*x/1800.0));
                               strcpy(c1->CMD.parameter_name[0],"set_low_rpm");  //set lower rpm limit
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);         //time interval 0?
                               a1=&c1->CMD;
                               printcmd(a1);          // Insert in the Queue 
                               fpsq_store(*c1);                                  
 
                          }
                   }
                 else if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          C00srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
                
                 break;
     case C01:   fprintf(stderr,"Command for C01 ANTENNA\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                  fprintf(stderr,"ANTENNA %s %s\n",c1->antenna_name,cmd1[0]);
                  fprintf(stderr,"System  %s\n",c1->CMD.system_name);
                  fprintf(stderr,"OP NAME  %s\n",c1->CMD.op_name);
               /*    if((!strcasecmp(c1->CMD.system_name,"front_end"))&&(!strcasecmp(c1->CMD.op_name,"mon")))
                    { strcpy(c1->CMD.parameter_name[0],"fe_box");
                        fprintf(stderr,"Enter FE BOX Number\n");
                        scanf("%d",&x);
                        sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                        sprintf(c1->CMD.Argument_Ch2[0],"%d",x); 
                        front_end(c1);c1_frontq_store(*c1); 
                    } */
                /* if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);c1_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);c1_fiberq_store(*c1); } */
                  if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);c1_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1);c1_senq_store(*c1); }
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  {
                     /*  if(!strcasecmp(c1->CMD.op_name,"mon")
                       {
                        strcpy(c1->CMD.parameter_name[0],"fe_box");
                        scanf("%d",&x);
                        sprintf(a1->CMD.Argument_Ch1[0],"%d",x);
                        sprintf(a1->CMD.Argument_Ch2[0],"%d",x); 
                       } */
                                   
                     front_end(c1);c1_frontq_store(*c1); 
                   }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); c1_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); c1_selfq_store(*c1);}
                  else if(!strcasecmp(c1->CMD.system_name,"fps"))
                 { 
                    for (i = 0; i < FPSEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],fpssyscmd[i]))
                        {
                          strcpy(c1->CMD.system_name,"fps");
                          fps_cmd_list(i,c1,a1);
                          c1_fpsq_store(*c1);
                        }
                      }
                      /* if(!strcasecmp(cmd1[2],"loadparam"))
                        {
                           // Read the FPS.dat file to load param for all 4 feed
                            loadparam();
                          fprintf(stderr,"#### HIGH USER 4 feed =>  %d %d %d %d \n",loadpara[0],loadpara[1],loadpara[2],loadpara[3]);
                        } */
                       if(!strcasecmp(cmd1[2],"mvpos"))
                        {
                           fprintf(stderr,"Enter the feed 610/150/1420/325\n");
                            scanf("%d",&setparam);
                            if(setparam==610)
                           { pos = loadpara[0];} 
                           else if(setparam == 150)
                            {pos = loadpara[1];}
                           else if(setparam == 1420)
                            {pos = loadpara[2];}
                           else if(setparam == 325)
                            {pos = loadpara[3]; }
                              fprintf(stderr,"Selected pos is %d\n",pos);
                             c1->CMD.seq= 32;
                            strcpy(c1->CMD.op_name,"run_to_preset");
                            c1->CMD.number_param=1;
                             strcpy(c1->CMD.parameter_name[0],"tar_encr_v");
                              x = pos/2;
                              y = x & 0x00ff;
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",y);  
                                 x = x >> 8;
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",x);  
                               a1 = &c1->CMD;
                               printcmd(a1);
                               c1_fpsq_store(*c1);
                           } 
                         else if (!strcasecmp(cmd1[2],"fpsinit"))    
                         {
                              c1->CMD.seq= 25;
                              strcpy(c1->CMD.op_name,"read_version"); 
                              c1->CMD.number_param=0; 
                              a1=&c1->CMD;
                              printcmd(a1);          //read version // Insert in the Queue
                              c1_fpsq_store(*c1);

                               angle = 1000/2;                 //counts!
                               x= angle & 0x00ff;
                               y= angle>>8;
                               c1->CMD.seq= 19;
                               c1->CMD.number_param=1;
                               strcpy(c1->CMD.op_name,"set_min_angle");
                               strcpy(c1->CMD.parameter_name[0],"set_min_angle");      //set min angle -16 deg
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                               a1=&c1->CMD;
                               printcmd(a1);  // Insert in the Queue
                               c1_fpsq_store(*c1);

                                angle = 17000/2;
                                c1->CMD.seq= 18;
                                c1->CMD.number_param=1;
                                strcpy(c1->CMD.op_name,"set_Max_angle");
                                strcpy(c1->CMD.parameter_name[0],"set_Max_angle");    //set max angle 270 deg
                                x = angle & 0x00ff;
                                y = angle >> 8;
                                sprintf(c1->CMD.Argument_Ch1[0],"%d",x);                           
                                sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                                a1=&c1->CMD;
                                printcmd(a1);  // Insert in the Queue
                                c1_fpsq_store(*c1);

                               x = 550; y = 0;
                               c1->CMD.seq= 13;
                               strcpy(c1->CMD.op_name,"set_low_rpm"); 
                               c1->CMD.number_param=1;
                               x=(x/5);
                               y= ((int) (y*0.2048*x/1800.0));
                               strcpy(c1->CMD.parameter_name[0],"set_low_rpm");  //set lower rpm limit
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);         //time interval 0?
                               a1=&c1->CMD;
                               printcmd(a1);          // Insert in the Queue 
                               c1_fpsq_store(*c1);                                  
 
                          }
                   }
                 //fprintf(stderr," Storing in Queue #####\n");
                // q1_store(*c1);
               break;
     case C02: printf("C02 ANTENNA\n");
               strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
               /* if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);c2_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);c2_fiberq_store(*c1); } */
                    if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);c2_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1);c2_senq_store(*c1); }
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);c2_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); c2_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); c2_selfq_store(*c1);}
                   else if(!strcasecmp(c1->CMD.system_name,"fps"))
                 { 
                    for (i = 0; i < FPSEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],fpssyscmd[i]))
                        {
                          strcpy(c1->CMD.system_name,"fps");
                          fps_cmd_list(i,c1,a1);
                          c2_fpsq_store(*c1);
                        }
                      }
                      /* if(!strcasecmp(cmd1[2],"loadparam"))
                        {
                           // Read the FPS.dat file to load param for all 4 feed
                            loadparam();
                          fprintf(stderr,"#### HIGH USER 4 feed =>  %d %d %d %d \n",loadpara[0],loadpara[1],loadpara[2],loadpara[3]);
                        } */
                       if(!strcasecmp(cmd1[2],"mvpos"))
                        {
                           fprintf(stderr,"Enter the feed 610/150/1420/325\n");
                            scanf("%d",&setparam);
                            if(setparam==610)
                           { pos = loadpara[0];} 
                           else if(setparam == 150)
                            {pos = loadpara[1];}
                           else if(setparam == 1420)
                            {pos = loadpara[2];}
                           else if(setparam == 325)
                            {pos = loadpara[3]; }
                              fprintf(stderr,"Selected pos is %d\n",pos);
                             c1->CMD.seq= 32;
                            strcpy(c1->CMD.op_name,"run_to_preset");
                            c1->CMD.number_param=1;
                             strcpy(c1->CMD.parameter_name[0],"tar_encr_v");
                              x = pos/2;
                              y = x & 0x00ff;
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",y);  
                                 x = x >> 8;
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",x);  
                               a1 = &c1->CMD;
                               printcmd(a1);
                               c2_fpsq_store(*c1);
                           } 
                         else if (!strcasecmp(cmd1[2],"fpsinit"))    
                         {
                              c1->CMD.seq= 25;
                              strcpy(c1->CMD.op_name,"read_version"); 
                              c1->CMD.number_param=0; 
                              a1=&c1->CMD;
                              printcmd(a1);          //read version // Insert in the Queue
                              c2_fpsq_store(*c1);

                               angle = 1000/2;                 //counts!
                               x= angle & 0x00ff;
                               y= angle>>8;
                               c1->CMD.seq= 19;
                               c1->CMD.number_param=1;
                               strcpy(c1->CMD.op_name,"set_min_angle");
                               strcpy(c1->CMD.parameter_name[0],"set_min_angle");      //set min angle -16 deg
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                               a1=&c1->CMD;
                               printcmd(a1);  // Insert in the Queue
                               c2_fpsq_store(*c1);

                                angle = 17000/2;
                                c1->CMD.seq= 18;
                                c1->CMD.number_param=1;
                                strcpy(c1->CMD.op_name,"set_Max_angle");
                                strcpy(c1->CMD.parameter_name[0],"set_Max_angle");    //set max angle 270 deg
                                x = angle & 0x00ff;
                                y = angle >> 8;
                                sprintf(c1->CMD.Argument_Ch1[0],"%d",x);                           
                                sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                                a1=&c1->CMD;
                                printcmd(a1);  // Insert in the Queue
                                c2_fpsq_store(*c1);

                               x = 550; y = 0;
                               c1->CMD.seq= 13;
                               strcpy(c1->CMD.op_name,"set_low_rpm"); 
                               c1->CMD.number_param=1;
                               x=(x/5);
                               y= ((int) (y*0.2048*x/1800.0));
                               strcpy(c1->CMD.parameter_name[0],"set_low_rpm");  //set lower rpm limit
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);         //time interval 0?
                               a1=&c1->CMD;
                               printcmd(a1);          // Insert in the Queue 
                               c2_fpsq_store(*c1);                                  
 
                          }
                   }
               break;
     case C03: printf("C03 ANTENNA\n");
               strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
               /* if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);c3_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);c3_fiberq_store(*c1); } */
                  if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);c3_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1); c3_senq_store(*c1);}
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);c3_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); c3_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); c3_selfq_store(*c1);}
                   else if(!strcasecmp(c1->CMD.system_name,"fps"))
                 { 
                    for (i = 0; i < FPSEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],fpssyscmd[i]))
                        {
                          strcpy(c1->CMD.system_name,"fps");
                          fps_cmd_list(i,c1,a1);
                          c3_fpsq_store(*c1);
                        }
                      }
                      /* if(!strcasecmp(cmd1[2],"loadparam"))
                        {
                           // Read the FPS.dat file to load param for all 4 feed
                            loadparam();
                          fprintf(stderr,"#### HIGH USER 4 feed =>  %d %d %d %d \n",loadpara[0],loadpara[1],loadpara[2],loadpara[3]);
                        } */
                       if(!strcasecmp(cmd1[2],"mvpos"))
                        {
                           fprintf(stderr,"Enter the feed 610/150/1420/325\n");
                            scanf("%d",&setparam);
                            if(setparam==610)
                           { pos = loadpara[0];} 
                           else if(setparam == 150)
                            {pos = loadpara[1];}
                           else if(setparam == 1420)
                            {pos = loadpara[2];}
                           else if(setparam == 325)
                            {pos = loadpara[3]; }
                              fprintf(stderr,"Selected pos is %d\n",pos);
                             c1->CMD.seq= 32;
                            strcpy(c1->CMD.op_name,"run_to_preset");
                            c1->CMD.number_param=1;
                             strcpy(c1->CMD.parameter_name[0],"tar_encr_v");
                              x = pos/2;
                              y = x & 0x00ff;
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",y);  
                                 x = x >> 8;
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",x);  
                               a1 = &c1->CMD;
                               printcmd(a1);
                               c3_fpsq_store(*c1);
                           } 
                         else if (!strcasecmp(cmd1[2],"fpsinit"))    
                         {
                              c1->CMD.seq= 25;
                              strcpy(c1->CMD.op_name,"read_version"); 
                              c1->CMD.number_param=0; 
                              a1=&c1->CMD;
                              printcmd(a1);          //read version // Insert in the Queue
                              c3_fpsq_store(*c1);

                               angle = 1000/2;                 //counts!
                               x= angle & 0x00ff;
                               y= angle>>8;
                               c1->CMD.seq= 19;
                               c1->CMD.number_param=1;
                               strcpy(c1->CMD.op_name,"set_min_angle");
                               strcpy(c1->CMD.parameter_name[0],"set_min_angle");      //set min angle -16 deg
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                               a1=&c1->CMD;
                               printcmd(a1);  // Insert in the Queue
                               c3_fpsq_store(*c1);

                                angle = 17000/2;
                                c1->CMD.seq= 18;
                                c1->CMD.number_param=1;
                                strcpy(c1->CMD.op_name,"set_Max_angle");
                                strcpy(c1->CMD.parameter_name[0],"set_Max_angle");    //set max angle 270 deg
                                x = angle & 0x00ff;
                                y = angle >> 8;
                                sprintf(c1->CMD.Argument_Ch1[0],"%d",x);                           
                                sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                                a1=&c1->CMD;
                                printcmd(a1);  // Insert in the Queue
                                c3_fpsq_store(*c1);

                               x = 550; y = 0;
                               c1->CMD.seq= 13;
                               strcpy(c1->CMD.op_name,"set_low_rpm"); 
                               c1->CMD.number_param=1;
                               x=(x/5);
                               y= ((int) (y*0.2048*x/1800.0));
                               strcpy(c1->CMD.parameter_name[0],"set_low_rpm");  //set lower rpm limit
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);         //time interval 0?
                               a1=&c1->CMD;
                               printcmd(a1);          // Insert in the Queue 
                               c3_fpsq_store(*c1);                                  
 
                          }
                   }
               break;
     case C04:printf("C04 Antenna \n");
              strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
               /* if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);c4_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);c4_fiberq_store(*c1); } */
                  if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);c4_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1); c4_senq_store(*c1);}
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);c4_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); c4_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); c4_selfq_store(*c1);}
                   else if(!strcasecmp(c1->CMD.system_name,"fps"))
                 { 
                    for (i = 0; i < FPSEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],fpssyscmd[i]))
                        {
                          strcpy(c1->CMD.system_name,"fps");
                          fps_cmd_list(i,c1,a1);
                          c4_fpsq_store(*c1);
                        }
                      }
                      /* if(!strcasecmp(cmd1[2],"loadparam"))
                        {
                           // Read the FPS.dat file to load param for all 4 feed
                            loadparam();
                          fprintf(stderr,"#### HIGH USER 4 feed =>  %d %d %d %d \n",loadpara[0],loadpara[1],loadpara[2],loadpara[3]);
                        } */
                       if(!strcasecmp(cmd1[2],"mvpos"))
                        {
                           fprintf(stderr,"Enter the feed 610/150/1420/325\n");
                            scanf("%d",&setparam);
                            if(setparam==610)
                           { pos = loadpara[0];} 
                           else if(setparam == 150)
                            {pos = loadpara[1];}
                           else if(setparam == 1420)
                            {pos = loadpara[2];}
                           else if(setparam == 325)
                            {pos = loadpara[3]; }
                              fprintf(stderr,"Selected pos is %d\n",pos);
                             c1->CMD.seq= 32;
                            strcpy(c1->CMD.op_name,"run_to_preset");
                            c1->CMD.number_param=1;
                             strcpy(c1->CMD.parameter_name[0],"tar_encr_v");
                              x = pos/2;
                              y = x & 0x00ff;
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",y);  
                                 x = x >> 8;
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",x);  
                               a1 = &c1->CMD;
                               printcmd(a1);
                               c4_fpsq_store(*c1);
                           } 
                         else if (!strcasecmp(cmd1[2],"fpsinit"))    
                         {
                              c1->CMD.seq= 25;
                              strcpy(c1->CMD.op_name,"read_version"); 
                              c1->CMD.number_param=0; 
                              a1=&c1->CMD;
                              printcmd(a1);          //read version // Insert in the Queue
                              c4_fpsq_store(*c1);

                               angle = 1000/2;                 //counts!
                               x= angle & 0x00ff;
                               y= angle>>8;
                               c1->CMD.seq= 19;
                               c1->CMD.number_param=1;
                               strcpy(c1->CMD.op_name,"set_min_angle");
                               strcpy(c1->CMD.parameter_name[0],"set_min_angle");      //set min angle -16 deg
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                               a1=&c1->CMD;
                               printcmd(a1);  // Insert in the Queue
                               c4_fpsq_store(*c1);

                                angle = 17000/2;
                                c1->CMD.seq= 18;
                                c1->CMD.number_param=1;
                                strcpy(c1->CMD.op_name,"set_Max_angle");
                                strcpy(c1->CMD.parameter_name[0],"set_Max_angle");    //set max angle 270 deg
                                x = angle & 0x00ff;
                                y = angle >> 8;
                                sprintf(c1->CMD.Argument_Ch1[0],"%d",x);                           
                                sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                                a1=&c1->CMD;
                                printcmd(a1);  // Insert in the Queue
                                c4_fpsq_store(*c1);

                               x = 550; y = 0;
                               c1->CMD.seq= 13;
                               strcpy(c1->CMD.op_name,"set_low_rpm"); 
                               c1->CMD.number_param=1;
                               x=(x/5);
                               y= ((int) (y*0.2048*x/1800.0));
                               strcpy(c1->CMD.parameter_name[0],"set_low_rpm");  //set lower rpm limit
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);         //time interval 0?
                               a1=&c1->CMD;
                               printcmd(a1);          // Insert in the Queue 
                               c4_fpsq_store(*c1);                                  
 
                          }
                   }
              break;
     case C05: printf("C05 ANTENNA\n");
               strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
               /* if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);c5_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);c5_fiberq_store(*c1); }*/
                   if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);c5_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1); c5_senq_store(*c1);}
                    // pthread_mutex_lock(&lock);
                     
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);c5_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); c5_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); c5_selfq_store(*c1);}
                   else if(!strcasecmp(c1->CMD.system_name,"fps"))
                 { 
                    for (i = 0; i < FPSEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],fpssyscmd[i]))
                        {
                          strcpy(c1->CMD.system_name,"fps");
                          fps_cmd_list(i,c1,a1);
                          c5_fpsq_store(*c1);
                        }
                      }
                      /* if(!strcasecmp(cmd1[2],"loadparam"))
                        {
                           // Read the FPS.dat file to load param for all 4 feed
                            loadparam();
                          fprintf(stderr,"#### HIGH USER 4 feed =>  %d %d %d %d \n",loadpara[0],loadpara[1],loadpara[2],loadpara[3]);
                        } */
                       if(!strcasecmp(cmd1[2],"mvpos"))
                        {
                           fprintf(stderr,"Enter the feed 610/150/1420/325\n");
                            scanf("%d",&setparam);
                            if(setparam==610)
                           { pos = loadpara[0];} 
                           else if(setparam == 150)
                            {pos = loadpara[1];}
                           else if(setparam == 1420)
                            {pos = loadpara[2];}
                           else if(setparam == 325)
                            {pos = loadpara[3]; }
                              fprintf(stderr,"Selected pos is %d\n",pos);
                             c1->CMD.seq= 32;
                            strcpy(c1->CMD.op_name,"run_to_preset");
                            c1->CMD.number_param=1;
                             strcpy(c1->CMD.parameter_name[0],"tar_encr_v");
                              x = pos/2;
                              y = x & 0x00ff;
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",y);  
                                 x = x >> 8;
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",x);  
                               a1 = &c1->CMD;
                               printcmd(a1);
                               c5_fpsq_store(*c1);
                           } 
                         else if (!strcasecmp(cmd1[2],"fpsinit"))    
                         {
                              c1->CMD.seq= 25;
                              strcpy(c1->CMD.op_name,"read_version"); 
                              c1->CMD.number_param=0; 
                              a1=&c1->CMD;
                              printcmd(a1);          //read version // Insert in the Queue
                              c5_fpsq_store(*c1);

                               angle = 1000/2;                 //counts!
                               x= angle & 0x00ff;
                               y= angle>>8;
                               c1->CMD.seq= 19;
                               c1->CMD.number_param=1;
                               strcpy(c1->CMD.op_name,"set_min_angle");
                               strcpy(c1->CMD.parameter_name[0],"set_min_angle");      //set min angle -16 deg
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                               a1=&c1->CMD;
                               printcmd(a1);  // Insert in the Queue
                               c5_fpsq_store(*c1);

                                angle = 17000/2;
                                c1->CMD.seq= 18;
                                c1->CMD.number_param=1;
                                strcpy(c1->CMD.op_name,"set_Max_angle");
                                strcpy(c1->CMD.parameter_name[0],"set_Max_angle");    //set max angle 270 deg
                                x = angle & 0x00ff;
                                y = angle >> 8;
                                sprintf(c1->CMD.Argument_Ch1[0],"%d",x);                           
                                sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                                a1=&c1->CMD;
                                printcmd(a1);  // Insert in the Queue
                                c5_fpsq_store(*c1);

                               x = 550; y = 0;
                               c1->CMD.seq= 13;
                               strcpy(c1->CMD.op_name,"set_low_rpm"); 
                               c1->CMD.number_param=1;
                               x=(x/5);
                               y= ((int) (y*0.2048*x/1800.0));
                               strcpy(c1->CMD.parameter_name[0],"set_low_rpm");  //set lower rpm limit
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);         //time interval 0?
                               a1=&c1->CMD;
                               printcmd(a1);          // Insert in the Queue 
                               c5_fpsq_store(*c1);                                  
 
                          }
                   }
               break;
     case C06: printf("C06 ANTENNA\n");
               strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
               /* if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);c6_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);c6_fiberq_store(*c1); }*/
                  if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);c6_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1); c6_senq_store(*c1);}
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);c6_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); c6_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); c6_selfq_store(*c1);}
                   else if(!strcasecmp(c1->CMD.system_name,"fps"))
                 { 
                    for (i = 0; i < FPSEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],fpssyscmd[i]))
                        {
                          strcpy(c1->CMD.system_name,"fps");
                          fps_cmd_list(i,c1,a1);
                          c6_fpsq_store(*c1);
                        }
                      }
                      /* if(!strcasecmp(cmd1[2],"loadparam"))
                        {
                           // Read the FPS.dat file to load param for all 4 feed
                            loadparam();
                          fprintf(stderr,"#### HIGH USER 4 feed =>  %d %d %d %d \n",loadpara[0],loadpara[1],loadpara[2],loadpara[3]);
                        } */
                       if(!strcasecmp(cmd1[2],"mvpos"))
                        {
                           fprintf(stderr,"Enter the feed 610/150/1420/325\n");
                            scanf("%d",&setparam);
                            if(setparam==610)
                           { pos = loadpara[0];} 
                           else if(setparam == 150)
                            {pos = loadpara[1];}
                           else if(setparam == 1420)
                            {pos = loadpara[2];}
                           else if(setparam == 325)
                            {pos = loadpara[3]; }
                              fprintf(stderr,"Selected pos is %d\n",pos);
                             c1->CMD.seq= 32;
                            strcpy(c1->CMD.op_name,"run_to_preset");
                            c1->CMD.number_param=1;
                             strcpy(c1->CMD.parameter_name[0],"tar_encr_v");
                              x = pos/2;
                              y = x & 0x00ff;
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",y);  
                                 x = x >> 8;
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",x);  
                               a1 = &c1->CMD;
                               printcmd(a1);
                               c6_fpsq_store(*c1);
                           } 
                         else if (!strcasecmp(cmd1[2],"fpsinit"))    
                         {
                              c1->CMD.seq= 25;
                              strcpy(c1->CMD.op_name,"read_version"); 
                              c1->CMD.number_param=0; 
                              a1=&c1->CMD;
                              printcmd(a1);          //read version // Insert in the Queue
                              c6_fpsq_store(*c1);

                               angle = 1000/2;                 //counts!
                               x= angle & 0x00ff;
                               y= angle>>8;
                               c1->CMD.seq= 19;
                               c1->CMD.number_param=1;
                               strcpy(c1->CMD.op_name,"set_min_angle");
                               strcpy(c1->CMD.parameter_name[0],"set_min_angle");      //set min angle -16 deg
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                               a1=&c1->CMD;
                               printcmd(a1);  // Insert in the Queue
                               c6_fpsq_store(*c1);

                                angle = 17000/2;
                                c1->CMD.seq= 18;
                                c1->CMD.number_param=1;
                                strcpy(c1->CMD.op_name,"set_Max_angle");
                                strcpy(c1->CMD.parameter_name[0],"set_Max_angle");    //set max angle 270 deg
                                x = angle & 0x00ff;
                                y = angle >> 8;
                                sprintf(c1->CMD.Argument_Ch1[0],"%d",x);                           
                                sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                                a1=&c1->CMD;
                                printcmd(a1);  // Insert in the Queue
                                c6_fpsq_store(*c1);

                               x = 550; y = 0;
                               c1->CMD.seq= 13;
                               strcpy(c1->CMD.op_name,"set_low_rpm"); 
                               c1->CMD.number_param=1;
                               x=(x/5);
                               y= ((int) (y*0.2048*x/1800.0));
                               strcpy(c1->CMD.parameter_name[0],"set_low_rpm");  //set lower rpm limit
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);         //time interval 0?
                               a1=&c1->CMD;
                               printcmd(a1);          // Insert in the Queue 
                               c6_fpsq_store(*c1);                                  
 
                          }
                   }
               break;
     case C08:printf("C08 Antenna \n");
              strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
              /*  if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);c8_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);c8_fiberq_store(*c1); }*/
                   if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);c8_senq_store(*c1); 
                     }
                     else
                     { fiber_optics(c1);c8_senq_store(*c1);  }
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);c8_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); c8_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); c8_selfq_store(*c1);}
                   else if(!strcasecmp(c1->CMD.system_name,"fps"))
                 { 
                    for (i = 0; i < FPSEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],fpssyscmd[i]))
                        {
                          strcpy(c1->CMD.system_name,"fps");
                          fps_cmd_list(i,c1,a1);
                          c8_fpsq_store(*c1);
                        }
                      }
                      /* if(!strcasecmp(cmd1[2],"loadparam"))
                        {
                           // Read the FPS.dat file to load param for all 4 feed
                            loadparam();
                          fprintf(stderr,"#### HIGH USER 4 feed =>  %d %d %d %d \n",loadpara[0],loadpara[1],loadpara[2],loadpara[3]);
                        } */
                       if(!strcasecmp(cmd1[2],"mvpos"))
                        {
                           fprintf(stderr,"Enter the feed 610/150/1420/325\n");
                            scanf("%d",&setparam);
                            if(setparam==610)
                           { pos = loadpara[0];} 
                           else if(setparam == 150)
                            {pos = loadpara[1];}
                           else if(setparam == 1420)
                            {pos = loadpara[2];}
                           else if(setparam == 325)
                            {pos = loadpara[3]; }
                              fprintf(stderr,"Selected pos is %d\n",pos);
                             c1->CMD.seq= 32;
                            strcpy(c1->CMD.op_name,"run_to_preset");
                            c1->CMD.number_param=1;
                             strcpy(c1->CMD.parameter_name[0],"tar_encr_v");
                              x = pos/2;
                              y = x & 0x00ff;
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",y);  
                                 x = x >> 8;
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",x);  
                               a1 = &c1->CMD;
                               printcmd(a1);
                               c8_fpsq_store(*c1);
                           } 
                         else if (!strcasecmp(cmd1[2],"fpsinit"))    
                         {
                              c1->CMD.seq= 25;
                              strcpy(c1->CMD.op_name,"read_version"); 
                              c1->CMD.number_param=0; 
                              a1=&c1->CMD;
                              printcmd(a1);          //read version // Insert in the Queue
                              c8_fpsq_store(*c1);

                               angle = 1000/2;                 //counts!
                               x= angle & 0x00ff;
                               y= angle>>8;
                               c1->CMD.seq= 19;
                               c1->CMD.number_param=1;
                               strcpy(c1->CMD.op_name,"set_min_angle");
                               strcpy(c1->CMD.parameter_name[0],"set_min_angle");      //set min angle -16 deg
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                               a1=&c1->CMD;
                               printcmd(a1);  // Insert in the Queue
                               c8_fpsq_store(*c1);

                                angle = 17000/2;
                                c1->CMD.seq= 18;
                                c1->CMD.number_param=1;
                                strcpy(c1->CMD.op_name,"set_Max_angle");
                                strcpy(c1->CMD.parameter_name[0],"set_Max_angle");    //set max angle 270 deg
                                x = angle & 0x00ff;
                                y = angle >> 8;
                                sprintf(c1->CMD.Argument_Ch1[0],"%d",x);                           
                                sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                                a1=&c1->CMD;
                                printcmd(a1);  // Insert in the Queue
                                c8_fpsq_store(*c1);

                               x = 550; y = 0;
                               c1->CMD.seq= 13;
                               strcpy(c1->CMD.op_name,"set_low_rpm"); 
                               c1->CMD.number_param=1;
                               x=(x/5);
                               y= ((int) (y*0.2048*x/1800.0));
                               strcpy(c1->CMD.parameter_name[0],"set_low_rpm");  //set lower rpm limit
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);         //time interval 0?
                               a1=&c1->CMD;
                               printcmd(a1);          // Insert in the Queue 
                               c8_fpsq_store(*c1);                                  
 
                          }
                   }
              break;
     case C09: fprintf(stderr,"C09 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          C09srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
               /*  else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);c9_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);c9_fiberq_store(*c1); }*/
                 else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);c9_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1);c9_senq_store(*c1); }
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);c9_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); c9_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); c9_selfq_store(*c1);}
                   else if(!strcasecmp(c1->CMD.system_name,"fps"))
                 { 
                    for (i = 0; i < FPSEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],fpssyscmd[i]))
                        {
                          strcpy(c1->CMD.system_name,"fps");
                          fps_cmd_list(i,c1,a1);
                          c9_fpsq_store(*c1);
                        }
                      }
                      /* if(!strcasecmp(cmd1[2],"loadparam"))
                        {
                           // Read the FPS.dat file to load param for all 4 feed
                            loadparam();
                          fprintf(stderr,"#### HIGH USER 4 feed =>  %d %d %d %d \n",loadpara[0],loadpara[1],loadpara[2],loadpara[3]);
                        } */
                       if(!strcasecmp(cmd1[2],"mvpos"))
                        {
                           fprintf(stderr,"Enter the feed 610/150/1420/325\n");
                            scanf("%d",&setparam);
                            if(setparam==610)
                           { pos = loadpara[0];} 
                           else if(setparam == 150)
                            {pos = loadpara[1];}
                           else if(setparam == 1420)
                            {pos = loadpara[2];}
                           else if(setparam == 325)
                            {pos = loadpara[3]; }
                              fprintf(stderr,"Selected pos is %d\n",pos);
                             c1->CMD.seq= 32;
                            strcpy(c1->CMD.op_name,"run_to_preset");
                            c1->CMD.number_param=1;
                             strcpy(c1->CMD.parameter_name[0],"tar_encr_v");
                              x = pos/2;
                              y = x & 0x00ff;
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",y);  
                                 x = x >> 8;
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",x);  
                               a1 = &c1->CMD;
                               printcmd(a1);
                               c9_fpsq_store(*c1);
                           } 
                         else if (!strcasecmp(cmd1[2],"fpsinit"))    
                         {
                              c1->CMD.seq= 25;
                              strcpy(c1->CMD.op_name,"read_version"); 
                              c1->CMD.number_param=0; 
                              a1=&c1->CMD;
                              printcmd(a1);          //read version // Insert in the Queue
                              c9_fpsq_store(*c1);

                               angle = 1000/2;                 //counts!
                               x= angle & 0x00ff;
                               y= angle>>8;
                               c1->CMD.seq= 19;
                               c1->CMD.number_param=1;
                               strcpy(c1->CMD.op_name,"set_min_angle");
                               strcpy(c1->CMD.parameter_name[0],"set_min_angle");      //set min angle -16 deg
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                               a1=&c1->CMD;
                               printcmd(a1);  // Insert in the Queue
                               c9_fpsq_store(*c1);

                                angle = 17000/2;
                                c1->CMD.seq= 18;
                                c1->CMD.number_param=1;
                                strcpy(c1->CMD.op_name,"set_Max_angle");
                                strcpy(c1->CMD.parameter_name[0],"set_Max_angle");    //set max angle 270 deg
                                x = angle & 0x00ff;
                                y = angle >> 8;
                                sprintf(c1->CMD.Argument_Ch1[0],"%d",x);                           
                                sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                                a1=&c1->CMD;
                                printcmd(a1);  // Insert in the Queue
                                c9_fpsq_store(*c1);

                               x = 550; y = 0;
                               c1->CMD.seq= 13;
                               strcpy(c1->CMD.op_name,"set_low_rpm"); 
                               c1->CMD.number_param=1;
                               x=(x/5);
                               y= ((int) (y*0.2048*x/1800.0));
                               strcpy(c1->CMD.parameter_name[0],"set_low_rpm");  //set lower rpm limit
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);         //time interval 0?
                               a1=&c1->CMD;
                               printcmd(a1);          // Insert in the Queue 
                               c9_fpsq_store(*c1);                                  
 
                          }
                   }
                 break;
            
     case C10: fprintf(stderr,"C10 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          C10srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
                /* else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);c10_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);c10_fiberq_store(*c1); } */
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);c10_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1);c10_senq_store(*c1); }
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);c10_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); c10_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); c10_selfq_store(*c1);}
                   else if(!strcasecmp(c1->CMD.system_name,"fps"))
                 { 
                    for (i = 0; i < FPSEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],fpssyscmd[i]))
                        {
                          strcpy(c1->CMD.system_name,"fps");
                          fps_cmd_list(i,c1,a1);
                          c10_fpsq_store(*c1);
                        }
                      }
                      /* if(!strcasecmp(cmd1[2],"loadparam"))
                        {
                           // Read the FPS.dat file to load param for all 4 feed
                            loadparam();
                          fprintf(stderr,"#### HIGH USER 4 feed =>  %d %d %d %d \n",loadpara[0],loadpara[1],loadpara[2],loadpara[3]);
                        } */
                       if(!strcasecmp(cmd1[2],"mvpos"))
                        {
                           fprintf(stderr,"Enter the feed 610/150/1420/325\n");
                            scanf("%d",&setparam);
                            if(setparam==610)
                           { pos = loadpara[0];} 
                           else if(setparam == 150)
                            {pos = loadpara[1];}
                           else if(setparam == 1420)
                            {pos = loadpara[2];}
                           else if(setparam == 325)
                            {pos = loadpara[3]; }
                              fprintf(stderr,"Selected pos is %d\n",pos);
                             c1->CMD.seq= 32;
                            strcpy(c1->CMD.op_name,"run_to_preset");
                            c1->CMD.number_param=1;
                             strcpy(c1->CMD.parameter_name[0],"tar_encr_v");
                              x = pos/2;
                              y = x & 0x00ff;
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",y);  
                                 x = x >> 8;
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",x);  
                               a1 = &c1->CMD;
                               printcmd(a1);
                               c10_fpsq_store(*c1);
                           } 
                         else if (!strcasecmp(cmd1[2],"fpsinit"))    
                         {
                              c1->CMD.seq= 25;
                              strcpy(c1->CMD.op_name,"read_version"); 
                              c1->CMD.number_param=0; 
                              a1=&c1->CMD;
                              printcmd(a1);          //read version // Insert in the Queue
                              c10_fpsq_store(*c1);

                               angle = 1000/2;                 //counts!
                               x= angle & 0x00ff;
                               y= angle>>8;
                               c1->CMD.seq= 19;
                               c1->CMD.number_param=1;
                               strcpy(c1->CMD.op_name,"set_min_angle");
                               strcpy(c1->CMD.parameter_name[0],"set_min_angle");      //set min angle -16 deg
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                               a1=&c1->CMD;
                               printcmd(a1);  // Insert in the Queue
                               c10_fpsq_store(*c1);

                                angle = 17000/2;
                                c1->CMD.seq= 18;
                                c1->CMD.number_param=1;
                                strcpy(c1->CMD.op_name,"set_Max_angle");
                                strcpy(c1->CMD.parameter_name[0],"set_Max_angle");    //set max angle 270 deg
                                x = angle & 0x00ff;
                                y = angle >> 8;
                                sprintf(c1->CMD.Argument_Ch1[0],"%d",x);                           
                                sprintf(c1->CMD.Argument_Ch2[0],"%d",y);
                                a1=&c1->CMD;
                                printcmd(a1);  // Insert in the Queue
                                c10_fpsq_store(*c1);

                               x = 550; y = 0;
                               c1->CMD.seq= 13;
                               strcpy(c1->CMD.op_name,"set_low_rpm"); 
                               c1->CMD.number_param=1;
                               x=(x/5);
                               y= ((int) (y*0.2048*x/1800.0));
                               strcpy(c1->CMD.parameter_name[0],"set_low_rpm");  //set lower rpm limit
                               sprintf(c1->CMD.Argument_Ch1[0],"%d",x);
                               sprintf(c1->CMD.Argument_Ch2[0],"%d",y);         //time interval 0?
                               a1=&c1->CMD;
                               printcmd(a1);          // Insert in the Queue 
                               c10_fpsq_store(*c1);                                  
 
                          }
                   }
                 break;
     case C11: fprintf(stderr,"C11 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          C11srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
               /*  else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);c11_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);c11_fiberq_store(*c1); }*/
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);c11_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1); c11_senq_store(*c1);}
                    // pthread_mutex_lock(&lock);
                   
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);c11_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); c11_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); c11_selfq_store(*c1);}
                 break;
     case C12: fprintf(stderr,"C12 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          C12srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
                 /* else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);c12_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);c12_fiberq_store(*c1); } */
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);c12_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1); c12_senq_store(*c1);}
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);c12_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); c12_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); c12_selfq_store(*c1);}
                 break;
     case C13: fprintf(stderr,"C13 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          C13srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
                /* else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);c13_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);c13_fiberq_store(*c1); } */
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);c13_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1);c13_senq_store(*c1); }
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);c13_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); c13_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); c13_selfq_store(*c1);}
                 break;
     case C14: fprintf(stderr,"C14 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          C14srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
               /*  else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);c14_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);c14_fiberq_store(*c1); } */
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);c14_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1);c14_senq_store(*c1); }
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);c14_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); c14_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); c14_selfq_store(*c1);}
                 break;
    
     case E02: fprintf(stderr,"E02 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          E02srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
                /* else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);e2_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);e2_fiberq_store(*c1); }*/
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);e2_senq_store(*c1); 
                     }
                     else
                     { fiber_optics(c1);e2_senq_store(*c1);  }
                    // pthread_mutex_lock(&lock);
                     
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);e2_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); e2_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); e2_selfq_store(*c1);}
                 break;
     case E03: fprintf(stderr,"E03 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          E03srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
                 /*  else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);e3_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);e3_fiberq_store(*c1); }*/
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);e3_senq_store(*c1); 
                     }
                     else
                     { fiber_optics(c1);e3_senq_store(*c1);  }
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);e3_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); e3_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); e3_selfq_store(*c1);}
                 break;
     case E04: fprintf(stderr,"E04 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          E04srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
                /*   else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);e4_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);e4_fiberq_store(*c1); } */
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);e4_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1);e4_senq_store(*c1); }
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);e4_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); e4_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); e4_selfq_store(*c1);}
                 break;
     
     case E05: fprintf(stderr,"E05 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          E04srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
                /*   else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);e5_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);e5_fiberq_store(*c1); }*/
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);e5_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1); e5_senq_store(*c1);}
                    // pthread_mutex_lock(&lock);
                   
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);e5_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); e5_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); e5_selfq_store(*c1);}
                 break;
     case E06: fprintf(stderr,"E06 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          E06srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
                /*  else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);e6_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);e6_fiberq_store(*c1); } */
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);e6_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1); e6_senq_store(*c1);}
                    // pthread_mutex_lock(&lock);
                   
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);e6_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); e6_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); e6_selfq_store(*c1);}
                 break;
     case S01: fprintf(stderr,"S01 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          S01srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
                 /* else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);s1_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);s1_fiberq_store(*c1); } */
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);s1_senq_store(*c1); 
                     }
                     else
                     { fiber_optics(c1); s1_senq_store(*c1); }
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);s1_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); s1_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); s1_selfq_store(*c1);}
                 break;
     case S02: fprintf(stderr,"S02 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          S02srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
              /*   else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);s2_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);s2_fiberq_store(*c1); }*/
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);s2_senq_store(*c1); 
                     }
                     else
                     { fiber_optics(c1);s2_senq_store(*c1);  }
                    // pthread_mutex_lock(&lock);
                   
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);s2_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); s2_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); s2_selfq_store(*c1);}
                 break;
     case S03: fprintf(stderr,"S03 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          S03srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
               /*  else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);s3_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);s3_fiberq_store(*c1); }*/
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);s3_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1);s3_senq_store(*c1); }
                    // pthread_mutex_lock(&lock);
                     
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);s3_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); s3_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); s3_selfq_store(*c1);}
                 break;
     case S04: fprintf(stderr,"S04 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          S04srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
               /*  else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);s4_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);s4_fiberq_store(*c1); } */
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);s4_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1);s4_senq_store(*c1); }
                    // pthread_mutex_lock(&lock);
                  
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);s4_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); s4_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); s4_selfq_store(*c1);}
                 break;
     case S06: fprintf(stderr,"S06 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          S06srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
               /*  else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);s6_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);s6_fiberq_store(*c1); } */
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);s6_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1);s6_senq_store(*c1); }
                    // pthread_mutex_lock(&lock);
                   
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);s6_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); s6_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); s6_selfq_store(*c1);}
                 break;
     case W01: fprintf(stderr,"W01 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          W01srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
               /*  else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);w1_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);w1_fiberq_store(*c1); }*/
                   else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);w1_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1);w1_senq_store(*c1); }
                    // pthread_mutex_lock(&lock);
                    
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);w1_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); w1_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); w1_selfq_store(*c1);}
                 break;
     case W02: fprintf(stderr,"W02 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          W02srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
                /*  else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);w2_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);w2_fiberq_store(*c1); }*/
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);w2_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1); w2_senq_store(*c1);}
                    // pthread_mutex_lock(&lock);
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);w2_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); w2_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); w2_selfq_store(*c1);}
                 break;
     case W03: fprintf(stderr,"W03 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          W03srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
                 /*  else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);w3_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);w3_fiberq_store(*c1); }*/
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);w3_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1); w3_senq_store(*c1);}
                    // pthread_mutex_lock(&lock);
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);w3_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); w3_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); w3_selfq_store(*c1);}
                 break;
     case W04: fprintf(stderr,"W04 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          W04srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
               /*   else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);w4_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);w4_fiberq_store(*c1); } */
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);w4_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1); w4_senq_store(*c1);}
                    // pthread_mutex_lock(&lock);
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);w4_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); w4_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); w4_selfq_store(*c1);}
                 break;
     case W05: fprintf(stderr,"W05 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          W05srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
             /*     else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);w5_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);w5_fiberq_store(*c1); }*/
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);w5_senq_store(*c1);
                     }
                     else
                     { fiber_optics(c1);w5_senq_store(*c1); }
                    // pthread_mutex_lock(&lock);
                   
                    // pthread_mutex_unlock(&lock);
                  }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);w5_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); w5_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); w5_selfq_store(*c1);}
                 break;
     case W06: fprintf(stderr,"W06 Antenna\n");
                strcpy(c1->antenna_name,cmd1[0]);
                strcpy(c1->CMD.system_name,cmd1[1]);
                strcpy(c1->CMD.op_name,cmd1[2]);
                if(!strcasecmp(c1->CMD.system_name,"servo"))
                 { 
                    for (i = 0; i < SEND; i++) // For direct command from user
                     {
                         if (!strcasecmp(cmd1[2],servocmd[i]))
                        {
                          strcpy(s1->SRVCMD.system_name,"servo");
                          servo_cmd_list(i,s1);
                          W06srv_store(*s1);
                        }
                     }
                     if(!strcasecmp(cmd1[2],"sendsacsrc"))
                      {
                       fprintf(stderr,"#### Issued sendsacsrc\n"); tracksetpara();
                      } 
                    else if(!strcasecmp(cmd1[2],"goin")) // Tracking routine
                      {fprintf(stderr,"#### Issued Inner track\n");OutTrack=0; }
                    else if(!strcasecmp(cmd1[2],"goout")) 
                      {fprintf(stderr,"#### Issued outer track\n"); OutTrack=1;}
                    else if(!strcasecmp(cmd1[2],"trkon"))
                      {fprintf(stderr,"#### Issued track On command\n");TrackFlag=1; } 
                    else if(!strcasecmp(cmd1[2],"trkoff")) 
                      {fprintf(stderr,"#### Issued track off ( STOP )command\n");TrackFlag=0; }                   
                 }
                 /* else if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                  { sentinel(c1);w6_senq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"fiber_optics"))
                  { fiber_optics(c1);w6_fiberq_store(*c1); }*/
                  else if((!strcasecmp(c1->CMD.system_name,"sentinel"))||(!strcasecmp(c1->CMD.system_name,"fiber_optics")))
                  { 
                     if(!strcasecmp(c1->CMD.system_name,"sentinel"))
                     {
                       sentinel(c1);  w6_senq_store(*c1);                     }
                     else
                     { fiber_optics(c1); w6_senq_store(*c1);}
                   }    
                  else if(!strcasecmp(c1->CMD.system_name,"front_end"))
                  { front_end(c1);w6_frontq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"back_end"))
                  { back_end(c1); w6_backq_store(*c1); }
                 else if(!strcasecmp(c1->CMD.system_name,"self_test"))
                 { self_test(c1); w6_selfq_store(*c1);}
                 break;
     default : break;
   }
}

void userdef(int k,setdata *set)
{
   int i,j;
  /*  setdata *set;  
    set = (setdata *)malloc(sizeof(setdata)); */
   switch(k)
   {
     case create: {printf("CREATE USER\n"); exec(set,k);write_us_shm(set);} break;
     case add: printf(" ADD USER\n");break;
     case cmd2sub: fprintf(stderr,"Command to Antennae in subarray\n");
                     CmdtoSub(set);
                     break;
     case deluser: printf("REMOVE USER\n");break;
     case showuser : fprintf(stderr,"Show user\n");
                     for(i=0;i<MAX_LOOP;i++)
                    {
                      fprintf(stderr,"usernb is %d\n",set->Tx[i].usernb);
                       for(k=0;k<MAX_LOOP;k++)
                      {
                        fprintf(stderr,"Sub ARRAy Number %d\n",set->Tx[i].s_a[k].sub_num);
                        fprintf(stderr,"The Antenna names in your sub Array\n");
                        for(j=0;j<set->Tx[i].s_a[k].num_in_sub;j++)
                         {
                          fprintf(stderr,"%s\n",set->Tx[i].s_a[k].ant_name[j]);
                         }             
                       } 
                     fprintf(stderr," Timestamp=> %s\n",set->Tx[i].timestamp); 
                   }
                    break;
     
     
     default : break;
   }
}

void dasdef(int r)
{
  // int r;
    message_buf sbuf;
    message_buf  rbuf;
    size_t buf_length;
    int ii;
   switch(r)
   {
      case dasinit:fprintf(stderr,"DAS INIT\n");
                  (void) strcpy(sbuf.mtext, "0 0 das init 1 7FFFFFFE F /home/teleset/gsb.hdr"); // Init Command
                   sndmsgq_(&sbuf);
                   break;
      case addp:  fprintf(stderr,"ADD Project\n");
                     ii=1;
                     wrt_hdr(ii);
                    (void) strcpy(sbuf.mtext, "4 1 das addp 1 /home/teleset/Desktop/proj.hdr"); //ADD Project
                     sndmsgq_(&sbuf);
                      break;    
      case startscan:  fprintf(stderr,"DAS START SCAN\n");
                        ii=0;
                        wrt_hdr(ii);
                        (void) strcpy(sbuf.mtext, "4 2 das start /home/teleset/Desktop/scan.hdr"); //Startscan
                        sndmsgq_(&sbuf);
                        break;
      case stopscan:   fprintf(stderr,"DAS STOP SCAN\n");
                       (void)  strcpy(sbuf.mtext, "4 3 das stop");    //   DAS Stop command
                       sndmsgq_(&sbuf); 
                       break;
      case delprj: fprintf(stderr,"Delete Project\n");
                  (void)  strcpy(sbuf.mtext, "4 4 das delp 1");  // Delete project command 
                  sndmsgq_(&sbuf);
                  break;
      case finish : fprintf(stderr,"Finish Project\n");
                   (void)  strcpy(sbuf.mtext, "4 5 das fini 1");  // Finish  command 
                    sndmsgq_(&sbuf);
                    break;
     default : break;
   }
}

void* highuser( void* parameters)
{
  char *us[]={ "create","add","cmd2sub","deluser","showuser"};
  char *das[]={"dasinit","Addp","delprj","startscan","stopscan","finish"};
  static char at_name[32][8] = {"C00","C01","C02","C03","C04","C05","C06","C08","C09","C10","C11","C12","C13","C14","E02"
           ,"E03","E04","E05","E06","S01","S02","S03","S04","S06","W01","W02","W03","W04","W05","W06"}; 
   char *del = " ";
   int i= 0,j;
   char cmd1[10][20];
    setdata *set;  
    set = (setdata *)malloc(sizeof(setdata)); 
   while((name=readline("\n >> "))!=NULL)  
    {
      i=0;
      if (strcmp(name,"stop")==0)
      continue;
      printf("\n");
      if(name)
      {
        pthread_mutex_lock(&lock);
        ret=1;
         token=strtok(name,del);
         while(token !=NULL)
         { 
          // i=0;
          strcpy(cmd1[i],token);
          fprintf(stderr," CMD[%d] => %s\n",i,cmd1[i]);
          i++; 
          no_element = i;
          //fprintf(stderr," Number of Element is %d\n",no_element);
          token =  strtok(NULL," ");
         }
         
        //  for(j=0;j<32;j++)
       //  {
          for (i = 0; i < END; i++) 
         {
           if (!strcasecmp(cmd1[0], at_name[i]))
            {
             //fprintf(stderr,"####### STRING is %s %d\n",cmd[0],i);
              antenna(i,cmd1);
            }
           }
       //  }
      //   for(j=0;j<5;j++)
      //   {
           for(i=0;i<UEND;i++)
          {
            if (!strcasecmp(cmd1[0], us[i]))
            {
              fprintf(stderr,"####### STRING is %s %d\n",cmd1[0],i);
              userdef(i,set);
              bzero(cmd1,sizeof(cmd1));
            }
          }
        // }
        //  for(j=0;j<5;j++)
       //  {
          for(i=0;i<DEND;i++)
         {
            if (!strcasecmp(cmd1[0], das[i]))
             {
             //fprintf(stderr,"####### STRING is %s %d\n",cmd[0],i);
              dasdef(i);
             }
           } 
       //  }
         bzero(name,sizeof(name));
        pthread_mutex_unlock(&lock);
      }
       else
        { ret=0; }
         //usleep(10000);
       if (name[0]!=0)
            add_history(name);
     }
    
   free(name);
   return NULL;
}
/*void* lowuser( void* parameters)
{
  char *del = " ";
  char *das[]={"dasinit","Addp","delprj","startscan","stopscan"};
  static char at_name[32][8] = {"C00","C01","C02","C03","C04","C05","C06","C08","C10","C11","C12","C13","C14","E02"
           ,"E03","E04","E05","E06","S01","S02","S03","S04","S06","W01","W02","W03","W04","W05","W06"}; 
  char *antn[]= {"C00","C01","C02","C03","C04"};
  char *user1[]={ "create","add","cmdtosub","del"};
  char *das[]={"dasinit","Addp","delprj","startscan","stopscan"};



  int i;

  for(;;)
  {
      pthread_mutex_lock(&lock);
      if(ret){
      //i = 0;
       ret=0;
    //  fprintf(stderr,"HIGH USER INPUT ===>%s\n",name);
      token=strtok(name,del);
       while(token !=NULL)
        { 
          strcpy(cmd1[i],token);
          fprintf(stderr," CMD[%d] => %s\n",i,cmd1[i]);
          i++; 
          no_element = i;
          //fprintf(stderr," Number of Element is %d\n",no_element);
          token =  strtok(NULL," ");
        } 
        for (i = 0; i < END; i++) 
        {
           if (!strcasecmp(cmd1[0], at_name[i]))
            {
             //fprintf(stderr,"####### STRING is %s %d\n",cmd[0],i);
              antenna(i);
            }
         }
          for(i=0;i<UEND;i++)
         {
            if (!strcasecmp(cmd1[0], us[i]))
            {
             //fprintf(stderr,"####### STRING is %s %d\n",cmd[0],i);
              userdef(i);
            }
          }
           for(i=0;i<DEND;i++)
         {
            if (!strcasecmp(cmd1[0], das[i]))
            {
             //fprintf(stderr,"####### STRING is %s %d\n",cmd[0],i);
              dasdef(i);
            }
          } 
        
       
      // ret =0;
      //usleep(500);
      }
      pthread_mutex_unlock(&lock);
   }
   return NULL;
} */
