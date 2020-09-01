// SSCLINK.H
// All Thread for 30 Antenna Servo system will be here. 

#ifndef SSCLINK_H
#define SSCLINK_H

#include<pthread.h>


#define C00_SERVO_IP "192.168.21.101" // SSL servo PC104 card IP

#define C01_SERVO_IP "192.168.10.102" // SSL servo PC104 card IP

#define C02_SERVO_IP "192.168.10.103" // SSL servo PC104 card IP

#define C03_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define C04_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define C05_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define C06_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define C08_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define C09_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define C10_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define C11_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define C12_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define C13_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define C14_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define E02_SERVO_IP "192.168.10.103" // SSL servo PC104 card IP

#define E03_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define E04_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define E05_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define E06_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define S01_SERVO_IP "192.168.10.102" // SSL servo PC104 card IP

#define S02_SERVO_IP "192.168.10.103" // SSL servo PC104 card IP

#define S03_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define S04_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define S06_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define W01_SERVO_IP "192.168.10.102" // SSL servo PC104 card IP

#define W02_SERVO_IP "192.168.10.103" // SSL servo PC104 card IP

#define W03_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define W04_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define W05_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

#define W06_SERVO_IP "192.168.10.101" // SSL servo PC104 card IP

void *C00_servo(void *);

void *C01_servo(void *);

void *C02_servo(void *);

void *C03_servo(void *);

void *C04_servo(void *);

void *C05_servo(void *);

void *C06_servo(void *);

void *C08_servo(void *);

void *C09_servo(void *);

void *C10_servo(void *);

void *C11_servo(void *);

void *C12_servo(void *);

void *C13_servo(void *);

void *C14_servo(void *);

void *E02_servo(void *);

void *E03_servo(void *);

void *E04_servo(void *);

void *E05_servo(void *);

void *E06_servo(void *);

void *S01_servo(void *);

void *S02_servo(void *);

void *S03_servo(void *);

void *S04_servo(void *);

void *S06_servo(void *);

void *W01_servo(void *);

void *W02_servo(void *);

void *W03_servo(void *);

void *W04_servo(void *);

void *W05_servo(void *);

void *W06_servo(void *);
pthread_mutex_t locks;

#endif
