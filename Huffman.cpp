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
	cout << "���ڿ� �� ���� �Է����ּ���" << endl;
	getline(cin, ref); // ������ ������ ��ü ���� �Է�
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
			C_length++;							// �Էµ� ���� ���� Ȯ��
	}

	NODE* C = new NODE[C_length];				// �Էµ� ���� ������ŭ �Ҵ�޾Ƽ� ������ ���� C ���� 
	if (!C)
	{
		cerr << "�޸� �Ҵ� ����" << endl;
		return nullptr;							// �޸� �Ҵ翡 �������� ��� ������ ó���� �ϰ� ����
	}
	int n = 0;
	for (int i = 0; i < ref.length() && n < C_length; i++)
	{
		if (check_alphabet(ref[i]))
		{
			C[n].c.alphabet = ref[i];
			i += 2;									 //  ':' ���� 

			if (i >= ref.length())					// ���� Ȯ��
				break;

			while (!check_number(ref[i]))				// ���ڸ� ���� ������ �̵�
			{
				i++;
			}
			string freq;
			while (check_number(ref[i]))				// ���ڿ��� �������·� ����
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
	return C;											// �Ҵ�� ������ �ּҰ� ��ȯ
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
	int Q_heapsize; // �ε���
	int Q_length;  // ����
public:
	Min_Priority_Queue(NODE* ptr,int length):Q(ptr),Q_heapsize(length-1),Q_length(length)
	{
		Build_Min_Heap(Q, Q_heapsize);
	}

	void Min_Heapify(NODE* ptr, int i, int heapsize) // �θ�� �ڽ� ���ؼ� �ּ� �� Ư�� ����
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

	void Build_Min_Heap(NODE* ptr, int heapsize) // �ּ� ������ �����
	{
		for (int i = (heapsize-1) / 2; i >= 0; i--) // ������ ���� ����� �θ���� ����
			Min_Heapify(ptr, i, heapsize);
	}

	NODE* Heap_Extract_Min()						// �� ���� ���� ���� ��� ����
	{
		if (Q_heapsize < 0)
			throw std::out_of_range("Heap is empty");
		NODE* child = new NODE;						// ������ ��带 ���� �Ҵ��� ��忡 ����
		*child = Q[0];
		Q[0]=Q[Q_heapsize];
		Q[Q_heapsize].c.freq = INFINITE;			// ���Ѵ�� ����
		Q_heapsize = Q_heapsize - 1;				//��� 1�� ���� �������� 1 ����
		Min_Heapify(Q, 0, Q_heapsize);
		return child;								// ���� �Ҵ��� ��� �ּ� ��ȯ
	}

	void Heap_Decrease_Key()						// ���ο� ��� ���ġ
	{
		int i = Q_heapsize;
		while (i>0 && Q[PARENT(i)].c.freq > Q[i].c.freq)
		{
			Exchange(Q[i], Q[PARENT(i)]);
			i = PARENT(i);
		}
	}

	void Min_Heap_Insert(NODE& ref)					// ���ο� ��� ����
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

	void DeleteNode(NODE* ptr)						// ������ �� 
	{
		if (ptr == nullptr)
			return;
		if (ptr->parent!= nullptr)   // ��Ʈ ��� ���� ������ ��ȯ
		{
			DeleteNode(ptr->left);
			DeleteNode(ptr->right);
			delete ptr;
		}
		else
		{
			delete[] ptr;			// ��Ʈ ��� ��ȯ
		}
	}

	void OutputCode(NODE* ptr)
	{
		if (ptr==nullptr)
			return;
		if (ptr != nullptr && ptr->c.alphabet == 0)			// ���Ӱ� ������� ���
		{
			ptr->left->code = ptr->code;					// �ڽĵ鿡�� �ڵ� �����ֱ�
			ptr->left->code += '0';							// ���� �ڽĿ��� 0 �߰�
			ptr->right->code = ptr->code;
			ptr->right->code += '1';						// ������ �ڽĿ��� 0 �߰�
			OutputCode(ptr->left);
			OutputCode(ptr->right);
		}
		else												// ���� ���(���� ���� ������) �̸� ���ĺ��� �� �� ���
			cout << ptr->c.alphabet << ": " << ptr->code << endl;
	}
};

void Huffman(NODE* C, int C_length)
{
	Min_Priority_Queue Q(C, C_length);				// �ּ� �켱���� Q ���� (���� C�� ����Ű��)
	for (int i = 0; i < C_length -1 ; i++)
	{
		NODE new_node;								// ���ο� ��� ����
		new_node.left = Q.Heap_Extract_Min();					// ���ο� ��� ���� �ڽĿ��� ���� �� ���� ���� ���� ���� �Ҵ�
		new_node.right = Q.Heap_Extract_Min();					// ���ο� ��� ������ �ڽĿ��� ���� �� ���� ���� ���� ���� �Ҵ�
		new_node.c.freq = new_node.left->c.freq + new_node.right->c.freq;		// ���� ������ �� �� ���� ���ο� ��� �� ���� ����
		Q.Min_Heap_Insert(new_node);				// ���ο� ��� �켱���� ť�� ����
	}
}

void Output(NODE* C, int& C_length)
{
	Huffman(C, C_length);
	Binary_Tree tree;						// tree ��ü ����
	tree.OutputCode(C);						// code ���
	tree.DeleteNode(C);						// �޸� ��ȯ
}

int main(void)
{
	string s;
	EnterString(s);					// ���ڿ� �Է�
	int C_length = 0;				// ���� ���� C ũ�� ����
	NODE* C=Make_C(C_length, s);	// ���� ���� C ����, ���� ���� C ũ�� üũ
	if (!C)							// �Ҵ� ���� ó��
		return -1;
	Output(C, C_length);			// �� ������ �Ҵ�� code ���
	return 0;
}