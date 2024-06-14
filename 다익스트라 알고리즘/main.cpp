#include "Graph.h"
#include "Priority_Queue.h"
#include <string>

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

int** Make_Adj_Matrix(const char* path, const char* mode, int& vertex_number)
{

	FILE* fp = fopen(path, mode);				// ���� ����
	if (fp == nullptr)							// ���� ó��
	{
		cout << "���� ���� ����" << endl;
		return nullptr;
	}

	vertex_number = Return_Num_In_File(fp, '\n');		// vertex �� �о����
	if (vertex_number == -1) {
		fclose(fp);
		return nullptr;
	}

	int** adj = new int* [vertex_number];			// vertex ����ŭ ������� ����
	for (int i = 0; i < vertex_number; i++)
	{
		adj[i] = new int[vertex_number];
	}

	for (int i = 0; i < vertex_number; i++)			// ���� �о�ͼ� ������� �ʱ�ȭ
	{
		for (int j = 0; j < vertex_number - 1; j++)
		{
			adj[i][j] = Return_Num_In_File(fp, ' ');
		}
		adj[i][vertex_number - 1] = Return_Num_In_File(fp, '\n');
	}

	fclose(fp);										// ���� �ݱ�

	return adj;
}

VERTEX* Dijstra(Graph& G, int& vertex_number)
{
	// INITIALIZE-SINGLE-SOURCE
	VERTEX* V = new VERTEX[vertex_number];
	for (int i = 0; i < vertex_number; i++)
	{
		V[i].vertex = i;
	}
	V[0].d = 0;
	VERTEX* S = new VERTEX[vertex_number];
	Priority_Queue Q(V, vertex_number);
	while (!Q.IsEmpty())
	{
		VERTEX temp = Q.Heap_Extract_Min();
		S[temp.vertex] = temp;
		for (int ptr_vertex = 0; ptr_vertex < vertex_number; ptr_vertex++)
		{
			if (G.Weight(S[temp.vertex].vertex, ptr_vertex) != 0)
			{
				Q.Relax(ptr_vertex, G.Weight(S[temp.vertex].vertex, ptr_vertex), S[temp.vertex].d, S[temp.vertex].vertex);
			}
		}
	}
	delete[] V;
	return S;
}

int main(void)
{
	const char* f_path = "5/graph.txt";			// ���� ���
	const char* mode = "rt";					// ���� ���� ���
	int vertex_number = 0;						// vertex ��

	int** adj = Make_Adj_Matrix(f_path, mode, vertex_number);			// ���� �о ������� �����
	if (adj == nullptr) {
		cout << "���� ��� ���� ����" << endl;
		return -1;
	}

	Graph G(adj,vertex_number);
	G.Get_Path(Dijstra(G, vertex_number));
	G.Show_ShortestPath_and_Distance();

	for (int i = 0; i < vertex_number; i++) 
		delete[] adj[i];
	delete[] adj;

	return 0;
}
