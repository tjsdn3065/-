#include "Graph.h"

Graph::Graph(VERTEX** map, int x_width, int y_width) :map(map), path(nullptr), x_width(x_width), y_width(y_width)
{
	V = new VERTEX[x_width * y_width];
	for (int y = 0; y < y_width; y++)
	{
		for (int x = 0; x < x_width; x++)
		{
			V[y * y_width + x] = map[y][x];
		}
	}

	double sqrt_2 = sqrt(2);

	E = new EDGE[DIRECTION::TOTAL];
	E[DIRECTION::N].dir = { 0, 1 };
	E[DIRECTION::N].w = 1.0;
	E[DIRECTION::NE].dir = { 1,1 };
	E[DIRECTION::NE].w = sqrt_2;
	E[DIRECTION::E].dir = { 1,0 };
	E[DIRECTION::E].w = 1.0;
	E[DIRECTION::SE].dir = { 1,-1 };
	E[DIRECTION::SE].w = sqrt_2;
	E[DIRECTION::S].dir = { 0,-1 };
	E[DIRECTION::S].w = 1.0;
	E[DIRECTION::SW].dir = { -1,-1 };
	E[DIRECTION::SW].w = sqrt_2;
	E[DIRECTION::W].dir = { -1,0 };
	E[DIRECTION::W].w = 1.0;
	E[DIRECTION::NW].dir = { -1,1 };
	E[DIRECTION::NW].w = sqrt_2;
}

VERTEX** Graph::GET_Map()
{
	return map;
}

VERTEX* Graph::Get_Vertex()
{
	return V;
}
EDGE* Graph::Get_Edge()
{
	return E;
}

void Graph::Get_Path(VERTEX* path)
{
	this->path = path;
}
int Graph::Cvt_2dim_index_to_1dim_index(int x, int y)
{
	return y * x_width + x;
}

void Graph::Show_ShortestPath_and_Distance(int x_start, int y_start, int x_goal, int y_goal)
{
	Get_Shortest_Path(path[path[Cvt_2dim_index_to_1dim_index(x_goal, y_goal)].from_when], x_start, y_start);
	cout << '(' << path[Cvt_2dim_index_to_1dim_index(x_goal, y_goal)].p.x + 1 << ',' << path[Cvt_2dim_index_to_1dim_index(x_goal, y_goal)].p.y + 1 << ')' << " : " << path[Cvt_2dim_index_to_1dim_index(x_goal, y_goal)].d_from_start << endl;
}
void Graph::Get_Shortest_Path(VERTEX vertex, int x_start, int y_start)
{
	if (vertex.p.x == x_start && vertex.p.y == y_start)
	{
		cout << '(' << vertex.p.x + 1 << ',' << vertex.p.y + 1 << ')' << " -> ";
		return;
	}
	else
	{
		Get_Shortest_Path(path[vertex.from_when], x_start, y_start);
		cout << '(' << vertex.p.x + 1 << ',' << vertex.p.y + 1 << ')' << " -> ";
		return;
	}
}
Graph::~Graph()
{
	for (int i = 0; i < y_width; i++)
		delete[] map[i];
	delete[] map;
	delete[] V;
	delete[] E;
	delete[] path;
}