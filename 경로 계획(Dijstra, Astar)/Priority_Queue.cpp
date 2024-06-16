#include "Priority_Queue.h"



void Exchange(VERTEX& ref1, VERTEX& ref2)
{
	VERTEX temp = ref1;
	ref1 = ref2;
	ref2 = temp;
}

Priority_Queue::Priority_Queue(VERTEX* ptr) :Q(ptr), Q_heapsize(0) {}

VERTEX* Priority_Queue::Get_Q()
{
	return Q;
}
int Priority_Queue::Get_Q_heapsize()
{
	return Q_heapsize;
}

bool Priority_Queue::IsEmpty()
{
	if (Q_heapsize < 0)
		return true;
	return false;
}
void Priority_Queue::Min_Heapify(VERTEX* ptr, int i, int heapsize) // 부모와 자식 비교해서 최소 힙 특성 유지
{
	int l = LEFT(i);
	int r = RIGHT(i);
	int smallest = i;
	if (l <= heapsize && ptr[l].d < ptr[i].d)
	{
		smallest = l;
	}
	if (r <= heapsize && ptr[r].d < ptr[smallest].d)
	{
		smallest = r;
	}
	if (smallest != i)
	{
		Exchange(ptr[i], ptr[smallest]);
		Min_Heapify(ptr, smallest, heapsize);
	}
}

VERTEX Priority_Queue::Heap_Extract_Min()						//  최소 정점 d값 추출
{
	if (Q_heapsize < 0)
		throw std::out_of_range("Heap is empty");
	VERTEX min = Q[0];
	Q[0] = Q[Q_heapsize];
	Q[Q_heapsize].d = numeric_limits<double>::max();
	Q_heapsize = Q_heapsize - 1;
	Min_Heapify(Q, 0, Q_heapsize); // 힙 속성 유지
	return min;
}

void Priority_Queue::Heap_Decrease_Key(int i)
{
	while (i > 0 && Q[PARENT(i)].d > Q[i].d)
	{
		Exchange(Q[i], Q[PARENT(i)]);
		i = PARENT(i);
	}
}

void Priority_Queue::Min_Heap_Insert(VERTEX V)					// 새로운 노드 삽입
{
	Q_heapsize++;
	Q[Q_heapsize] = V;
	Heap_Decrease_Key(Q_heapsize);
}
