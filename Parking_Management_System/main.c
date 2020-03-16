#include"ALL.h"

Queue *front[MAX_FLOOR];
Queue *rear[MAX_FLOOR];

int main()
{
	srand((unsigned int)time(NULL));
	Set_Slot();
	
	Enter_Car(4);
	Exit_Car();
	//히스토리 출력하는거 만들기
	//최단거리 찾는거 만들기(L회전 R회전 횟수)



}