#include <iostream>
#include <string>
#include <vector>
using namespace std;

// �迭(����) ��� �ּ��� 
class heap {
private:
	vector<int> arr; // ���� ���Ҹ� �����ϴ� ������(����)
	void swap(int idx1, int idx2);
	void upHeap(int idx);  // ���� �ε��� idx�� ����� ���ҿ��� upHeap �� ����
	void downHeap(int idx);  // ���� �ε��� idx�� ����� ���ҿ��� downHeap �� ����
public:
	heap();
	int size();
	bool empty();
	void insert(int data);
	int min();
	void removeMin();
	void print();
};

heap::heap() {
	arr.push_back(0); // 0�� �ε����� �ϴ� 0���� �ʱ�ȭ.
}

int heap::size() {
	return arr.size() - 1; // 0�� �ε����� ����� �����ʹ� �����ؾ� �ϹǷ�, arr.size() ���� 1�� �� ���� ����
}

bool heap::empty() {
	return (arr.size() == 1); // // 0�� �ε����� ����� �����ʹ� �����ؾ� �ϹǷ� ����� 1�϶� �� ���� 
}

// ����ִ� �ε��� 0�� Ȱ���� �� �ε��� idx1, idx2�� ��ġ�� ���Ҹ� ��ü
void heap::swap(int idx1, int idx2) {
	arr[0] = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = arr[0];
}

void heap::insert(int data) {
	arr.push_back(data); // ����1) ���� ���� : O(1)
	upHeap(size()); // ����2) ���� ���� : O(log n)
}

void heap::upHeap(int idx) {
	if (idx == 1)  // ��Ʈ ��忡 ������ ��� upHeap ���� 
		return;

	// �ڽ��� ���� �θ𺸴� �ڽ��� key ���� �� Ŭ������ ��� upHeap �� ����
	// upHeap �� ��ġ�� ����, ������ ��ġ�� ã�ư��� ����.
	int parent = idx / 2;
	if (arr[parent] > arr[idx]) {
		swap(parent, idx);
		upHeap(parent);
	}
}

// ��Ʈ ��� ������( = �ε��� 1�� ����� ������ ) �� ����
int heap::min()
{
	if (empty())
		return -1;

	return arr[1]; // ��Ʈ ��� ������ ����
}

// �ּڰ� ���� 
void heap::removeMin()
{
	if (empty())
	{
		cout << -1 << endl;
		return;
	}
	// �ܰ�1) ������ ���� : O(1)
	swap(1, size()); // ����1) �� ������ �����͸� ��Ʈ ��忡 ������
	cout << arr.back() << endl;
	arr.pop_back(); // ����2) �� ������ ������ ����


	// �ܰ�2) ���� ���� : 2 x O(log n)
	downHeap(1); // �ٿ����� �����ؼ�, �ֽ�ȭ�� ��Ʈ ��� �����Ͱ� ������ ��ġ�� ã�ư����� �ϱ�
}

void heap::downHeap(int idx) {
	int left = 2 * idx;
	int right = 2 * idx + 1;

	int child; // ����, ������ �ڽ� �� ���� �ڽŰ� swap �� ������ �ڽ��� �ε��� 

	// �� �ڽ� ��� �������� ���� ��� downHeap ����
	if (left > size()) {
		return;
	}

	// ���� �ڽĸ� �����ϴ� ���
	else if (left == size()) {
		child = left;
	}

	// ����, ������ �ڽ� ��� �����ϴ� ���
	// �� �ڽ��� �� ���� �ڽ��� ã�Ƴ���.
	else {
		if (arr[left] <= arr[right]) // child ����
			child = left;
		else
			child = right;
	}

	// heap-order �� �������� �ʴ� ���. ��, downHeap�� �����ؾ� �ϴ� ��� 
	// ã�Ƴ� �� ���� �ڽİ� ���� �ڽ��� swap �� ������ �Ǵ��ϰ� swap �� ����

	if (arr[child] < arr[idx]) {  // �ڽ��� �ڽ� key �� ���� �� �۾Ƽ� downHeap �� �����ؾ� �ϴ� ���
		swap(child, idx); // �ڽ��� ���� swap
		downHeap(child); // �� �ٿ��� ����
	}
}

void heap::print()
{
	if (empty())
	{
		cout << -1 << endl;
		return;
	}

	// �ε��� 0�� �� �ε��� �̹Ƿ�, �ε��� 1���� ���
	for (int i = 1; i < arr.size(); i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
}

int main(void)
{
	heap h;
	int t;
	cin >> t;
	while (t--)
	{
		string a;
		cin >> a;
		if (a == "insert")
		{
			int data;
			cin >> data;
			h.insert(data);
		}
		else if (a == "size")
		{
			cout << h.size() << endl;
		}
		else if (a == "isEmpty")
		{
			if (h.empty())
				cout << 1 << endl;
			else
				cout << 0 << endl;
		}
		else if (a == "pop")
		{
			h.removeMin();
		}
		else if (a == "top")
		{
			cout << h.min() << endl;
		}
		else if (a == "print")
		{
			h.print();
		}
	}
}