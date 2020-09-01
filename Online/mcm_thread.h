#ifndef _MCM_THREAD_H
#define _MCM_THREAD_H

#include"server.h"
#include"queue.h"
#include"socket.h"

/* #define SENTINEL_IP "192.168.33.2"
#define FIBER_IP "192.168.31.2"
#define FRONT_IP "192.168.31.3"
#define BACKEND_IP "192.168.31.4"
#define SELF_IP "192.168.31.5"
#define C01_SENTINEL_IP "192.168.32.2"
#define C01_FIBER_IP "192.168.32.3"
#define C01_FRONT_IP "192.168.32.4"
#define C01_BACKEND_IP "192.168.32.5"
#define C01_SELF_IP "192.168.32.6" */ 

#define SENTINEL_IP "192.168.21.100"
//#define SENTINEL_IP "192.168.8.231"
//#define C01_SENTINEL_IP "192.168.32.2"
#define C01_SENTINEL_IP "192.168.21.101"  // C01 Antenna Sentinel system 
#define C02_SENTINEL_IP "192.168.21.102"
#define C03_SENTINEL_IP "192.168.21.103"
//#define C04_SENTINEL_IP "192.168.32.5"
#define C04_SENTINEL_IP "192.168.21.104"   // C04 antenna sentinel system 
#define C05_SENTINEL_IP "192.168.21.105"
//#define C06_SENTINEL_IP "192.168.31.3"
#define C06_SENTINEL_IP "192.168.21.106"   // C06 antenna sentinel system
//#define C06_SENTINEL_IP "192.168.49.105"
#define C08_SENTINEL_IP "192.168.21.108"
#define C09_SENTINEL_IP "192.168.21.109"
#define C10_SENTINEL_IP "192.168.21.110"
#define C11_SENTINEL_IP "192.168.21.111"
#define C12_SENTINEL_IP "192.168.21.112"
#define C13_SENTINEL_IP "192.168.21.113"
#define C14_SENTINEL_IP "192.168.21.114"
#define E02_SENTINEL_IP "192.168.21.115"
#define E03_SENTINEL_IP "192.168.21.116"
#define E04_SENTINEL_IP "192.168.21.117"
#define E05_SENTINEL_IP "192.168.21.118"
#define E06_SENTINEL_IP "192.168.21.119"
#define S01_SENTINEL_IP "192.168.21.120"
#define S02_SENTINEL_IP "192.168.46.121"
#define S03_SENTINEL_IP "192.168.21.122"
#define S04_SENTINEL_IP "192.168.21.123"
#define S06_SENTINEL_IP "192.168.31.3"
#define W01_SENTINEL_IP "192.168.21.121"   // S02 IP assigned for time being 
#define W02_SENTINEL_IP "192.168.32.2"
#define W03_SENTINEL_IP "192.168.32.3"
#define W04_SENTINEL_IP "192.168.32.4"
#define W05_SENTINEL_IP "192.168.32.5"
#define W06_SENTINEL_IP "192.168.33.2"


//#define FPS_IP "192.168.8.235" // FPS system IP.

#define FPS_IP "192.168.48.107"           // FPS system IP for C06 antenna testing.
#define C01_FPS_IP "192.168.21.131"    // C01 Antenna FPS system 
#define C02_FPS_IP "192.168.24.132"
#define C03_FPS_IP "192.168.48.4"
#define C04_FPS_IP "192.168.23.110"     // C04 antenna FPS system 
#define C05_FPS_IP "192.168.21.132"
#define C06_FPS_IP "192.168.21.107"     // C06 antenna FPS system
#define C08_FPS_IP "192.168.48.4"
#define C09_FPS_IP "192.168.48.4"
#define C10_FPS_IP "192.168.48.4"
#define C11_FPS_IP "192.168.48.4"
#define C12_FPS_IP "192.168.48.4"
#define C13_FPS_IP "192.168.48.4"
#define C14_FPS_IP "192.168.48.4"
#define E02_FPS_IP "192.168.48.4"
#define E03_FPS_IP "192.168.48.4"
#define E04_FPS_IP "192.168.48.4"
#define E05_FPS_IP "192.168.48.4"
#define E06_FPS_IP "192.168.48.4"
#define S01_FPS_IP "192.168.48.4"
#define S02_FPS_IP "192.168.48.4"
#define S03_FPS_IP "192.168.48.4"
#define S04_FPS_IP "192.168.48.4"
#define S06_FPS_IP "192.168.48.4"
#define W01_FPS_IP "192.168.48.4"
#define W02_FPS_IP "192.168.48.4"
#define W03_FPS_IP "192.168.48.4"
#define W04_FPS_IP "192.168.48.4"
#define W05_FPS_IP "192.168.48.4"
#define W06_FPS_IP "192.168.48.4"


