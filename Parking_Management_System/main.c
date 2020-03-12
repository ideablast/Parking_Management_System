#include"ALL.h"

Queue *front[MAX_FLOOR];
Queue *rear[MAX_FLOOR];

int main()
{
	int floor_idx;
	int queue_idx;
	Car temp;
	temp.enter_time = 0;
	temp.number = 0;

	for (floor_idx = 0; floor_idx < MAX_FLOOR; floor_idx++)
	{
		front[floor_idx] = Add_new_queue();
		rear[floor_idx] = Add_new_queue();

		//각 층의 주차자리 추가 및 초기화
		for (queue_idx = 0; queue_idx < MAX_QUEUE; queue_idx++)
		{
			L_enQueue(floor_idx, temp);
		}
	}

}