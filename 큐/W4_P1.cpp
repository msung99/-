#include <iostream>
#include <string>
using namespace std;

class arrayQueue {
private:
	int* arr;  // ť�� ���Ҹ� �����ϴ� �迭
	int capacity;  // ť�� �ִ� ũ�⸦ �����ϴ� ����
	int frontIndex; // �迭���� ť�� front ��ġ�� �����ϴ� ����
	int rearIndex;  // �迭���� ť�� "rear ��ġ + 1" �� �����ϴ� ����
	int n; // ť�� ���� ũ�⸦ �����ϴ� ����

public:
	arrayQueue(int capacity);
	bool isFull();
	bool empty();
	int size();
	void front();
	void rear();
	void enqueue(int data);
	void dequeue();
};



arrayQueue::arrayQueue(int capacity) {
	this->capacity = capacity;
	arr = new int[capacity];
	frontIndex = rearIndex = 0;
	n = 0;
}



bool arrayQueue::isFull() {
	return n > capacity; // ť�� �ִ�ũ�� capacity ��ŭ ť�� ����� �����ߴٸ� ���� ������
}



bool arrayQueue::empty() {
	return n == 0; // ť�� ���� ������ n�� ���� 0�̸� ����ִ� ����
}



int arrayQueue::size() {
	return n; // ť�� ���� ������ �� ����
}

// �� ��(frontIndex) �� ������ �� ���

void arrayQueue::front() {  // ť�� front�� ����� ���Ҹ� �����ϴ� �Լ�
	if (empty())
		cout << "Empty" << endl;
	else {
		cout << arr[frontIndex % capacity] << endl;
	}
}



// �� ��(rearIndex) �� ������ �� ���
void arrayQueue::rear() {
	if (empty())
		cout << "Empty" << endl;
	else {
		cout << arr[(rearIndex - 1) % (capacity+1)] << endl; // rearIndex �� �迭�� �� ��ġ(rear) ĭ�� ���� ĭ�� ����Ų�ٴ� �� �����ϱ�!
	}
}


void arrayQueue::enqueue(int data) { // ť�� rear �� ���Ҹ� �����ϴ� ���
	if (isFull()) {  // capacity �̻����� ť�� �����Ͱ� �߰��Ǵ� ���� ������
		cout << "FULL" << endl;   //  => ����� �����ؼ� enqueue ��ɾ �Է¹��� ��� �׳� �����ϰ� �ϴ��� ��� ������
	}

	// rearIndex �� �迭�� �� ��ġ(rear) ĭ�� ���� ĭ�� ����Ų�ٴ� ���� �����ϱ�!
	else {
		arr[rearIndex] = data;  // �迭�� rearIndex ��ġ�� ���Ҹ� �����ϰ�, 1����
		rearIndex = rearIndex + 1;
		n++; // ť ���� ������ 1����
	}
}



void arrayQueue::dequeue() {
	if (empty())
	{
		cout << "Empty" << endl;
	}
	else
	{
		cout << arr[frontIndex] << endl; // ������Ű���� �� ���� ���� ���
		frontIndex = (frontIndex + 1) % capacity; // ���� => front �ε����� ��ĭ �̵���Ŵ���ν�, ��ġ ������ ���� ȿ���� ����
		n--; // ť�� ���� ������ 1����
	}
}

int main() {
	int test_case;
	cin >> test_case; // N : ť�� ũ��, test_case : �׽�Ʈ���̽� Ƚ��
	arrayQueue _arr(10000);

	for (int i = 0; i < test_case; i++) {
		string a;
		cin >> a;
		if (a == "isFull") {
			if (_arr.isFull())
				cout << "FULL" << '\n';
			else
				cout << "NOT FULL" << '\n';
		}

		else if (a == "isEmpty") {
			if (_arr.empty())
				cout << "True" << endl;
			else
				cout << "False" << endl;
		}

		else if (a == "dequeue") {
			_arr.dequeue();
		}

		else if (a == "enqueue") {
			int v;
			cin >> v;
			_arr.enqueue(v);
		}

		else if (a == "front") {
			_arr.front();
		}

		else if (a == "rear") {
			_arr.rear();
		}

		else if (a == "size") {
			cout << _arr.size() << '\n';
		}
	}
}

