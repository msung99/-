// �̱۸� ��ũ�� ����Ʈ ����� ���� ����
// (���� ��ũ�� ����Ʈ ������ ¥�� �ȹ���� ���� ���غ��� �ɵ�?)

#include <iostream>
#include <string>
using namespace std;

struct node {
	int data;
	node* next;
	node* prev;
};

class listStack {
private:
	node* topNode;
	int listSize;
public:
	listStack();
	bool empty();
	int size();
	int top();
	void push(int data);
	void pop();
};

listStack::listStack()
{
	topNode = NULL;
	listSize = 0;
}

bool listStack::empty()
{
	if (listSize == 0)
		return true;
	else
		return false;
}

int listStack::size()
{
	return listSize;
}

int listStack::top()  // top ���� : O(1)
{
	if (empty())
		return -1;
	else
		return topNode->data;
}

void listStack::push(int data) // push ���� : head ���(topNode ���) ���� ���� ���� => O(1)
{
	node* newNode = new node;
	newNode->data = data;

	newNode->next = topNode;
	topNode = newNode;
	listSize++;
}

void listStack::pop() // pop ���� : ���������� head ��忡�� ���� ���� => O(1)
{
	if (empty())
		return;

	node* tmp = topNode;
	topNode = topNode->next;
	delete tmp;
	listSize--;
}