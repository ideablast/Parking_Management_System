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