#define FIBER_IP "192.168.22.114"      // C14 MCM card   
//#define C01_FIBER_IP "192.168.33.2"
#define C01_FIBER_IP "192.168.22.123"   // C01 antenna OF system 
#define C02_FIBER_IP "192.168.21.124"
#define C03_FIBER_IP "192.168.21.125"
#define C04_FIBER_IP "192.168.21.126"   // C04 antenna Of system 
#define C05_FIBER_IP "192.168.21.127"
//#define C06_FIBER_IP "192.168.36.8"
#define C06_FIBER_IP "192.168.21.128"   // C06 Fiber Optics MCM Card IP
//#define C06_FIBER_IP "192.168.36.10" 
#define C08_FIBER_IP "192.168.36.9"
#define C09_FIBER_IP "192.168.48.4"
#define C10_FIBER_IP "192.168.48.4"
#define C11_FIBER_IP "192.168.48.4"
#define C12_FIBER_IP "192.168.48.4"
#define C13_FIBER_IP "192.168.48.4"
#define C14_FIBER_IP "192.168.48.4"
#define E02_FIBER_IP "192.168.48.4"
#define E03_FIBER_IP "192.168.48.4"
#define E04_FIBER_IP "192.168.48.4"
#define E05_FIBER_IP "192.168.48.4"
#define E06_FIBER_IP "192.168.48.4"
#define S01_FIBER_IP "192.168.48.4"
#define S02_FIBER_IP "192.168.48.4"
#define S03_FIBER_IP "192.168.48.4"
#define S04_FIBER_IP "192.168.48.4"
#define S06_FIBER_IP "192.168.48.4"
#define W01_FIBER_IP "192.168.48.4"
#define W02_FIBER_IP "192.168.48.4"
#define W03_FIBER_IP "192.168.48.4"
#define W04_FIBER_IP "192.168.48.4"
#define W05_FIBER_IP "192.168.48.4"
#define W06_FIBER_IP "192.168.48.4"



#define FRONT_IP "192.168.8.172"            
//#define FRONT_IP "192.168.31.3"  
#define C01_FRONT_IP "192.168.8.112"
#define C02_FRONT_IP "192.168.35.5"
#define C03_FRONT_IP "192.168.37.5"
#define C04_FRONT_IP "192.168.37.104"    
#define C05_FRONT_IP "192.168.37.7"
#define C06_FRONT_IP "192.168.37.109"   
#define C08_FRONT_IP "192.168.37.9"
#define C09_FRONT_IP "192.168.48.4"
#define C10_FRONT_IP "192.168.48.4"
#define C11_FRONT_IP "192.168.48.4"
#define C12_FRONT_IP "192.168.48.4"
#define C13_FRONT_IP "192.168.48.4"
#define C14_FRONT_IP "192.168.48.4"
#define E02_FRONT_IP "192.168.48.4"
#define E03_FRONT_IP "192.168.48.4"
#define E04_FRONT_IP "192.168.48.4"
#define E05_FRONT_IP "192.168.48.4"
#define E06_FRONT_IP "192.168.48.4"
#define S01_FRONT_IP "192.168.48.4"
#define S02_FRONT_IP "192.168.48.4"
#define S03_FRONT_IP "192.168.48.4"
#define S04_FRONT_IP "192.168.48.4"
#define S06_FRONT_IP "192.168.48.4"
#define W01_FRONT_IP "192.168.48.4"
#define W02_FRONT_IP "192.168.48.4"
#define W03_FRONT_IP "192.168.48.4"
#define W04_FRONT_IP "192.168.48.4"
#define W05_FRONT_IP "192.168.48.4"
#define W06_FRONT_IP "192.168.48.4"
 
#define BACKEND_IP "192.168.31.2"    // LAB Set up MCM card.   
#define C01_BACKEND_IP "192.168.8.120"  // LAB new MCM card Testing At 15/01/2015
#define C02_BACKEND_IP "192.168.38.4"
#define C03_BACKEND_IP "192.168.38.5"
#define C04_BACKEND_IP "192.168.38.2"  // LAB Network
#define C05_BACKEND_IP "192.168.38.7"
#define C06_BACKEND_IP "192.168.38.110"  
#define C08_BACKEND_IP "192.168.38.9"
#define C09_BACKEND_IP "192.168.48.4"
#define C10_BACKEND_IP "192.168.48.4"
#define C11_BACKEND_IP "192.168.48.4"
#define C12_BACKEND_IP "192.168.48.4"
#define C13_BACKEND_IP "192.168.48.4"
#define C14_BACKEND_IP "192.168.48.4"
#define E02_BACKEND_IP "192.168.48.4"
#define E03_BACKEND_IP "192.168.48.4"
#define E04_BACKEND_IP "192.168.48.4"
#define E05_BACKEND_IP "192.168.48.4"
#define E06_BACKEND_IP "192.168.48.4"
#define S01_BACKEND_IP "192.168.48.4"
#define S02_BACKEND_IP "192.168.48.4"
#define S03_BACKEND_IP "192.168.48.4"
#define S04_BACKEND_IP "192.168.48.4"
#define S06_BACKEND_IP "192.168.48.4"
#define W01_BACKEND_IP "192.168.48.4"
#define W02_BACKEND_IP "192.168.48.4"
#define W03_BACKEND_IP "192.168.48.4"
#define W04_BACKEND_IP "192.168.48.4"
#define W05_BACKEND_IP "192.168.48.4"
#define W06_BACKEND_IP "192.168.48.4"


