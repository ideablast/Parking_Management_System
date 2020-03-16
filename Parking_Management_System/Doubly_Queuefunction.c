#include"ALL.h"

extern Queue *front[MAX_FLOOR];
extern Queue *rear[MAX_FLOOR];

Queue* Add_new_queue()
{
	Queue *temp = (Queue*)malloc(sizeof(Queue));
	temp->Car.enter_time = 0;
	temp->Car.number = 0;
	temp->L_Link = NULL;
	temp->R_Link = NULL;

	return temp;
}

Queue* Add_existed_queue()
{
	Queue *temp = (Queue*)malloc(sizeof(Queue));
	temp->Car.enter_time = 0;
	temp->Car.number = 0;
	temp->L_Link = NULL;
	temp->R_Link = NULL;

	return temp;
}

//front, rear의 링크중 L_Link만 사용

void L_enQueue(int floor_idx, Car enter_car)//front로 추가된다.
{
	Queue *temp = Add_new_queue();
	temp->Car.number = enter_car.number;
	temp->Car.enter_time = enter_car.enter_time;

	if (front[floor_idx]->L_Link == NULL)
	{
		front[floor_idx]->L_Link = temp;
		rear[floor_idx]->L_Link = temp;
	}

	else
	{
		//temp->L_Link = front[floor_idx]->L_Link->L_Link;
		front[floor_idx]->L_Link->L_Link = temp;

		temp->R_Link = front[floor_idx]->L_Link;
		front[floor_idx]->L_Link = temp;

	}

}

void L_existed_enQueue(int floor_idx, Car enter_car)//front로 추가된다.
{
	Queue *temp = Add_new_queue();
	temp->Car.number = enter_car.number;
	temp->Car.enter_time = enter_car.enter_time;

	if (front[floor_idx]->L_Link == NULL)
	{
		front[floor_idx]->L_Link = temp;
		rear[floor_idx]->L_Link = temp;
	}

	else
	{
		temp->L_Link = front[floor_idx]->L_Link->L_Link;
		front[floor_idx]->L_Link->L_Link = temp;

		temp->R_Link = front[floor_idx]->L_Link;
		front[floor_idx]->L_Link = temp;

	}

}

void R_enQueue(int floor_idx, Car enter_car)//rear[floor_idx]로 추가된다.
{
	Queue *temp = Add_new_queue();
	temp->Car.number = enter_car.number;
	temp->Car.enter_time = enter_car.enter_time;

	if (rear[floor_idx]->L_Link == NULL)
	{
		front[floor_idx]->L_Link = temp;
		rear[floor_idx]->L_Link = temp;
	}
	else
	{
		//temp->R_Link = rear[floor_idx]->L_Link->R_Link;
		rear[floor_idx]->L_Link->R_Link = temp;
		temp->L_Link = rear[floor_idx]->L_Link;
		rear[floor_idx]->L_Link = temp;
	}

}

void R_existed_enQueue(int floor_idx, Car enter_car)//rear[floor_idx]로 추가된다.
{
	Queue *temp = Add_new_queue();
	temp->Car.number = enter_car.number;
	temp->Car.enter_time = enter_car.enter_time;

	if (rear[floor_idx]->L_Link == NULL)
	{
		front[floor_idx]->L_Link = temp;
		rear[floor_idx]->L_Link = temp;
	}
	else
	{
		temp->R_Link = rear[floor_idx]->L_Link->R_Link;
		rear[floor_idx]->L_Link->R_Link = temp;
		temp->L_Link = rear[floor_idx]->L_Link;
		rear[floor_idx]->L_Link = temp;
	}

}

Car R_deQueue(int floor_idx)//rear[floor_idx]부터 나간다.
{
	Queue *deQueue_mem;
	Car deQueue_car_Data;
	Car result;

	deQueue_mem = rear[floor_idx]->L_Link;
	deQueue_car_Data = rear[floor_idx]->L_Link->Car;
	result = deQueue_car_Data;

	if (rear[floor_idx]->L_Link != front[floor_idx]->L_Link)
	{
		rear[floor_idx]->L_Link = deQueue_mem->L_Link;
		rear[floor_idx]->L_Link->R_Link = deQueue_mem->R_Link;
		free(deQueue_mem);
	}
	else
	{
		front[floor_idx]->L_Link = deQueue_mem->L_Link;
		rear[floor_idx]->L_Link = deQueue_mem->L_Link;
		free(deQueue_mem);
	}

	return result;
}

