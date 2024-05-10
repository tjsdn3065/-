#ifndef STACK_H
#define STACK_H

#include <iostream>
#define DEFAULTSIZE 5

using namespace std;

template <class KeyType>
class Stack
{
private:
	KeyType* stack;
	int MaxSize;
	int top;
public:
	Stack(int MaxStackSize = DEFAULTSIZE);
	~Stack() { delete[] stack; }
	bool IsFull();
	bool IsEmpty();
	void Push(const KeyType& item);
	KeyType* Pop(KeyType&);
};

void StackFull();
void StackEmpty();

template <class KeyType>
Stack<KeyType>::Stack(int MaxStackSize) :MaxSize(MaxStackSize)
{
	stack = new KeyType[MaxSize];
	top = -1;
}

template <class KeyType>
bool Stack<KeyType>::IsFull()
{
	if (top == MaxSize - 1)
		return true;
	else
		return false;
}

template <class KeyType>
bool Stack<KeyType>::IsEmpty()
{
	if (top == -1)
		return true;
	else
		return false;
}

template <class KeyType>
void Stack<KeyType>::Push(const KeyType& x)
{
	if (IsFull())
		StackFull(); //가득 찼다는 문구 출력
	else
		stack[++top] = x;
}

template <class KeyType>
KeyType* Stack<KeyType>::Pop(KeyType& x)
{
	if (IsEmpty())
	{
		StackEmpty(); //비어있다는 문구 출력
		return 0;
	}
	x = stack[top--];
	return &x;
}


#endif
