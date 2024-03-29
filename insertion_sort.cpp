#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define LENGTH 100

int* RandomArray(int* A);
void Choice(int* A);
void AscendingInsertionSort(int* A);
void DescendingInsertionSort(int* A);
void Result(int* A);


int main()
{
	int A[100];
	Choice(RandomArray(A));
	return 0;
}

int* RandomArray(int* A)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100; i++)
		A[i] = (rand() % 1000) + 1;
	return A;
}

void Choice(int *A)
{
	cout << "1은 오름차순 2은 내림차순" << endl;
	int a;
	cin >> a;
	while (a != 1 && a != 2)
	{
		cout << "다시 입력바람" << endl;
		cin >> a;
	}
	if (a == 1)
		AscendingInsertionSort(A);
	else
		DescendingInsertionSort(A);
}

void AscendingInsertionSort(int* A)
{
	for (int j = 1; j < LENGTH; j++)
	{
		int key = A[j];
		int i = j - 1;
		while ((i >= 0) && (A[i] > key))
		{
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
	Result(A);
}
void DescendingInsertionSort(int* A)
{
	for (int j = 1; j < LENGTH; j++)
	{
		int key = A[j];
		int i = j - 1;
		while ((i >= 0) && (A[i] < key))
		{
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
	Result(A);
}

void Result(int* A)
{
	for (int i = 0; i < LENGTH; i++)
		cout << A[i] << ' ';
}