Car L_deQueue(int floor_idx)//front[floor_idx]부터 나간다. 
{
	Queue *deQueue_mem;
	Car deQueue_car_Data;
	Car result;

	deQueue_mem = front[floor_idx]->L_Link;
	deQueue_car_Data = front[floor_idx]->L_Link->Car;
	result = deQueue_car_Data;

	if (front[floor_idx]->L_Link != rear[floor_idx]->L_Link)
	{
		front[floor_idx]->L_Link = deQueue_mem->R_Link;
		front[floor_idx]->L_Link->L_Link = deQueue_mem->L_Link;
		free(deQueue_mem);
	}
	else
	{
		front[floor_idx]->L_Link = deQueue_mem->R_Link;
		rear[floor_idx]->L_Link = deQueue_mem->R_Link;
		free(deQueue_mem);
	}

	return result;
}

int IsEmpty(int floor_idx)
{
	return front[floor_idx]->L_Link == NULL;
}

int Count_Queue(int floor_idx)
{
	int cnt = 0;
	Queue *Count = front[floor_idx]->L_Link;

	while (Count != NULL)
	{
		cnt++;
		Count = Count->R_Link;
	}
	cnt++;

	return cnt;
}
/*PARKING_TOWER_MANAGEMENT_FUNC*/
void Set_Slot()
{
	int floor_idx;
	int queue_idx;
	Car temp;
	temp.enter_time = 0;
	temp.number = 0;

	//각 층의 주차자리 추가 및 초기화
	for (floor_idx = 0; floor_idx < MAX_FLOOR; floor_idx++)
	{
		front[floor_idx] = Add_new_queue();
		rear[floor_idx] = Add_new_queue();

		for (queue_idx = 0; queue_idx < MAX_QUEUE; queue_idx++)
		{
			L_enQueue(floor_idx, temp);
		}
	}


	//front와 rear의 링크 설정
	for (floor_idx = 0; floor_idx < MAX_FLOOR; floor_idx++)
	{
		
		if (floor_idx == 0)//1층
		{
			front[0]->L_Link->L_Link = front[1]->L_Link;
			if (MAX_FLOOR % 2 == 1)
			{
				rear[0]->L_Link->R_Link = front[MAX_FLOOR - 1]->L_Link;
			}
			else
			{
				rear[0]->L_Link->R_Link = rear[MAX_FLOOR - 1]->L_Link;
			}
		}
		else if (floor_idx == MAX_FLOOR - 1)//최상층
		{
			front[floor_idx];
			rear[floor_idx];

			if (MAX_FLOOR % 2 == 1)
			{
				front[MAX_FLOOR - 1]->L_Link->L_Link = rear[0]->L_Link;
				rear[MAX_FLOOR - 1]->L_Link->R_Link = rear[MAX_FLOOR - 2]->L_Link;
			}
			else
			{
				rear[MAX_FLOOR - 1]->L_Link->R_Link = rear[0]->L_Link;
				front[MAX_FLOOR - 1]->L_Link->L_Link = front[MAX_FLOOR - 2]->L_Link;
			}

		}
		else
		{
			if (floor_idx % 2 == 0)
			{
				front[floor_idx]->L_Link->L_Link = front[floor_idx+1]->L_Link;
				rear[floor_idx]->L_Link->R_Link = rear[floor_idx - 1]->L_Link;
			}
			else
			{
				front[floor_idx]->L_Link->L_Link = front[floor_idx-1]->L_Link;
				rear[floor_idx]->L_Link->R_Link = rear[floor_idx+1]->L_Link;
			}
		}
	}
}
Car L_Rotation_Xtimes(int floor_idx, int times)//
//times에 1전달시 front에 주차된 차량 정보 확인 가능
{
	Car temp;
	int cnt;
	
	for (cnt = 0; cnt < times; cnt++)
	{
		temp = L_deQueue(floor_idx);
		//R_enQueue(floor_idx, temp
		R_existed_enQueue(floor_idx, temp);
	}
	return temp;
}

