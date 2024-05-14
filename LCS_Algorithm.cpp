#include <iostream>
#include <string>

using namespace std;

enum DIRECTION
{
	DIAGONAL=1,
	UP = 2,
	LEFT = 3
};

struct LCSResult
{
	int** c;
	int** b;
};

bool StringCheck(string& ref)
{
	for (int i = 0; i < ref.length(); i++)
		if (ref[i] != 'A' && ref[i] != 'C' && ref[i] != 'G' && ref[i] != 'T')
		{
			cout << "오류" << endl;
			cout << "A C G T 중에서 입력해주세요" << endl;
			return false;
		}
	return true;
}

void EnterString(string& X,string& Y)
{
	cout << "A C G T 로 구성된 문자열을 입력해주세요" << endl;
	bool n=false;
	while (!n)
	{
		cout << "X 입력: ";
		cin >> X;
		n=StringCheck(X);
	}
	n = false;
	while (!n)
	{
		cout << "Y 입력: ";
		cin >> Y;
		n = StringCheck(Y);
	}
}

void LCS_DynamicAllocation(LCSResult& ref,int row,int col)
{
	ref.b = new int* [row + 1];
	ref.c = new int* [row + 1];

	for (int i = 0; i < row + 1; i++)
	{
		ref.b[i] = new int[col + 1];
		ref.c[i] = new int[col + 1];
		ref.b[i][0] = 0;
		ref.c[i][0] = 0;
	}
	for (int i = 1; i < col + 1; i++)
	{
		ref.b[0][i] = 0;
		ref.c[0][i] = 0;
	}
}

void LCS_Delete(LCSResult& ref, int r)
{
	for (int i = 0; i < r + 1; i++)
	{
		delete[] ref.c[i];
		delete[] ref.b[i];
	}
	delete[] ref.c;
	delete[] ref.b;
}

void LCS_Length(LCSResult& ref,const string& X,const string Y, int row, int col)
{
		
	for (int i = 1; i < row + 1; i++)
	{
		for (int j = 1; j < col + 1; j++)
		{
			if (X[i-1] == Y[j-1])
			{
				ref.c[i][j] = ref.c[i - 1][j - 1] + 1;
				ref.b[i][j] = DIRECTION::DIAGONAL;
			}
			else if (ref.c[i - 1][j] >= ref.c[i][j - 1])
			{
				ref.c[i][j] = ref.c[i - 1][j];
				ref.b[i][j] = DIRECTION::UP;
			}
			else
			{
				ref.c[i][j] = ref.c[i][j - 1];
				ref.b[i][j] = DIRECTION::LEFT;
			}
		}
	}
	cout << "LCS의 길이: " << ref.c[row][col]<<endl;
}

void Print_LCS(int** b,const string& X,int row,int col)
{
	if (row == 0 || col == 0)
		return;
	if (b[row][col] == DIRECTION::DIAGONAL)
	{
		Print_LCS(b, X, row - 1, col - 1);
		cout << X[row-1];
	}
	else if (b[row][col] == DIRECTION::UP)
		Print_LCS(b, X, row - 1, col);
	else
		Print_LCS(b, X, row, col - 1);
}

int main(void)
{
	string X, Y;
	EnterString(X, Y);
	int row = X.length();
	int col = Y.length();
	LCSResult LCS;
	LCS_DynamicAllocation(LCS,row,col);
	LCS_Length(LCS,X, Y,row,col);
	Print_LCS(LCS.b, X, row, col);
	LCS_Delete(LCS, row);
	return 0;
}