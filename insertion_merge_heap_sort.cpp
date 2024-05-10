#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define LENGTH 100
#define A_INDEX_LENGTH 99
#define PARENT(i) (i/2)
#define LEFT(i) (2*i)
#define RIGHT(i) (2*i+1)

void RandomArray(int* A);
void Input(int* A, int& method, int& order);
void Sort(int* A, int& method, int& order);
bool Option(int& order, int& ref1, int& ref2);
void InsertionSort(int* A, int& order);
void MergeSort(int* A, int& order, int top, int bottom);
void Merge(int* A, int& order, int top, int mid, int bottom);
void Exchange(int& ref1, int& ref2);
void HeapSort(int* A,int& order);
void Build_Heap(int* A, int& A_heapsize, int& order);
void Heapify(int* A, int i, int& A_heapsize, int& order);
void Output(int* A);


int main()
{
	int A[LENGTH] = { 0 };
	int method = 0;  // 0: Insertion,  1: Merge, 2: Heap
	int order = 0; // 0: ascending, 1: descending
	
	Input(A, method, order);  // 난수 발생, method / order 사용자 입력
	Sort(A, method, order);    // InsertionSort,  MergeSort, HeapSort 함수 호출 , 단 오름차순/내림차순을 하나의 함수로 처리  
	Output(A);

	return 0;
}

void RandomArray(int* A)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < LENGTH; i++)
		A[i] = (rand() % 1000) + 1;
}

void Input(int* A, int& method, int& order)
{
	RandomArray(A);
	cout << "0은 Insertion 1은 Merge 2는 Heap" << endl;
	cin >> method;
	cout << "0은 ascending 1은 descending" << endl;
	cin >> order;
}

void Sort(int* A, int& method, int& order)
{
	if (method == 0)
		InsertionSort(A, order);
	else if (method == 1)
		MergeSort(A, order, 0, A_INDEX_LENGTH);
	else
		HeapSort(A, order);
}

bool Option(int& order, int& ref1, int& ref2)
{
	if (order == 0)
		return (ref1 >= ref2);
	else
		return (ref1 < ref2);
}

void InsertionSort(int* A, int& order)
{
	for (int j = 1; j < LENGTH; j++)
	{
		int key = A[j];
		int i = j - 1;
		while ((i >= 0) && Option(order, A[i], key))
		{
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
}

void MergeSort(int* A, int& order, int top, int bottom)
{
	if (top < bottom)
	{
		int mid = (top + bottom) / 2;
		MergeSort(A, order, top, mid);
		MergeSort(A, order, mid + 1, bottom);
		Merge(A, order, top, mid, bottom);
	}
}

void Merge(int* A, int& order, int top, int mid, int bottom)
{
	int n1 = mid - top + 1;
	int n2 = bottom - mid;
	int* L = new int[n1 + 1];
	int* R = new int[n2 + 1];
	int i = 0;
	int j = 0;
	for (i; i < n1; i++)
		L[i] = A[top + i];
	for (j; j < n2; j++)
		R[j] = A[mid + j + 1];
	L[n1] = (order == 0) ? 1001 : 0;
	R[n2] = (order == 0) ? 1001 : 0;
	i = 0;
	j = 0;
	for (int k = top; k <= bottom; k++)
	{
		if (Option(order, R[j], L[i]))
			A[k] = L[i++];
		else
			A[k] = R[j++];
	}
	delete[] L;
	delete[] R;
}

void Exchange(int& ref1, int& ref2)
{
	int temp = ref1;
	ref1 = ref2;
	ref2 = temp;
}

void HeapSort(int* A, int& order)
{
	int A_heapsize = 0;
	Build_Heap(A, A_heapsize,order);
	for (int i = A_INDEX_LENGTH; i > 0; i--)
	{
		Exchange(A[0], A[i]);
		A_heapsize--;
		Heapify(A, 0, A_heapsize,order);
	}
}

void Build_Heap(int* A,int& A_heapsize, int& order)
{	
	A_heapsize = A_INDEX_LENGTH;
	for (int i = (A_INDEX_LENGTH) / 2; i >= 0; i--)
		Heapify(A, i, A_heapsize,order);
}

void Heapify(int* A, int i, int& A_heapsize,int& order)
{
	int l = LEFT(i);
	int r = RIGHT(i);
	int n = 0;
	if (l <= A_heapsize && Option(order,A[l],A[i]))
		n = l;
	else
		n = i;
	if (r <= A_heapsize && Option(order, A[r], A[n]))
		n = r;
	if (n != i)
	{
		Exchange(A[i], A[n]);
		Heapify(A, n, A_heapsize,order);
	}
}

void Output(int* A)
{
	for (int i = 0; i < 100; i++)
		cout << A[i] << ' ';
}