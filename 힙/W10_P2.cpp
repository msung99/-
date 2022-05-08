#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// �迭(����) ��� �ִ��� 
class heap {
private:
	vector<int> arr;
	void swap(int idx1, int idx2);
	void upHeap(int idx);
	void downHeap(int idx);
public:
	heap();
	int size();
	bool empty();
	void insert(int data);
	int max();
	void removeMax();
	void print(int p, int count);
	void make_and_insert();
};

heap::heap() {
	arr.push_back(0);
}

int heap::size() {
	return arr.size() - 1;
}

bool heap::empty() {
	return (arr.size() == 1);
}


void heap::swap(int idx1, int idx2) {
	arr[0] = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = arr[0];
}

void heap::insert(int data) {
	arr.push_back(data);
	upHeap(size());
}

void heap::upHeap(int idx) {
	if (idx == 1)
		return;

	// minHeap �� �ٸ� ���� :  �ڽ��� ���� �θ𺸴� �ڽ��� key ���� �� "Ŭ������" ��� upHeap �� ����
	int parent = idx / 2;
	if (arr[parent] < arr[idx]) {
		swap(parent, idx);
		upHeap(parent);
	}
}

int heap::max()
{
	if (empty())
		return -1;

	return arr[1];
}




void heap::removeMax()
{
	if (empty())
	{
		cout << -1 << endl;
		return;
	}


	swap(1, size());
	arr.pop_back();

	downHeap(1);
}

void heap::downHeap(int idx) {
	int left = 2 * idx;
	int right = 2 * idx + 1;

	int child;


	if (left > size()) {
		return;
	}

	else if (left == size()) {
		child = left;
	}

	// minHeap �� �ٸ� ���� : �� �ڽ��� �� "ū �ڽ�"�� ã�Ƴ���.
	else {
		if (arr[left] <= arr[right])
			child = right;
		else
			child = left;
	}

	if (arr[child] > arr[idx]) {  // minHeap�� �ٸ� ���� : �ڽ��� �ڽ� key �� ���� �� "�۾Ƽ�" downHeap �� �����ؾ� �ϴ� ���
		swap(child, idx);
		downHeap(child);
	}
}

void heap::print(int p, int count)
{
	if (empty())
	{
		cout << -1 << endl;
		return;
	}

	// ���� �ռ� �����߿� �� ���� ������ 2�� ���ϰ� �Ǿ������� �ұ��ϰ�, 
	// ���� ���� �����߿� p �̻��� �µ��� ���� ������ �ִٸ� ��� ������ �µ��� p ���Ϸ� ����µ� ������ ���̴�/
	if (size() <= 2 && max() > p)
	{
		cout << "False" << endl;
		return;
	}

	cout << count << endl;
	for (int i = 1; i < arr.size(); i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
}

void heap::make_and_insert()
{
	vector<int> new_list;

	// ���� 3���� �µ��� ���� ���� ����
	new_list.push_back(max());
	removeMax();
	new_list.push_back(max());
	removeMax();
	new_list.push_back(max());
	removeMax();

	sort(new_list.begin(), new_list.end());
	int result = (new_list[0] + new_list[2]) / 2; // ���ο� ���� ����

	insert(result); // ���ο� ���� ���� �߰� 
}

int main(void)
{
	int t;
	cin >> t;
	while (t--)
	{
		heap h;
		int n, p;
		cin >> n >> p;

		// ���� �Ҵ�
		for (int i = 0; i < n; i++)
		{
			int data;
			cin >> data;
			h.insert(data);
		}

		// �� ������ 3�� �̻��̸�, ���� ������ �µ��� p���� ū���� �����Ҷ� ���� �ռ� ���� �ݺ�
		// (��, �� ������ 2�� �����̸�, ���� ��� ������ �µ��� p���� ������ �ռ� ���� ����)
		int count = 0;	
		while (h.size() >= 3 && h.max() > p)
		{
			h.make_and_insert();
			count++;
		}
		h.print(p, count);
	}
}