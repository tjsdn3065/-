#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define LENGTH 100

void RandomArray(int* A);
void Input(int* A, int* method, int* order);
void Sort(int* A, int* method, int* order);
bool Option(int* order, int a, int key);
void InsertionSort(int* A, int* order);
void MergeSort(int* A, int* order, int top, int bottom);
void Merge(int* A, int* order, int top, int mid, int bottom);
void Output(int* A);


int main()
{
	int A[LENGTH] = { 0 };
	int method = 0;  // 0: Insertion,  1: Merge
	int order = 0; // 0: ascending, 1: descending
	Input(A, &method, &order);  // 난수 발생, method / order 사용자 입력
	Sort(A, &method, &order);    // InsertionSort 및 MergeSort 함수 호출 , 단 오름차순/내림차순을 하나의 함수로 처리  
	Output(A);
	return 0;
}

void RandomArray(int* A)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < LENGTH; i++)
		A[i] = (rand() % 1000) + 1;
}

void Input(int* A, int* method, int* order)
{
	RandomArray(A);
	cout << "0은 Insertion 1은 Merge" << endl;
	cin >> *method;
	cout << "0은 ascending 1은 descending" << endl;
	cin >> *order;
}

void Sort(int* A, int* method, int* order)
{
	if (*method == 0)
		InsertionSort(A, order);
	else
		MergeSort(A, order,0,LENGTH-1);
}

bool Option(int* order, int a, int key)
{
	if (*order == 0)
		return (a >= key);
	else
		return (a < key);
}

void InsertionSort(int* A,int* order)
{
	for (int j = 1; j < LENGTH; j++)
	{
		int key = A[j];
		int i = j - 1;
		while ((i >= 0) && Option(order,A[i],key))
		{
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
}

void MergeSort(int* A, int* order,int top,int bottom)
{
	if (top < bottom)
	{
		int mid = (top + bottom) / 2;
		MergeSort(A, order, top, mid);
		MergeSort(A, order, mid+1, bottom);
		Merge(A, order, top, mid, bottom);
	}
}

void Merge(int* A, int* order, int top, int mid, int bottom)
{
	int n1 = mid - top + 1;
	int n2 = bottom - mid;
	int* L = new int[n1 + 1];
	int* R = new int[n2 + 1];
	int i = 0;
	int j = 0;
	for ( i ; i < n1; i++)
		L[i] = A[top + i];
	for ( j ; j < n2; j++)
		R[j] = A[mid + j+1];
	L[n1] = (*order == 0) ? 1001 : 0;
	R[n2] = (*order == 0) ? 1001 : 0;
	i = 0;
	j = 0;
	for (int k = top; k <= bottom ; k++)
	{
		if (Option(order, R[j], L[i]))
			A[k] = L[i++];
		else
			A[k] = R[j++];
	}
	delete[] L;
	delete[] R;
}

void Output(int* A)
{
	for (int i = 0; i < 100; i++)
		cout << A[i] << ' ';
}