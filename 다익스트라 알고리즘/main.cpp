#include "Graph.h"
#include "Priority_Queue.h"
#include <string>

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

int** Make_Adj_Matrix(const char* path, const char* mode, int& vertex_number)
{

	FILE* fp = fopen(path, mode);				// 파일 열기
	if (fp == nullptr)							// 예외 처리
	{
		cout << "파일 열기 실패" << endl;
		return nullptr;
	}

	vertex_number = Return_Num_In_File(fp, '\n');		// vertex 수 읽어오기
	if (vertex_number == -1) {
		fclose(fp);
		return nullptr;
	}

	int** adj = new int* [vertex_number];			// vertex 수만큼 인접행렬 생성
	for (int i = 0; i < vertex_number; i++)
	{
		adj[i] = new int[vertex_number];
	}

	for (int i = 0; i < vertex_number; i++)			// 파일 읽어와서 인접행렬 초기화
	{
		for (int j = 0; j < vertex_number - 1; j++)
		{
			adj[i][j] = Return_Num_In_File(fp, ' ');
		}
		adj[i][vertex_number - 1] = Return_Num_In_File(fp, '\n');
	}

	fclose(fp);										// 파일 닫기

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
	const char* f_path = "5/graph.txt";			// 파일 경로
	const char* mode = "rt";					// 파일 개방 모드
	int vertex_number = 0;						// vertex 수

	int** adj = Make_Adj_Matrix(f_path, mode, vertex_number);			// 파일 읽어서 인접행렬 만들기
	if (adj == nullptr) {
		cout << "인접 행렬 생성 실패" << endl;
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
