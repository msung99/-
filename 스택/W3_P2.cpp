#include <iostream>
#include <string>
using namespace std;

class arrayStack {
public:
	arrayStack(int capacity);
	bool empty();
	int size();
	char top();
	void push(char data);
	void pop();

private:
	int* arr;  // ������ ���Ҹ� �����ϴ� �迭
	int capacity; // ������ �ִ� ũ�⸦ �����ϴ� ����
	int topIndex; // �迭���� ������ top�� ����Ǿ� �ִ� �ε����� �����ϴ� ����
};

arrayStack::arrayStack(int capacity) {
	this->capacity = capacity;
	arr = new int[capacity];
	topIndex = -1;
}

bool arrayStack::empty() {
	if (topIndex == -1) {
		return true;
	}
	else {
		return false;
	}
}

char arrayStack::top() {
	return char(arr[topIndex]);
}

void arrayStack::push(char data) {
	if (size() == capacity)
	{
		cout << "FULL";
		return;
	}

	topIndex++;
	arr[topIndex] = data;
}

int arrayStack::size() {
	return topIndex + 1;
}

void arrayStack::pop() {
	if (empty()) {
		return;
	}

	cout << top();
	topIndex--;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;

	arrayStack s(1000);

	// 1-2+3 
	// ���� :  12-3+
	// ���� :  1-2343


	// 12-3+
	// ����:+
	while (n--)
	{
		string str;
		cin >> str;
		for (int i = 0; i < str.length(); i++) 
		{
			if (str[i] == '+' || str[i] == '-')
			{
				while (!s.empty())
				{
					s.pop(); 
				}
				s.push(str[i]);
			}
			else if (str[i] == '*' || str[i] == '/')
			{
				while (s.top() == '*' || s.top() == '/')
				{
					s.pop();
				}
				s.push(str[i]);
			}
			else
			{
				cout << str[i];
			}
		}
		
		while (!s.empty())
			s.pop();
		cout << '\n';
	}
}