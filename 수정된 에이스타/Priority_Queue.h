#ifndef _P_Q_H_
#define _P_Q_H_

#include "Graph.h"

#define PARENT(i) ((i-1)/2)
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)


void Exchange(VERTEX& ref1, VERTEX& ref2);

class Priority_Queue
{
	VERTEX* Q;
	int Q_heapsize;
public:
	Priority_Queue(VERTEX* ptr);
	VERTEX* Get_Q();
	int Get_Q_heapsize();
	bool IsEmpty();
	void Min_Heapify(VERTEX* ptr, int i, int heapsize); // 부모와 자식 비교해서 최소 힙 특성 유지
	VERTEX Heap_Extract_Min();						//  최소 정점 d값 추출
	void Heap_Decrease_Key(int i);
	void Min_Heap_Insert(VERTEX V);
};

#endif