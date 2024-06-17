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
	void Min_Heapify(VERTEX* ptr, int i, int heapsize); // �θ�� �ڽ� ���ؼ� �ּ� �� Ư�� ����
	VERTEX Heap_Extract_Min();						//  �ּ� ���� d�� ����
	void Heap_Decrease_Key(int i);
	void Min_Heap_Insert(VERTEX V);
};

#endif