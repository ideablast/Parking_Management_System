#ifndef __Data_H__
#define __Data_H__
typedef struct _Car {
	int number;
	int enter_time;
}Car;


typedef struct _Queue {
	struct _Car Car;
	struct _Queue *L_Link;
	struct _Queue *R_Link;
}Queue;

#endif

#define MAX_FLOOR 5
#define MAX_QUEUE 10

#define TRUE 1
#define FALSE 0
#define FAIL -1


