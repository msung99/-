#include <iotstream>
#include <string>
using namespace std;

class vector {
private:
	int* arr;
	int n;
	int capacity;
public:
	vector(int capacity);
	int size();
	bool empty();
	int at(int idx);
	void set(int idx, int data);
	void insert(int idx, int data);
	void erase(int idx);
	void reverse(int size);
};

vector::vector(int capacity)
{
	this->capacity = capacity;
	n = 0;
	arr = new int[capacity];
}

int vector::size() // O(1)
{
	return n;
}

bool vector::empty() // O(1)
{
	if (n == 0)
		return true;
	else
		return false;
}

int vector::at(int idx)  // O(1)
{
	if (idx < 0 || idx >= n)
		return -1;

	return arr[idx];
}

void vector::set(int idx, int data) // O(1)
{
	if (idx < 0 || idx >= n)
		return;
	arr[idx] = data;
	n++;
}

// insert ���� : O(1) => ������ O(n) ������, ���� ������� ���������Ƿ� Amotized Analysis�� ���� O(1) �̴�.
void vector::insert(int idx, int data) 
{
	if (idx < 0 || idx >= n)
		return;
	if (n == capacity) // �迭�� ������ ���� strategy �� �ϴ°��
		reverse(2 * capacity);  // ���� strategy => O(1)

	for (int i = n - 1; i >= idx; i--)
	{
		arr[i + 1] = arr[i];
	}
	arr[idx] = data;
	n++;
}

void vector::reverse(int size)  // ���� strategy => O(1) (Amotized Analysis�� ���� O(n)ó�� ������ �����δ� O(1)�̴�)
{
	if (size <= capacity)
		return;
	int* newArr = new int[size]; // ��ο� �迭�� ������ ���� �Ҵ�
	for (int i = 0; i < n; i++)
	{
		newArr[i] = arr[i];
	}

	if (arr != NULL) // ���� �迭 ����
		delete[] arr;

	arr = newArr; // ���� �迭�� ���� �����Ͱ� ���� ���ο� �迭�� ����Ű�� ��
	capacity = size;
}

void vector::erase(int idx) // erase ���� : O(n) (=> ȯ���迭�� �����ߴٸ� �Ǿ�,�ǵ� ���Ҹ� erase�ϴ� ���꿡 ���ؼ��� O(1)�� �ɷ������̴�.)
{
	if (idx < 0 || idx >= n)
		return;
	for (int i = idx + 1; i <= n - 1; i++)
	{
		arr[i - 1] = arr[i];
	}
	n--;
}





















