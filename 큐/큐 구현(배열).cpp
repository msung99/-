#include <iostream>
using namespace std;

# define MAX 99999


// ���� ť ����
class Queue {
private:
	int data[MAX]; // ť �����͸� �����ϴ� �迭
	int index_front; // ���� �� �ε��� ( = head ������ )
	int index_back; // �� �� �ε���   ( = tail ������ )
public:
	Queue();
	bool empty();
	void push(int x);
	void pop();
	int front();
	int back();
	int size();
};

Queue::Queue() {
	index_front = 0;
	index_back = 0;
}

bool Queue::empty()
{
	return index_front == index_back;
}

void Queue::push(int x)
{// �迭�� ������ �ٽ� 0�� �ε������� �����ؼ� push �� �ϴ� ���� ť�� Ư���� ����
	index_back = (index_back + 1) % MAX;  // �ε��� MAX-1 ���� ����á�ٸ�, �ٽ� 0�� �ε��� ���� �����͸� ���� 
	data[index_back] = x;
}

void Queue::pop()
{
	index_front = (index_front + 1) % MAX; // head �����͸� ��ĭ �ڷ� �̵����Ѽ�, ��ġ ������ ���ϰ� �� 
	// (�����δ� �޸𸮿��� �������� ����)
}

int Queue::front()
{
	return data[(index_front + 1) % MAX];
}

int Queue::back()
{
	return data[index_back];
}

int Queue::size()
{
	return (index_back - index_front + MAX) % MAX;
}

int main(void)
{
	Queue q;
	// 1~10 ���ڸ� ť�� push
	for (int i = 1; i <= 10; i++) {
		q.push(i);
	}

	// 1~4 ���ڸ� pop
	for (int i = 1; i <= 4; i++) {
		q.pop();
	}

	cout << "size:" << q.size() << '\n'; // 6 

	while (!q.empty())
	{
		cout << "pop:" << q.front() << '\n'; // ������ �������� �� ( = �� �� �������� ��) �� �����ϰ�
		q.pop(); // ������Ŵ
	}
}





















