#include <iostream>
#include <string>

#define INFINITE 2147483647
#define PARENT(i) ((i-1)/2)
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)

using namespace std;

struct DATA
{
	char alphabet = 0;
	int freq = 0;
};

struct NODE
{
	DATA c;
	NODE* parent = nullptr;
	NODE* left = nullptr;
	NODE* right = nullptr;
	string code;
};

void EnterString(string& ref)
{
	cout << "문자와 빈도 수를 입력해주세요" << endl;
	getline(cin, ref); // 공백을 포함한 전체 라인 입력
}

bool check_alphabet(const char& ref)
{
	if (ref >= 97 && ref <= 122)  // 97=='a'  122=='z'
		return true;
	else
		return false;
}

bool check_number(const char& ref)
{
	if (ref >= 48 && ref <= 57)  //48=='0' 57=='9'
		return true;
	else
		return false;
}

NODE* Make_C(int& C_length, const string& ref)
{
	for (int i = 0; i < ref.length(); i++)
	{
		if (check_alphabet(ref[i]))
			C_length++;							// 입력된 문자 개수 확인
	}

	NODE* C = new NODE[C_length];				// 입력된 문자 개수만큼 할당받아서 문자의 집합 C 생성 
	if (!C)
	{
		cerr << "메모리 할당 실패" << endl;
		return nullptr;							// 메모리 할당에 실패했을 경우 적절한 처리를 하고 종료
	}
	int n = 0;
	for (int i = 0; i < ref.length() && n < C_length; i++)
	{
		if (check_alphabet(ref[i]))
		{
			C[n].c.alphabet = ref[i];
			i += 2;									 //  ':' 점프 

			if (i >= ref.length())					// 범위 확인
				break;

			while (!check_number(ref[i]))				// 숫자를 만날 때까지 이동
			{
				i++;
			}
			string freq;
			while (check_number(ref[i]))				// 문자열을 정수형태로 변경
			{
				freq += ref[i];
				i++;
			}
			if (!freq.empty()) {
				C[n].c.freq = stoi(freq);
			}
			n++;
		}
	}
	return C;											// 할당된 집합의 주소값 반환
}

void Exchange(NODE& ref1, NODE& ref2)
{
	NODE temp = ref1;
	ref1 = ref2;
	ref2 = temp;
}

class Min_Priority_Queue
{
private:
	NODE* Q;
	int Q_heapsize; // 인덱스
	int Q_length;  // 개수
public:
	Min_Priority_Queue(NODE* ptr,int length):Q(ptr),Q_heapsize(length-1),Q_length(length)
	{
		Build_Min_Heap(Q, Q_heapsize);
	}

	void Min_Heapify(NODE* ptr, int i, int heapsize) // 부모와 자식 비교해서 최소 힙 특성 유지
	{
		int l = LEFT(i);
		int r = RIGHT(i);
		int smallest = i;
		if (l <= heapsize && ptr[l].c.freq < ptr[i].c.freq)
		{
			smallest = l;
		}
		if (r <= heapsize && ptr[r].c.freq < ptr[smallest].c.freq)
		{
			smallest = r;
		}
		if (smallest != i)
		{
			Exchange(ptr[i], ptr[smallest]);
			Min_Heapify(ptr, smallest, heapsize);
		}
	}

	void Build_Min_Heap(NODE* ptr, int heapsize) // 최소 힙으로 만들기
	{
		for (int i = (heapsize-1) / 2; i >= 0; i--) // 마지막 리프 노드의 부모부터 시작
			Min_Heapify(ptr, i, heapsize);
	}

	NODE* Heap_Extract_Min()						// 빈도 수가 가장 작은 노드 추출
	{
		if (Q_heapsize < 0)
			throw std::out_of_range("Heap is empty");
		NODE* child = new NODE;						// 추출한 노드를 새로 할당한 노드에 저장
		*child = Q[0];
		Q[0]=Q[Q_heapsize];
		Q[Q_heapsize].c.freq = INFINITE;			// 무한대로 변경
		Q_heapsize = Q_heapsize - 1;				//노드 1개 제외 시켰으니 1 감소
		Min_Heapify(Q, 0, Q_heapsize);
		return child;								// 새로 할당한 노드 주소 반환
	}

	void Heap_Decrease_Key()						// 새로운 노드 재배치
	{
		int i = Q_heapsize;
		while (i>0 && Q[PARENT(i)].c.freq > Q[i].c.freq)
		{
			Exchange(Q[i], Q[PARENT(i)]);
			i = PARENT(i);
		}
	}

	void Min_Heap_Insert(NODE& ref)					// 새로운 노드 삽입
	{
		Q_heapsize++;
		Q[Q_heapsize]=ref;
		ref.left->parent = &Q[Q_heapsize];
		ref.right->parent = &Q[Q_heapsize];
		Heap_Decrease_Key();
	}
};

class Binary_Tree
{
private:
	NODE* tree;
public:
	Binary_Tree() :tree(nullptr) {}

	void DeleteNode(NODE* ptr)						// 추출할 때 
	{
		if (ptr == nullptr)
			return;
		if (ptr->parent!= nullptr)   // 루트 노드 뼤고 나머지 반환
		{
			DeleteNode(ptr->left);
			DeleteNode(ptr->right);
			delete ptr;
		}
		else
		{
			delete[] ptr;			// 루트 노드 반환
		}
	}

	void OutputCode(NODE* ptr)
	{
		if (ptr==nullptr)
			return;
		if (ptr != nullptr && ptr->c.alphabet == 0)			// 새롭게 만들었던 노드
		{
			ptr->left->code = ptr->code;					// 자식들에게 코드 물려주기
			ptr->left->code += '0';							// 왼쪽 자식에겐 0 추가
			ptr->right->code = ptr->code;
			ptr->right->code += '1';						// 오른쪽 자식에겐 0 추가
			OutputCode(ptr->left);
			OutputCode(ptr->right);
		}
		else												// 리프 노드(문자 집합 구성원) 이면 알파벳과 빈도 수 출력
			cout << ptr->c.alphabet << ": " << ptr->code << endl;
	}
};

void Huffman(NODE* C, int C_length)
{
	Min_Priority_Queue Q(C, C_length);				// 최소 우선순위 Q 생성 (집합 C를 가리키는)
	for (int i = 0; i < C_length -1 ; i++)
	{
		NODE new_node;								// 새로운 노드 생성
		new_node.left = Q.Heap_Extract_Min();					// 새로운 노드 왼쪽 자식에게 지금 이 순간 가장 작은 놈을 할당
		new_node.right = Q.Heap_Extract_Min();					// 새로운 노드 오른쪽 자식에게 지금 이 순간 가장 작은 놈을 할당
		new_node.c.freq = new_node.left->c.freq + new_node.right->c.freq;		// 왼쪽 오른쪽 빈도 수 합을 새로운 노드 빈도 수에 대입
		Q.Min_Heap_Insert(new_node);				// 새로운 노드 우선순위 큐에 삽입
	}
}

void Output(NODE* C, int& C_length)
{
	Huffman(C, C_length);
	Binary_Tree tree;						// tree 객체 생성
	tree.OutputCode(C);						// code 출력
	tree.DeleteNode(C);						// 메모리 반환
}

int main(void)
{
	string s;
	EnterString(s);					// 문자열 입력
	int C_length = 0;				// 문자 집합 C 크기 변수
	NODE* C=Make_C(C_length, s);	// 문자 집합 C 생성, 문자 집합 C 크기 체크
	if (!C)							// 할당 실패 처리
		return -1;
	Output(C, C_length);			// 각 문자의 할당된 code 출력
	return 0;
}