Car R_Rotation_Xtimes(int floor_idx, int times)
//times에 1전달시 rear에 주차된 차량 정보 확인 가능
{
	Car temp;
	int cnt;


	for (cnt = 0; cnt < times; cnt++)
	{
		temp = R_deQueue(floor_idx);
		//L_enQueue(floor_idx, temp);
		L_existed_enQueue(floor_idx, temp);
	}

	return temp;
}

Car Make_Rand_Car()
{
	Car temp;
	struct tm *date;
	date = Get_time();

	temp.enter_time = To_sec(date->tm_hour, date->tm_min, date->tm_sec);
	temp.number = rand() & 9999 + 1;

	return temp;
}

int Duplication_Check(int floor_idx, Car temp)
{
	int  idx, result;
	Car check_temp;

	for (idx = 0; idx < MAX_QUEUE; idx++)
	{
		check_temp = L_Rotation_Xtimes(floor_idx, 1);
		if (check_temp.number == temp.number)
			result = TRUE;
		else
			result = FALSE;
	}

	return result;
}

Car Random_Input()
{
	Car temp;
	int floor_idx, result;

	while (1)
	{
		temp = Make_Rand_Car();
		for (floor_idx = 0; floor_idx < MAX_FLOOR; floor_idx++)
		{
			result = Duplication_Check(floor_idx, temp);
		}
		if (result == FALSE)
			break;
	}

	return temp;
}

void Print_Car_Info(Car temp)
{
	printf("차량 번호: %d ", temp.number);
	printf("시간: %d\n", temp.enter_time);
}

Car User_Input()
{
	Car temp;
	struct tm *date;
	date = Get_time();

	printf("차량 번호를 입력해주세요:"); scanf("%d", &temp.number); clear_buf();
	temp.enter_time = To_sec(date->tm_hour, date->tm_min, date->tm_sec);

	return temp;
}

void Enter_Slot(int floor_idx, int slot_idx, Car enter_car)
{
	Car temp;
	int cnt;

	for (cnt = 0; cnt < slot_idx; cnt++)
	{
		temp = L_deQueue(floor_idx);
		if (cnt == slot_idx - 1)
			temp = enter_car;
		//R_enQueue(floor_idx, temp);
		R_existed_enQueue(floor_idx, temp);
	}

	for (cnt = 0; cnt < slot_idx; cnt++)
	{
		temp = R_deQueue(floor_idx);
		L_existed_enQueue(floor_idx, temp);
	}
}

void Enter_Car(int times)
{
	int floor_idx;
	int slot_idx;

	int test_times;

	Car temp;

	for (test_times = 0; test_times < times; test_times++)
	{
		Show_Status();
		floor_idx = Floor_Select();

		while (1)
		{
			Show_Floor_Status(floor_idx);
			slot_idx = Slot_Select();
			temp = L_Rotation_Xtimes(floor_idx, slot_idx);
			R_Rotation_Xtimes(floor_idx, slot_idx);
			if (temp.number == 0)
			{
				puts("주차가능");
				//Sleep(500);
				break;
			}
			else
			{
				puts("주차불가");
				//Sleep(500);
			}
		}
		//테스트용
		temp = Random_Input();
		Print_Car_Info(temp);
		//User_Input();
		Enter_Slot(floor_idx, slot_idx, temp);
		Show_Floor_Status(floor_idx);
		puts("주차 완료");
	}
}

void Exit_Car()
{
	int  floor_idx, Queue_idx;
	int find_floor, find_slot;
	Car check_temp, temp, reset_temp;

	reset_temp.enter_time = 0;
	reset_temp.number = 0;
	temp = User_Input();

	for (floor_idx = 0; floor_idx < MAX_FLOOR; floor_idx++)
	{
		for (Queue_idx = 0; Queue_idx < MAX_QUEUE; Queue_idx++)
		{
			check_temp = L_Rotation_Xtimes(floor_idx, 1);
			if (check_temp.number == temp.number)
			{
				find_floor = floor_idx;
				find_slot = Queue_idx + 1;
				R_Rotation_Xtimes(find_floor, find_slot);
				Enter_Slot(find_floor, find_slot, reset_temp);
				printf("정산할 요금:%d\n", charge_settlement(find_floor, check_temp.enter_time));
				break;
			}
		}
	}
	Show_Floor_Status(find_floor);
	Deliver_Car(find_floor, find_slot);
}