#define SELF_IP "192.168.39.2"
#define C01_SELF_IP "192.168.39.3"
#define C02_SELF_IP "192.168.39.4"
#define C03_SELF_IP "192.168.39.5"
#define C04_SELF_IP "192.168.39.6"
#define C05_SELF_IP "192.168.39.7"
#define C06_SELF_IP "192.168.39.8"
#define C08_SELF_IP "192.168.39.9"
#define C09_SELF_IP "192.168.48.4"
#define C10_SELF_IP "192.168.48.4"
#define C11_SELF_IP "192.168.48.4"
#define C12_SELF_IP "192.168.48.4"
#define C13_SELF_IP "192.168.48.4"
#define C14_SELF_IP "192.168.48.4"
#define E02_SELF_IP "192.168.48.4"
#define E03_SELF_IP "192.168.48.4"
#define E04_SELF_IP "192.168.48.4"
#define E05_SELF_IP "192.168.48.4"
#define E06_SELF_IP "192.168.48.4"
#define S01_SELF_IP "192.168.48.4"
#define S02_SELF_IP "192.168.48.4"
#define S03_SELF_IP "192.168.48.4"
#define S04_SELF_IP "192.168.48.4"
#define S06_SELF_IP "192.168.48.4"
#define W01_SELF_IP "192.168.48.4"
#define W02_SELF_IP "192.168.48.4"
#define W03_SELF_IP "192.168.48.4"
#define W04_SELF_IP "192.168.48.4"
#define W05_SELF_IP "192.168.48.4"
#define W06_SELF_IP "192.168.48.4"

void *sentinel_thread(void *);
void *fiber_thread(void *);
void *front_thread(void *);
void *backend_thread(void *);
void *self_thread(void *);
void *fps_thread(void *);

void *C01_sentinel_thread(void *);
void *C01_fiber_thread(void *);
void *C01_front_thread(void *);
void *C01_backend_thread(void *);
void *C01_self_thread(void *);
void *C01_fps_thread(void *);

void *C02_sentinel_thread(void *);
void *C02_fiber_thread(void *);
void *C02_front_thread(void *);
void *C02_backend_thread(void *);
void *C02_self_thread(void *);
void *C02_fps_thread(void *);


void *C03_sentinel_thread(void *);
void *C03_fiber_thread(void *);
void *C03_front_thread(void *);
void *C03_backend_thread(void *);
void *C03_self_thread(void *);
void *C03_fps_thread(void *);

void *C04_sentinel_thread(void *);
void *C04_fiber_thread(void *);
void *C04_front_thread(void *);
void *C04_backend_thread(void *);
void *C04_self_thread(void *);
void *C04_fps_thread(void *);

void *C05_sentinel_thread(void *);
void *C05_fiber_thread(void *);
void *C05_front_thread(void *);
void *C05_backend_thread(void *);
void *C05_self_thread(void *);
void *C05_fps_thread(void *);

void *C06_sentinel_thread(void *);
void *C06_fiber_thread(void *);
void *C06_front_thread(void *);
void *C06_backend_thread(void *);
void *C06_self_thread(void *);
void *C06_fps_thread(void *);

void *C08_sentinel_thread(void *);
void *C08_fiber_thread(void *);
void *C08_front_thread(void *);
void *C08_backend_thread(void *);
void *C08_self_thread(void *);
void *C08_fps_thread(void *);

void *C09_sentinel_thread(void *);
void *C09_fiber_thread(void *);
void *C09_front_thread(void *);
void *C09_backend_thread(void *);
void *C09_self_thread(void *);
void *C09_fps_thread(void *);

void *C10_sentinel_thread(void *);
void *C10_fiber_thread(void *);
void *C10_front_thread(void *);
void *C10_backend_thread(void *);
void *C10_self_thread(void *);
void *C10_fps_thread(void *);

