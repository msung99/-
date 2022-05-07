#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ���� - �� ������ �켱������ ���ϴ� ADT
// compare(p ,q) : p�� q���� �켱������ �������� �Ǵ�.
// maxPQ �� ���������Ƿ�, �켱������ �ִ��̴�.
struct compare {
	bool operator()(const int& p, const int& q) const {
		return p > q; // maxPQ �̹Ƿ� p > q �ε�, ���� minPQ �� �����ߴٸ� "return p < q" �� �ȴ�.
	}
};

// maxPQ �� ���� ������ ������ ���ͷ� ����
class unsortedSeqPQ {
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

int unsortedSeqPQ::size() {
	return seq.size();
}

bool unsortedSeqPQ::empty() {
	return (seq.size() == 0);
}

// �켱���� ť�� ���� e�� ����
// ���İ����� ���ϰ�, �׳� ������ �� �ڿ� ���� ����
void unsortedSeqPQ::insert(int data) {
	seq.push_back(data);
}

// ����(���ı���) C�� ���� �ּڰ��� Ž��
// ���ĵ��� ���� ���������� �Ǿտ������� �� ������ �ϴ� Ž���ϸ鼭 �ִ� ã�Ƴ���
int unsortedSeqPQ::max() {
	if (empty())
		return -1;

	compare C;
	int max_value = seq[0];
	for (int i = 0; i < seq.size(); i++) {
		if (C(seq[i], max_value))
			max_value = seq[i];
	}
	return max_value;
}

// ���ĵ��� ���� ���������� �Ǿտ������� �� ������ �ϴ� Ž���ϸ鼭
// �ִ� ã�Ƴ��� ����
void unsortedSeqPQ::removeMax() {
	if (empty())
		return;

	compare C;
	int maxIdx = 0;
	for (int i = 0; i < seq.size(); i++) {
		if (C(seq[i], seq[maxIdx]))
			maxIdx = i;
	}
	seq.erase(seq.begin() + maxIdx);
}


int main(void)
{
	int t;
	cin >> t;
	while (t--)
	{
		// ��������(selection sort)�� ���� PQ�� ������ ������ ���ͷ� ����
		unsortedSeqPQ q;
		int n;
		cin >> n;

		// 1) ������ ������ �������� �ʰ� �״�� PQ �迭�� ī����,
		while (n--) 
		{
			int data;
			cin >> data;
			q.insert(data);
		}

		// 2) �ִ��� ������ �� �տ������� ���ϸ鼭 ã�Ƴ���, ã�Ƴ� �ִ��� PQ ���� ��°� ���ÿ� ����
		int q_size = q.size(); 
		for (int i = 0; i < q_size; i++) 
		{
			cout << q.max() << ' '; // �ִ� ����ϰ�
			q.removeMax(); // �ִ� ����
		}
		cout << endl;
	}
}