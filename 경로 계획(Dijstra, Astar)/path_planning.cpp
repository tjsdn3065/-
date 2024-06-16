#include "path_planning.h"

void Initialize_Single_Soure(string path_planning, Graph& G, int x_start, int y_start, int x_goal, int y_goal)
{
	VERTEX* s = G.Get_Vertex();
	s[0].p = { x_start,y_start };
	s[0].d_from_start = 0.0;
	if (path_planning == "Dijstra")
		s[0].d = s[0].d_from_start;
	else if (path_planning == "Astar")
	{
		s[0].d_to_goal = (x_goal - x_start) + (y_goal - y_start);
		s[0].d = s[0].d_from_start + s[0].d_to_goal;
	}
	s[0].state = STATE::DISCOVER;
}

void Relax(string path_planning, Graph& G, Priority_Queue& Q, VERTEX& v_adj, VERTEX& v_cur, double w, int x_goal, int y_goal)
{
	VERTEX* temp_Q = Q.Get_Q();
	int temp_Q_heapsize = Q.Get_Q_heapsize();
	bool is_updated = false;

	if (v_adj.state == STATE::DISCOVER)
	{
		if (path_planning == "Dijstra")
		{
			if (v_adj.d > v_cur.d + w)
			{
				is_updated = true;
				v_adj.d = v_cur.d + w;
			}
		}
		else if (path_planning == "Astar")
		{
			if (v_adj.d > v_cur.d_from_start + w + v_adj.d_to_goal)
			{
				is_updated = true;
				v_adj.d_from_start = v_cur.d_from_start + w;
				v_adj.d = v_adj.d_from_start + v_adj.d_to_goal;
			}
		}
		if (is_updated == true)				// 업데이트가 되었다면 적용
		{
			v_adj.from_when = G.Cvt_2dim_index_to_1dim_index(v_cur.p.x, v_cur.p.y);
			for (int i = 0; i < temp_Q_heapsize + 1; i++)
			{
				if (temp_Q[i].p.x == v_adj.p.x && temp_Q[i].p.y == v_adj.p.y)
				{
					temp_Q[i] = v_adj;
					Q.Heap_Decrease_Key(i);
				}
			}
		}
	}
	else if (v_adj.state == STATE::NOT_DISCOVER)
	{
		v_adj.d_from_start = v_cur.d_from_start + w;

		if (path_planning == "Dijstra")
		{
			v_adj.d = v_adj.d_from_start;
		}
		else if (path_planning == "Astar")
		{
			v_adj.d_to_goal = (x_goal - v_adj.p.x) + (y_goal - v_adj.p.y);
			v_adj.d = v_adj.d_from_start + v_adj.d_to_goal;
		}
		v_adj.from_when = G.Cvt_2dim_index_to_1dim_index(v_cur.p.x, v_cur.p.y);
		v_adj.state = STATE::DISCOVER;
		Q.Min_Heap_Insert(v_adj);
	}
}

VERTEX* Path_Planning(string path_planning, Graph& G, int x_width, int y_width, int x_start, int y_start, int x_goal, int y_goal)
{
	// 타이머 시작
	auto start = high_resolution_clock::now();

	VERTEX** map = G.GET_Map();
	EDGE* E = G.Get_Edge();

	Initialize_Single_Soure(path_planning, G, x_start, y_start, x_goal, y_goal);

	VERTEX* S = new VERTEX[x_width * y_width];			// 확정된 정점 집합

	Priority_Queue Q(G.Get_Vertex());		// 발견된 정점 집합

	while (!Q.IsEmpty())
	{
		VERTEX v_cur = Q.Heap_Extract_Min();
		v_cur.state = STATE::FINISH;
		map[v_cur.p.y][v_cur.p.x].state = v_cur.state;
		S[G.Cvt_2dim_index_to_1dim_index(v_cur.p.x, v_cur.p.y)] = v_cur;
		if (v_cur.p.x == x_goal && v_cur.p.y == y_goal)						// 목표에 도달하면 반복문 탈출
			break;
		for (int i = 0; i < DIRECTION::TOTAL; i++)							// 모든 방향에 대해 업데이트
		{
			if (0 > v_cur.p.y + E[i].dir.y || y_width - 1 < v_cur.p.y + E[i].dir.y || 0 > v_cur.p.x + E[i].dir.x || x_width - 1 < v_cur.p.x + E[i].dir.x)	// 맵 벗어나면 패스
				continue;

			VERTEX& v_adj = map[v_cur.p.y + E[i].dir.y][v_cur.p.x + E[i].dir.x];
			if (v_adj.state == STATE::FINISH || v_adj.state == STATE::OBSTACLE)		// 확정된 정점이거나 장애물이면 패스
				continue;
			else
				Relax(path_planning, G, Q, v_adj, v_cur, E[i].w,x_goal,y_goal);
		}
	}

	// 타이머 종료
	auto stop = high_resolution_clock::now();

	// 경과 시간 계산
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "수행 시간: " << duration.count() << " 마이크로초" << endl;
	return S;
}

void Map_Final_Path(VERTEX** map, VERTEX& v, int x_width)
{
	if (v.p.x == 0 && v.p.y == 0)
	{
		v.state = STATE::PATH;
		return;
	}
	Map_Final_Path(map, map[v.from_when / x_width][v.from_when % x_width], x_width);
	v.state = STATE::PATH;
}

void Map_Update_Final_Path(VERTEX** map, int x_width)
{
	Map_Final_Path(map, map[19][19], x_width);
}
