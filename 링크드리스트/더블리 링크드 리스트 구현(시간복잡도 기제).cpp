#include <iostream>
#include <string>
using namespace std;

struct node {
	int data; // ������ �ʵ�
	node* next;  // ��ũ �ʵ�
	node* prev;
};

class doublyLinkedList {
private:
	node* head;
	node* tail;
	int listSize;
public:
	doublyLinkedList();
	bool empty();
	void append(int data);
	void insertion(int idx, int data);
	void delection(int idx);
	void print();
};

doublyLinkedList::doublyLinkedList()
{
	head = NULL;
	tail = NULL;
	listSize = 0;
}


bool doublyLinkedList::empty()
{
	if (listSize == 0)
		return true;

	else
		return false;
}

void doublyLinkedList::append(int data) //tail��(tail�� �ڿ���) ������ �߰� => O(1)
{
	node* newNode = new node;
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;

	if (empty())
	{
		head = newNode;
		tail = newNode;
		listSize++;
	}
	else
	{
		tail->next = newNode;
		newNode->prev = tail;
		tail = tail->next;
		listSize++;
	}
}


void doublyLinkedList::insertion(int idx, int data)
{

	if (idx < 0 || idx > listSize){
		return;
	}

	else if (idx == listSize)
	{
		append(data); // tail �� insert => O(1)
	}

	if (idx == 0) // head �� insert => O(1)
	{
		node* newNode = new node;
		newNode->data = data;
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		listSize++;
	}

	else
	{
		node* newNode = new node;
		newNode->data = data;
		node* curNode = head;
		for (int i = 1; i < idx; i++)    // �߰��� insert => O(n)
		{
			curNode = curNode->next; // ������ ��ġ�� ���� ���
		}
		curNode->next->prev = newNode;
		newNode->next = curNode->next;

		newNode->prev = curNode;
		curNode->next = newNode;

		listSize++;
	}
}

void doublyLinkedList::delection(int idx)
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

	else if (idx == listSize) // tail ��� ���� => O(1)   ( �̱۸� ����Ʈ�� ��� tail ������ O(n) )
	{
		tail->prev->next = NULL;
		tail = tail->prev;
		delete tail;
		listSize--;
	}

	else
	{
		node* preNode = head;
		for (int i = 0; i < idx; i++)  // �߰��� �ִ� ��� ���� => O(n)
		{
			preNode = curNode;
			curNode = curNode->next;
		}
		preNode->next = curNode->next;
		curNode->next->prev = preNode;
		delete curNode;
		listSize--;
	}
}

void doublyLinkedList::print()
{
	if (empty())
	{
		cout << "Empty\n";
		return;
	}
	node* curNode = head;
	while (curNode != NULL)
	{
		cout << curNode->data << ' ';
		curNode = curNode->next;
	}
	cout << '\n';
}

bool empty();
void append(int data);
void insertion(int idx, int data);
void delection(int idx);
void print();

int main(void)
{
	doublyLinkedList d1;

	int testCase;
	cin >> testCase;

	while (testCase--)
	{
		string command;
		cin >> command;

		if (command == "empty")
		{
			if (d1.empty())
				cout << "EMPTY" << endl;
			else
				cout << "NOT EMPTY" << endl;
		}

		else if (command == "append")
		{
			int dat;
			cin >> dat;
			d1.append(dat);
		}
		else if (command == "insertion")
		{
			int a, b;
			cin >> a >> b;
			d1.insertion(a, b);
		}
		else if (command == "delection")
		{
			int a;
			cin >> a;
			d1.delection(a);
		}
		else if (command == "print")
		{
			d1.print();
		}
	}
}