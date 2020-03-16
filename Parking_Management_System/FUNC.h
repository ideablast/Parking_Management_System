#pragma once
#ifndef __FUNC_H__
#define __FUNC_H__

/*BASIC_QUEUE*/
Queue* Add_new_queue();
void L_enQueue(int floor_idx, Car enter_car);
void L_existed_enQueue(int floor_idx, Car enter_car);
void R_enQueue(int floor_idx, Car enter_car);
void R_existed_enQueue(int floor_idx, Car enter_car);
Car R_deQueue(int floor_idx);
Car L_deQueue(int floor_idx);
int IsEmpty(int floor_idx);
int Count_Queue(int floor_idx);

/*PARKING_TOWER_MANAGEMENT_FUNC*/
void Set_Slot();
Car L_Rotation_Xtimes(int floor_idx, int times);
Car R_Rotation_Xtimes(int floor_idx, int times);
void Enter_Slot(int floor_idx, int slot_idx, Car enter_car);
Car User_Input();
void Enter_Car(int times);
int charge_settlement(int floor_idx, int enter_time);
void Exit_Car();
int Deliver_Car(int find_floor, int find_slot);

/*PARKING_TOWER_MANAGEMENT_TEST*/
Car Make_Rand_Car();
int Duplication_Check(int floor_idx, Car temp);
Car Random_Input();
void Print_Car_Info(Car temp);

/*PARKING_TOWER_MANAGEMENT_PRINT*/
void Show_Floor_Status(int floor_idx);
void Show_Status();
int Floor_Select();
int Slot_Select();

/*TIME*/
struct tm *Get_time();
int To_sec(int hour, int min, int sec);

/*SIMPLE_FUNCTION*/
void clear_buf();
#endif

