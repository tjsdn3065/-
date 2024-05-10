#include "stack.h"


enum directions { N, NE, E, SE, S, SW, W, NW };

struct offset
{
	int a, b;
};
offset Move[8] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };



struct items
{
	int x, y, dir;
};

int mark[6][7] = { 0 };
int maze[6][7] =
{
	{1,1,1,1,1,1,1},
	{1,0,0,0,0,0,1},
	{1,1,1,0,1,1,1},
	{1,1,1,0,1,1,1},
	{1,1,1,0,0,0,1},
	{1,1,1,1,1,1,1}
};

void Path(int m, int p)										//외벽을 뺀 미로 크기
{
	mark[1][1] = 1;											//입구에서 시작
	Stack<items> stack(m * p);								//m*p만큼 메모리 공간 할당받음 구조체 자료형으로
	items temp = { 1,1,E };									//처음 탐색의 기준이 되는 좌표와 방향
	stack.Push(temp);										//구조체 변수를 스택에 푸시해서 스택이 비어있지 않게 함
	while (!stack.IsEmpty())
	{
		temp = *stack.Pop(temp);							//새로운 이동점을 못 찾으면 스택에서 삭제
		int i = temp.x; int j = temp.y; int d = temp.dir;	//탐색의 기준이 되는 좌표와 방향
		while (d < 8)									
		{
			int g = i + Move[d].a;							//탐색을 해서 갈 위치
			int h = j + Move[d].b;							//탐색을 해서 갈 위치
			if ((g == m) && (h == p))						//출구 도착
			{
				//cout << stack;								//경로 출력
				cout << i << " " << j << endl;				//경로상의 마지막 두 위치 출력
				cout << m << " " << p << endl;				//출구 출력
				return;
			}
			if ((!maze[g][h]) && (!mark[g][h]))				//새로운 위치 찾았다면
			{
				mark[g][h] = 1;								//왔다고 표시
				temp.x = i; temp.y = j; temp.dir = d + 1;	//탐색을 했던 위치와 다음의 탐색할 방향
				stack.Push(temp);							//스택에 푸시
				i = g; j = h; d = N;						//탐색의 기준이 되는 위치 업데이트
			}
			else
				d++;										//새로운 위치를 찾기 위해 방향 증가
		}
	}
}


int main(void)
{
	//파일 읽어서 입구 정보 출구 정보 메이즈 정보 읽기
	//경로함수알고리즘(이 안에 경로 각각을 파일에 쓰기
	Path(4, 5);
	return 0;
}

