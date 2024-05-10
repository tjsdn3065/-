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

void Path(int m, int p)										//�ܺ��� �� �̷� ũ��
{
	mark[1][1] = 1;											//�Ա����� ����
	Stack<items> stack(m * p);								//m*p��ŭ �޸� ���� �Ҵ���� ����ü �ڷ�������
	items temp = { 1,1,E };									//ó�� Ž���� ������ �Ǵ� ��ǥ�� ����
	stack.Push(temp);										//����ü ������ ���ÿ� Ǫ���ؼ� ������ ������� �ʰ� ��
	while (!stack.IsEmpty())
	{
		temp = *stack.Pop(temp);							//���ο� �̵����� �� ã���� ���ÿ��� ����
		int i = temp.x; int j = temp.y; int d = temp.dir;	//Ž���� ������ �Ǵ� ��ǥ�� ����
		while (d < 8)									
		{
			int g = i + Move[d].a;							//Ž���� �ؼ� �� ��ġ
			int h = j + Move[d].b;							//Ž���� �ؼ� �� ��ġ
			if ((g == m) && (h == p))						//�ⱸ ����
			{
				//cout << stack;								//��� ���
				cout << i << " " << j << endl;				//��λ��� ������ �� ��ġ ���
				cout << m << " " << p << endl;				//�ⱸ ���
				return;
			}
			if ((!maze[g][h]) && (!mark[g][h]))				//���ο� ��ġ ã�Ҵٸ�
			{
				mark[g][h] = 1;								//�Դٰ� ǥ��
				temp.x = i; temp.y = j; temp.dir = d + 1;	//Ž���� �ߴ� ��ġ�� ������ Ž���� ����
				stack.Push(temp);							//���ÿ� Ǫ��
				i = g; j = h; d = N;						//Ž���� ������ �Ǵ� ��ġ ������Ʈ
			}
			else
				d++;										//���ο� ��ġ�� ã�� ���� ���� ����
		}
	}
}


int main(void)
{
	//���� �о �Ա� ���� �ⱸ ���� ������ ���� �б�
	//����Լ��˰���(�� �ȿ� ��� ������ ���Ͽ� ����
	Path(4, 5);
	return 0;
}

