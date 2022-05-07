// maxPQ �� ����, ¦���� �켱������ ���� 

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ���� - �� ������ �켱������ ���ϴ� ADT
struct compare {
	bool operator()(const int& p, const int& q) const {
		return p > q;
	}                  
};

class sortedSeqPQ {
private:
	vector<int> seq; 
public:
	int size();
	bool empty();
	void insert(int e);
	int max();
	void removeMax();
	void print();
};

int sortedSeqPQ::size() {
	return seq.size();
}

bool sortedSeqPQ::empty() {
	return (seq.size() == 0);
}

// unsortedSeqPq �� �޸�, ������ ���Ϳ� ���Ҹ� ���Խ� �׳� �������� �ʰ� ���Ե� ������ ��ġ�� ã�ư��� ���Եȴ�.
void sortedSeqPQ::insert(int data) {
	compare C;
	int idx = 0;

	// data ���Ұ� ���Ե� ������ ��ġ�� Ž��
	for (idx = 0; idx < seq.size(); idx++) {
		if (C(seq[idx], data))  // ������ ���Һ��� �켱������ ����(= key���� �� ����) ���Ұ� ó�� �����ϴ� ��ġ�� Ž�� 
			break;
	}
	seq.insert(seq.begin() + idx, data);  // ã�� ��ġ�� ���ο� ������ �� ����
}

// unsortedSeqPQ �� �޸� �̹� �������� ���ĵ��ִ� �����̹Ƿ�, �׳� �ٷ� �ּڰ� �������ָ� �ȴ�.
int sortedSeqPQ::max() {
	if (empty())
		return -1;

	return seq.front(); 
}

// unsortedSeqPQ �� �޸� �̹� �������� ���ĵ��ִ� �����̹Ƿ�, �׳� �ٷ� �ּڰ��� �����ϸ� ���̴�.
void sortedSeqPQ::removeMax() {
	if (empty())
		return;

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
		if (seq[i] % 2 == 0)
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
	int t;
	cin >> t;
	while (t--)
	{
		sortedSeqPQ q;
		int n;
		cin >> n;
		while (n--)
		{
			int data;
			cin >> data;
			q.insert(data);
		}
		q.print();
	}
}