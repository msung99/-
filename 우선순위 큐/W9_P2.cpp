#include <iostream>
#include <vector>
using namespace std;

// ����
struct compare {
	// �� ���� e1, e2�� ���ؼ�
	// e1 < e2 �� ��� True��, �ƴ� ��� False�� ����
	bool operator()(const int& e1, const int& e2) const {
		return e1 < e2;
	}
};

class unsortedSeqPQ {
private:
	vector<int> seq; // ���ĵ��� ���� �������� �����ϴ� ����
public:
	int size();
	bool empty();
	void insert(int e);
	int min();
	void removeMin();
};

int unsortedSeqPQ::size()
{
	return seq.size();
}

bool unsortedSeqPQ::empty()
{
	return (seq.size() == 0);
}

// �켱���� ť�� ���� e�� �����ϴ� �Լ�
void unsortedSeqPQ::insert(int e)
{
	seq.push_back(e); // �������� ���� ������ ��ġ�� ���Ҹ� ����
}

// �켱������ ���� ���� ( = ���� ���� ����) ���Ҹ� �����ϴ� �Լ�
int unsortedSeqPQ::min()
{
	if (empty())
		return -1;

	compare C; // ���� ���� ����
	int minVal = seq[0]; 

	// �������� ���������� Ž���ϸ�
	for (int i = 0; i < seq.size(); i++)
	{
		// ���� �켱������ ���� ���Ҹ� minVal�� ����
		if (C(seq[i], minVal))
		{
			minVal = seq[i];
		}
	}
}

// �켱������ ���� ����(= ���� ���� ����) ���Ҹ� �����ϴ� �Լ�
void unsortedSeqPQ::removeMin()
{
	if (empty())
		return;

	compare C; // ���� ���� ����
	int minIdx = 0;

	// �������� ���������� Ž���ϸ�
	// ���� �켱������ ���� ������ �ε����� minIdx �� ����
	for (int i = 0; i < seq.size(); i++)
	{
		if (C(seq[i], seq[minIdx]))
			minIdx = i;
	}
	seq.erase(seq.begin() + minIdx);  // �������� ���� �켱������ ���� ���� minIdx �� ����
}

//////////////////////////////////////////////////////////////////////

class sortedSeqPQ {
private:
	vector<int> seq; // ������������ ���ĵ� �������� �����ϴ� ����
public:
	int size();
	bool empty();
	void insert(int e);
	int min();
	int max();
	void removeMin();
	void removeMax();
	void print();
};


int sortedSeqPQ::size()
{
	return seq.size();
}

bool sortedSeqPQ::empty()
{
	return (seq.size() == 0);
}

// �켱���� ť�� ���� e�� �����ϴ� �Լ�
void sortedSeqPQ::insert(int e)
{
	compare C;
	int idx = 0;

	// �������� ���������� Ž���ϸ�
	// ������ ���Һ��� �켱������ ���� ���Ұ� ó�� �����ϴ� ��ġ Ž��
	for (idx = 0; idx < seq.size(); idx++) {
		if (C(seq[idx], e))
			break;
	}

	seq.insert(seq.begin() + idx, e); // ã�� ��ġ�� �տ� ���ο� ���� e ����
}

// �켱������ ���� ���� ����(= �ּڰ�)�� �����ϴ� �Լ�
int sortedSeqPQ::min()
{
	if (empty())
		return -1;

	return seq.back(); // �������� ���� ������ ���Ҹ� ����
}

/*
void sortedSeqPQ::min()
{
	if (empty())
	{
		cout << "empty" << endl;
		return;
	}
	cout << seq.back() << endl;
}
*/

// �켱������ ���� ���� ����( = �ִ�) �� ����
int sortedSeqPQ::max()
{
	if (empty())
		return -1;

	return seq.front(); 
}

/*
void sortedSeqPQ::max()
{
	if (empty())
	{
		cout << "empty" << endl;
		return;
	}
	cout << seq.front() << endl;
}
*/

// �켱������ ���� ���� ���Ҹ� �����ϴ� �Լ�
void sortedSeqPQ::removeMin()
{
	if (empty())
	{
		cout << "empty" << endl;
		return;
	}
	seq.pop_back(); // �������� ���� ������ ���Ҹ� ����
}

// �ִ� ���� 
void sortedSeqPQ::removeMax()
{
	if (empty())
	{
		cout << "empty" << endl;
		return;
	}
	seq.erase(seq.begin());
}

void sortedSeqPQ::print()
{
	if (empty())
	{
		cout << "empty" << endl;
		return;
	}

	vector<int> list;

	// �������� ���
	for (int i = 0; i < seq.size(); i++)
	{
		if (seq[i] % 2 == 1)
			cout << seq[i] << ' ';
		else
			list.push_back(seq[i]);
	}
	for (int i = 0; i < list.size(); i++)
	{
		cout << list[i] << ' ';
	}

	cout << endl;
}

int main(void)
{
	int testCase;
	cin >> testCase;
	while (testCase--)
	{
		sortedSeqPQ s;
		int count;
		cin >> count;
		for (int i = 0; i < count; i++)
		{
			int data;
			cin >> data;
			s.insert(data);
		}
		s.print();
	}
}
	/*
	while (testCase--)
	{
		string a;
		cin >> a;
		if (a == "size")
		{
			cout << s.size() << endl;
		} 

		else if (a == "empty")
		{
			if (s.empty())
				cout << "empty" << endl;
			else
				cout << "Not empty" << endl;
		}

		else if (a == "insert")
		{
			int b;
			cin >> b;
			s.insert(b);
		}

		else if (a == "min")
		{
			cout << s.min() << endl;
		}

		else if (a == "removeMin")
		{
			s.removeMin();
		}
		else if (a == "removeMax")
		{
			s.removeMax();
		}

		else if (a == "print")
		{
			s.print();
		}
		else if (a == "max")
		{
			cout << s.max() << endl;
		}
	}
	*/