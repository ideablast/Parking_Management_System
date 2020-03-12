#pragma once
#include"ALL.h"

#ifndef __FUNC_H__
#define __FUNC_H__

/*BASIC_QUEUE*/
Queue* Add_new_queue();
void L_enQueue(int floor_idx, Car enter_car);
void R_enQueue(int floor_idx, Car enter_car);
Car R_deQueue(int floor_idx);
Car L_deQueue(int floor_idx);
int IsEmpty(int floor_idx);
int Count_Queue(int floor_idx);

#endif

