#include "Graph.h"



Graph::Graph(int** pptr, int n) :adj(pptr), path(nullptr), vertex_number(n) {}

int Graph::Weight(int row, int col)
{
	return adj[row][col];
}
void Graph::Get_Path(VERTEX* path)
{
	this->path = path;
}
void Graph::Show_ShortestPath_and_Distance()
{
	for (int i = 1; i < vertex_number; i++)
	{
		Get_Shortest_Path(path[path[i].from_when]);
		cout << path[i].vertex+1;
		cout << " : " << path[i].d << endl;
	}
}
void Graph::Get_Shortest_Path(VERTEX vertex)
{
	if (vertex.from_when != NIL)
		Get_Shortest_Path(path[vertex.from_when]);
	cout << vertex.vertex + 1 << " -> ";
}
Graph::~Graph()
{
	delete[] path;
}