int Deliver_Car(int find_floor, int find_slot)
{
	int rand_floor;
	int rand_f_r;//0:front, r:1
	int front_cnt = 0;
	int rear_cnt = 0;
	int times;
	Queue *location = front[find_floor]->L_Link;
	Queue *pre_location;
	Queue *target;

	rand_floor = rand() % MAX_FLOOR;
	rand_f_r = rand() % 2;

	printf("현재 %d층 %d(0:f, 1:r)\n", rand_floor, rand_f_r);

	if (rand_f_r == 0)
		target = front[rand_floor]->L_Link;
	else
		target = rear[rand_floor]->L_Link;

	for (times = 0; times < find_slot; times++)//시작 위차로 세팅
	{
		location = location->R_Link;
	}

	while (1)
	{
		if (location == target)
			break;

		pre_location = location->L_Link;
		while (1)
		{
			location = location->L_Link;
			pre_location = pre_location->L_Link;
			front_cnt++;
			if (pre_location->L_Link == location)
			{
				location = pre_location;
				front_cnt++;
				break;
			}

		}

		if (location == target)
			break;

		pre_location = location->R_Link;
		while (1)
		{
			location = location->R_Link;
			pre_location = pre_location->R_Link;
			front_cnt++;
			if (pre_location->R_Link == location)
			{
				location = pre_location;
				front_cnt++;
				break;
			}
		}

		if (location == target)
			break;
	}


	while (1)
	{
		if (location == target)
			break;

		pre_location = location->R_Link;
		while (1)
		{
			location = location->R_Link;
			pre_location = pre_location->R_Link;
			rear_cnt++;
			if (pre_location->R_Link == location)
			{
				location = pre_location;
				rear_cnt++;
				break;
			}
		}

		if (location == target)
			break;

		pre_location = location->L_Link;
		while (1)
		{
			location = location->L_Link;
			pre_location = pre_location->L_Link;
			rear_cnt++;
			if (pre_location->L_Link == location)
			{
				location = pre_location;
				rear_cnt++;
				break;
			}
		}
		
		if (location == target)
			break;
	}

	printf("앞으로 출차 했을때: %d 회 이동\n", front_cnt+1);
	printf("뒤로 출차 했을때: %d 회 이동\n", rear_cnt + 1);

	return front_cnt > rear_cnt ? rear_cnt : front_cnt;
}

int charge_settlement(int floor_idx, int enter_time )
{
	int cur_time;
	struct tm *date;
	date = Get_time();

	cur_time = To_sec(date->tm_hour, date->tm_min, date->tm_sec);

	return (MAX_FLOOR - floor_idx + 10) * 1000 + (cur_time - enter_time) * 100;
}


/*PARKING_TOWER_MANAGEMENT_PRINT*/
void Show_Floor_Status(int floor_idx)
{
	Car temp;
	int idx;
	printf("%d층: ", floor_idx);
	for (idx = 0; idx < MAX_QUEUE; idx++)
	{
		temp = L_Rotation_Xtimes(floor_idx, 1);
		if (temp.number == 0)
			printf("□ ");
		else
			printf("■ ");
	}
	puts("");
}

void Show_Status()
{
	int floor_idx;
	printf("□:주차가능 ■:주차불가\n");
	for (floor_idx = 0; floor_idx < MAX_FLOOR; floor_idx++)
	{
		Show_Floor_Status(floor_idx);
	}
}

int Floor_Select()
{
	int floor;
	printf("층을 골라주세요:"); scanf("%d", &floor); clear_buf(); puts("");
	system("cls");
	
	return floor;
}

int Slot_Select()
{
	int slot;
	printf("자리를 골라주세요:"); scanf("%d", &slot); clear_buf(); puts("");
	system("cls");

	return slot;
}

/*TIME*/
struct tm *Get_time()//함수가 실행될때 마다 현재 시간을 구할 수 있음
{
	const time_t t = time(NULL);
	return localtime(&t);
}

int To_sec(int hour, int min, int sec)
{
	return (hour * 3600) + (min * 60) + sec;
}

/*SIMPLE_FUNCTION*/
void clear_buf()//버퍼 비우기
{
	while (getchar() != '\n');
}

#ifdef NOTYET

