#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<iostream>

#define INFINITE 2147483647
#define NIL -1

using namespace std;

struct VERTEX
{
	int d = INFINITE;
	int vertex = NIL;
	int from_when = NIL;
};

class Graph
{
private:
	int** adj;
	VERTEX* path;
	int vertex_number;
public:
	Graph(int** pptr, int n);
	int Weight(int row, int col);
	void Get_Path(VERTEX* path);
	void Show_ShortestPath_and_Distance();
	void Get_Shortest_Path(VERTEX vertex);
	~Graph();
};

#endif

