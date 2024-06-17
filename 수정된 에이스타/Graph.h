#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<iostream>
#include <limits>
#include<cmath>

using namespace std;

enum STATE
{
	NOT_DISCOVER, DISCOVER, FINISH, OBSTACLE, PATH
};

enum DIRECTION
{
	N, NE, E, SE, S, SW, W, NW, TOTAL
};

struct POINT
{
	int x;
	int y;
};

struct VERTEX
{
	POINT p;
	double d = numeric_limits<double>::max();
	double d_from_start = 0.0;
	double d_to_goal = 0.0;
	double d_to_center = 0.0;
	double direction=0.0;
	int from_when = 0;
	int state = STATE::NOT_DISCOVER;
};

struct EDGE
{
	POINT dir;
	double w;
};

class Graph
{
private:
	VERTEX** map;
	VERTEX* V;
	EDGE* E;
	VERTEX* path;
	int x_width;
	int y_width;
public:
	Graph(VERTEX** map, int x_width, int y_width);
	VERTEX** GET_Map();
	VERTEX* Get_Vertex();
	EDGE* Get_Edge();
	int Cvt_2dim_index_to_1dim_index(int x, int y);
	void Get_Path(VERTEX* path);
	void Show_ShortestPath_and_Distance(int x_start, int y_start, int x_goal, int y_goal);
	void Get_Shortest_Path(VERTEX vertex, int x_start, int y_start);
	~Graph();
};

#endif