void L_enQueue(int floor_idx, Car enter_car)//front로 추가된다.
{
	Queue *temp = Add_new_queue();
	temp->Car.number = enter_car.number;
	temp->Car.enter_time = enter_car.enter_time;

	if (front[floor_idx]->L_Link == NULL)
	{
		front[floor_idx]->L_Link = temp;
		rear[floor_idx]->L_Link = temp;
	}

	else
	{
		front[floor_idx]->L_Link->L_Link = temp;
		temp->R_Link = front[floor_idx]->L_Link;
		front[floor_idx]->L_Link = temp;

	}

}

void R_enQueue(int floor_idx, Car enter_car)//rear[floor_idx]로 추가된다.
{
	Queue *temp = Add_new_queue();
	temp->Car.number = enter_car.number;
	temp->Car.enter_time = enter_car.enter_time;

	if (rear[floor_idx]->L_Link == NULL)
	{
		front[floor_idx]->L_Link = temp;
		rear[floor_idx]->L_Link = temp;
	}
	else
	{
		rear[floor_idx]->L_Link->R_Link = temp;
		temp->L_Link = rear[floor_idx]->L_Link;
		rear[floor_idx]->L_Link = temp;
	}

}





//front, rear의 링크중 L_Link만 사용
void L_enQueue(int floor_idx, Car enter_car)//front로 추가된다.
{
	Queue *temp = Add_new_queue();
	temp->Car.number = enter_car.number;
	temp->Car.enter_time = enter_car.enter_time;

	if (front[floor_idx]->L_Link == NULL)
	{
		front[floor_idx]->L_Link = temp;
		rear[floor_idx]->L_Link = temp;
	}

	else
	{
		front[floor_idx]->L_Link->L_Link = temp;
		temp->R_Link = front[floor_idx]->L_Link;
		front[floor_idx]->L_Link = temp;

	}

}

void R_enQueue(int floor_idx, Car enter_car)//rear[floor_idx]로 추가된다.
{
	Queue *temp = Add_new_queue();
	temp->Car.number = enter_car.number;
	temp->Car.enter_time = enter_car.enter_time;

	if (rear[floor_idx]->L_Link == NULL)
	{
		front[floor_idx]->L_Link = temp;
		rear[floor_idx]->L_Link = temp;
	}
	else
	{
		rear[floor_idx]->L_Link->R_Link = temp;
		temp->L_Link = rear[floor_idx]->L_Link;
		rear[floor_idx]->L_Link = temp;
	}

}

Car R_deQueue(int floor_idx)//rear[floor_idx]부터 나간다.
{
	Queue *deQueue_mem;
	Car deQueue_car_Data;
	Car result;

	deQueue_mem = rear[floor_idx]->L_Link;
	deQueue_car_Data = rear[floor_idx]->L_Link->Car;
	result = deQueue_car_Data;

	if (rear[floor_idx]->L_Link != front[floor_idx]->L_Link)
	{
		rear[floor_idx]->L_Link = deQueue_mem->L_Link;
		rear[floor_idx]->L_Link->R_Link = NULL;
		free(deQueue_mem);
	}
	else
	{
		front[floor_idx]->L_Link = deQueue_mem->L_Link;
		rear[floor_idx]->L_Link = deQueue_mem->L_Link;
		free(deQueue_mem);
	}

	return result;
}

Car L_deQueue(int floor_idx)//front[floor_idx]부터 나간다. 
{
	Queue *deQueue_mem;
	Car deQueue_car_Data;
	Car result;

	deQueue_mem = front[floor_idx]->L_Link;
	deQueue_car_Data = front[floor_idx]->L_Link->Car;
	result = deQueue_car_Data;

	if (front[floor_idx]->L_Link != rear[floor_idx]->L_Link)
	{
		front[floor_idx]->L_Link = deQueue_mem->R_Link;
		front[floor_idx]->L_Link->L_Link = NULL;
		free(deQueue_mem);
	}
	else
	{
		front[floor_idx]->L_Link = deQueue_mem->R_Link;
		rear[floor_idx]->L_Link = deQueue_mem->R_Link;
		free(deQueue_mem);
	}

	return result;
}

int IsEmpty(int floor_idx)
{
	return front[floor_idx]->L_Link == NULL;
}

int Count_Queue(int floor_idx)
{
	int cnt = 0;
	Queue *Count = front[floor_idx]->L_Link;

	while (Count != NULL)
	{
		cnt++;
		Count = Count->R_Link;
	}
	cnt++;

	return cnt;
}
#endif