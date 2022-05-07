#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ���� - �� ������ �켱������ ���ϴ� ADT
// compare(p ,q) : p�� q���� �켱������ �������� �Ǵ�.
// ex) compare(10,3) : 10 < 3 ? => false (10�� 3���� �켱������ �����Ƿ� false�� ����)
struct compare {
	bool operator()(const int& p, const int& q) const {
		return p > q;  // ���� maxPQ �� �ƴ� minPQ �� ���ڸ� �����Ѵٸ�, 
	}                  // �켱������ �ִ� �ƴ� �ּڰ��̹Ƿ� "return p < q" �� �����ؾ� �Ѵ�. (���⼭�� minPQ�� ����)
};


class sortedSeqPQ {
private:
	vector<int> seq; // ������������ ���ĵ� �������� �����ϴ� ����
public:
	int size();
	bool empty();
	void insert(int e);
	int min();
	void removeMin();
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
int sortedSeqPQ::min() {
	if (empty())
		return -1;

	return seq.back(); // ������ �� �ڿ� ������ִ� �ּڰ��� ����
}

// unsortedSeqPQ �� �޸� �̹� �������� ���ĵ��ִ� �����̹Ƿ�, �׳� �ٷ� �ּڰ��� �����ϸ� ���̴�.
void sortedSeqPQ::removeMin() {
	if (empty())
		return;

	seq.pop_back(); // ������ �� �ڿ� ������ִ� �ּڰ��� ����
}

void sortedSeqPQ::print() {
	for (int i = 0; i < seq.size(); i++) {
		cout << seq[i] << ' ';
	}
	cout << endl;
}

int main(void)
{
	int t;
	cin >> t;

	while (t--)
	{
		// ���� ���� (Insertion sort) ���� => sorted �������� ����
		sortedSeqPQ q;
		int n;
		cin >> n;
		while (n--)  // PQ �������� ���Ҹ� ���������� ��� ���ĵ� ���� ����
		{
			int data;
			cin >> data;
			q.insert(data);
		}
		q.print();
	}
}