void *C11_sentinel_thread(void *);
void *C11_fiber_thread(void *);
void *C11_front_thread(void *);
void *C11_backend_thread(void *);
void *C11_self_thread(void *);
void *C11_fps_thread(void *);

void *C12_sentinel_thread(void *);
void *C12_fiber_thread(void *);
void *C12_front_thread(void *);
void *C12_backend_thread(void *);
void *C12_self_thread(void *);
void *C12_fps_thread(void *);

void *C13_sentinel_thread(void *);
void *C13_fiber_thread(void *);
void *C13_front_thread(void *);
void *C13_backend_thread(void *);
void *C13_self_thread(void *);
void *C13_fps_thread(void *);

void *C14_sentinel_thread(void *);
void *C14_fiber_thread(void *);
void *C14_front_thread(void *);
void *C14_backend_thread(void *);
void *C14_self_thread(void *);
void *C14_fps_thread(void *);

void *E01_sentinel_thread(void *);
void *E01_fiber_thread(void *);
void *E01_front_thread(void *);
void *E01_backend_thread(void *);
void *E01_self_thread(void *);
void *E01_fps_thread(void *);

void *E02_sentinel_thread(void *);
void *E02_fiber_thread(void *);
void *E02_front_thread(void *);
void *E02_backend_thread(void *);
void *E02_self_thread(void *);
void *E02_fps_thread(void *);

void *E03_sentinel_thread(void *);
void *E03_fiber_thread(void *);
void *E03_front_thread(void *);
void *E03_backend_thread(void *);
void *E03_self_thread(void *);
void *E03_fps_thread(void *);

void *E04_sentinel_thread(void *);
void *E04_fiber_thread(void *);
void *E04_front_thread(void *);
void *E04_backend_thread(void *);
void *E04_self_thread(void *);
void *E04_fps_thread(void *);

void *E05_sentinel_thread(void *);
void *E05_fiber_thread(void *);
void *E05_front_thread(void *);
void *E05_backend_thread(void *);
void *E05_self_thread(void *);
void *E05_fps_thread(void *);

void *E06_sentinel_thread(void *);
void *E06_fiber_thread(void *);
void *E06_front_thread(void *);
void *E06_backend_thread(void *);
void *E06_self_thread(void *);
void *E06_fps_thread(void *);

void *S01_sentinel_thread(void *);
void *S01_fiber_thread(void *);
void *S01_front_thread(void *);
void *S01_backend_thread(void *);
void *S01_self_thread(void *);
void *S01_fps_thread(void *);

void *S02_sentinel_thread(void *);
void *S02_fiber_thread(void *);
void *S02_front_thread(void *);
void *S02_backend_thread(void *);
void *S02_self_thread(void *);
void *S02_fps_thread(void *);

void *S03_sentinel_thread(void *);
void *S03_fiber_thread(void *);
void *S03_front_thread(void *);
void *S03_backend_thread(void *);
void *S03_self_thread(void *);
void *S03_fps_thread(void *);

void *S04_sentinel_thread(void *);
void *S04_fiber_thread(void *);
void *S04_front_thread(void *);
void *S04_backend_thread(void *);
void *S04_self_thread(void *);
void *S04_fps_thread(void *);

void *S06_sentinel_thread(void *);
void *S06_fiber_thread(void *);
void *S06_front_thread(void *);
void *S06_backend_thread(void *);
void *S06_self_thread(void *);
void *S06_fps_thread(void *);

void *W01_sentinel_thread(void *);
void *W01_fiber_thread(void *);
void *W01_front_thread(void *);
void *W01_backend_thread(void *);
void *W01_self_thread(void *);
void *W01_fps_thread(void *);

void *W02_sentinel_thread(void *);
void *W02_fiber_thread(void *);
void *W02_front_thread(void *);
void *W02_backend_thread(void *);
void *W02_self_thread(void *);
void *W02_fps_thread(void *);

void *W03_sentinel_thread(void *);
void *W03_fiber_thread(void *);
void *W03_front_thread(void *);
void *W03_backend_thread(void *);
void *W03_self_thread(void *);
void *W03_fps_thread(void *);

void *W04_sentinel_thread(void *);
void *W04_fiber_thread(void *);
void *W04_front_thread(void *);
void *W04_backend_thread(void *);
void *W04_self_thread(void *);
void *W04_fps_thread(void *);

void *W05_sentinel_thread(void *);
void *W05_fiber_thread(void *);
void *W05_front_thread(void *);
void *W05_backend_thread(void *);
void *W05_self_thread(void *);
void *W05_fps_thread(void *);

void *W06_sentinel_thread(void *);
void *W06_fiber_thread(void *);
void *W06_front_thread(void *);
void *W06_backend_thread(void *);
void *W06_self_thread(void *);
void *W06_fps_thread(void *);

#endif
