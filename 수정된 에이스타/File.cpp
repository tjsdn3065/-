#include "File.h"

int Return_Num_In_File(FILE* fp, char until_when)
{
	string s_n;
	int c = 0;
	int n = 0;

	while ((c = fgetc(fp)) != EOF)					// 읽을 수 없을 때까지 읽기
	{
		if (c == until_when)						// 전달인자만큼 읽기
		{
			break;
		}
		s_n += (char)c;
	}

	if (s_n.empty()) {
		cout << "파일 읽기 실패" << endl;
		return -1;
	}

	n = stoi(s_n);									// 문자열 정수로 변환

	return n;
}

VERTEX** Make_Map(const char* path, const char* mode, const int x_width, const int y_width)
{

	int obstacle_number = 0;
	int left = 0, bottom = 0, right = 0, top = 0;

	VERTEX** map = new VERTEX * [y_width];			// 맵 생성
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

	FILE* fp = fopen(path, mode);				// 파일 열기
	if (fp == nullptr)							// 예외 처리
	{
		cout << "파일 열기 실패" << endl;
		return nullptr;
	}

	obstacle_number = Return_Num_In_File(fp, '\n');		// 장애물 수 읽어오기
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

	fclose(fp);										// 파일 닫기

	return map;
}

void SavePathToCSV(const string& filename, VERTEX** map, int x_width, int y_width)
{
	ofstream outFile(filename);

	for (int y = 0; y < y_width; y++) {
		for (int x = 0; x < x_width; x++) {
			if (map[y][x].state == STATE::PATH)
				outFile << "P"; // 경로
			else if (map[y][x].state == STATE::FINISH)
				outFile << "F"; // 확정되었던 정점
			else if (map[y][x].state == STATE::OBSTACLE)
				outFile << "X"; // 장애물
			else
				outFile << "o"; // 빈 공간
			if (x < x_width - 1)
				outFile << ",";
		}
		outFile << "\n";
	}

	outFile.close();
}