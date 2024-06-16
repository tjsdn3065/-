#include "File.h"

int Return_Num_In_File(FILE* fp, char until_when)
{
	string s_n;
	int c = 0;
	int n = 0;

	while ((c = fgetc(fp)) != EOF)					// ���� �� ���� ������ �б�
	{
		if (c == until_when)						// �������ڸ�ŭ �б�
		{
			break;
		}
		s_n += (char)c;
	}

	if (s_n.empty()) {
		cout << "���� �б� ����" << endl;
		return -1;
	}

	n = stoi(s_n);									// ���ڿ� ������ ��ȯ

	return n;
}

VERTEX** Make_Map(const char* path, const char* mode, const int x_width, const int y_width)
{

	int obstacle_number = 0;
	int left = 0, bottom = 0, right = 0, top = 0;

	VERTEX** map = new VERTEX * [y_width];			// �� ����
	for (int i = 0; i < y_width; i++)
	{
		map[i] = new VERTEX[x_width];
	}

	for (int y = 0; y < y_width; y++)
	{
		for (int x = 0; x < x_width; x++)
		{
			map[y][x].p.x = x;
			map[y][x].p.y = y;
		}
	}

	FILE* fp = fopen(path, mode);				// ���� ����
	if (fp == nullptr)							// ���� ó��
	{
		cout << "���� ���� ����" << endl;
		return nullptr;
	}

	obstacle_number = Return_Num_In_File(fp, '\n');		// ��ֹ� �� �о����
	if (obstacle_number == -1) {
		fclose(fp);
		return nullptr;
	}

	for (int i = 0; i < obstacle_number; i++)
	{
		left = Return_Num_In_File(fp, ' ') - 1;
		bottom = Return_Num_In_File(fp, ' ') - 1;
		right = Return_Num_In_File(fp, ' ');
		top = Return_Num_In_File(fp, '\n');
		for (int y = bottom; y < top; y++)
		{
			for (int x = left; x < right; x++)
			{
				map[y][x].state = STATE::OBSTACLE;
			}
		}
	}

	fclose(fp);										// ���� �ݱ�

	return map;
}

void SavePathToCSV(const string& filename, VERTEX** map, int x_width, int y_width)
{
	ofstream outFile(filename);

	for (int y = 0; y < y_width; y++) {
		for (int x = 0; x < x_width; x++) {
			if (map[y][x].state == STATE::PATH)
				outFile << "P"; // ���
			else if (map[y][x].state == STATE::FINISH)
				outFile << "F"; // Ȯ���Ǿ��� ����
			else if (map[y][x].state == STATE::OBSTACLE)
				outFile << "X"; // ��ֹ�
			else
				outFile << "o"; // �� ����
			if (x < x_width - 1)
				outFile << ",";
		}
		outFile << "\n";
	}

	outFile.close();
}