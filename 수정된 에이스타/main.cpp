#include "path_planning.h"

void Choice_Path_planning(string& path_planning)
{
	int n = 0;
	cout << "1: Dijstra    2: Astar" << endl;
	cin >> n;
	if (n == 1)
		path_planning = "Dijstra";
	else if (n == 2)
		path_planning = "Astar";
}

int main(void)
{
	const char* f_path = "5/map.txt";			// 파일 경로
	const char* mode = "rt";					// 파일 개방 모드

	string path_planning;
	int x_width = 20, y_width = 20;
	int x_start = 0, y_start = 0;
	int x_goal = 19, y_goal = 19;

	VERTEX** map=Make_Map(f_path, mode, x_width, y_width);
	if (map == nullptr)
	{
		return -1;
	}

	Choice_Path_planning(path_planning);

	Graph G(map, x_width, y_width);
	G.Get_Path(Path_Planning(path_planning, G, x_width, y_width, x_start,y_start,x_goal,y_goal));
	G.Show_ShortestPath_and_Distance(x_start, y_start, x_goal, y_goal);

	Map_Update_Final_Path(map, x_width, y_width);
	SavePathToCSV("result.txt", map, x_width, y_width);

	G.~Graph();

	return 0;
}
