#include <iostream>
#include <string>
using namespace std;

struct node {
	int data; // ������ �ʵ�
	node* next;  // ��ũ �ʵ�
};

class singlyLinkedList {
private:
	node* head;
	node* tail;
	int listSize;
public:
	singlyLinkedList();
	bool empty();
	void append(int data);
	void insertion(int idx, int data); 
	void delection(int idx);
	void print();
};

singlyLinkedList::singlyLinkedList()
{
	head = NULL;
	tail = NULL;
	listSize = 0;
}


bool singlyLinkedList::empty()
{
	if (listSize == 0)
		return true;

	else
		return false;
}
void singlyLinkedList::append(int data) //tail��(tail�� �ڿ���) ������ �߰� => O(1)
{
	node* newNode = new node;
	newNode->data = data;

	if (empty())
	{
		head = newNode;
		tail = newNode;
		listSize++;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
		listSize++;
	}
}


void singlyLinkedList::insertion(int idx, int data)
{
	node* newNode = new node;
	newNode->data = data;

	if (idx < 0 || idx > listSize)
		return;

	if (idx == 0) // head �� insert => O(1)
	{
		newNode->next = head;
		head = newNode;
	}

	else if (idx == listSize)
	{
		append(data); // tail �� insert => O(1)
	}
	else
	{
		node* curNode = new node;
		for (int i = 1; i < idx; i++)    // �߰��� insert => O(n)
		{
			curNode->next = curNode;
		}
		newNode->next = curNode->next;
		curNode->next = newNode;
		listSize++;
	}
}

void singlyLinkedList::delection(int idx)
{
	if (empty() || idx < 0 || idx > listSize)
		return;

	node* curNode = head;
	if (idx == 0) // head �� ���� => O(1)
	{
		if (listSize == 1)
		{
			head = NULL;
			tail = NULL;
			listSize--;
		}
		else
		{
			head = head->next;
			delete curNode;
			listSize--;
		}
	}
	else
	{
		node* preNode = head;
		for (int i = 0; i < idx; i++)  // �߰��� �ִ°�, �Ǵ� tail�� ���� => O(n)
		{
			preNode = curNode;
			curNode = curNode->next;
		}
		preNode->next = curNode->next;
		if (curNode == tail)
			tail = preNode;
		delete curNode;
		listSize--;
	}
}

void singlyLinkedList::print()
{
	if (empty())
	{
		cout << "Empty";
	}
	node* curNode = head;
	while (curNode != NULL)
	{
		cout << curNode->data << ' ';
		curNode = curNode->next;
	}
	cout << endl;
}