#include <iostream>
#include <string>
using namespace std;

struct node {
	int data;
	node* prev;
	node* next;
};

class nodeList {
private:
	node* header;  // header ��带 �����ϴ� ������ ����
	node* trailer;  // trailer ��带 �����ϴ� ������ ����
	int n;
public:
	nodeList();
	bool empty();
	int size();

	node* begin();  // ����Ʈ�� ù��° ������ �ּҸ� �����ϴ� �Լ�
	node* end();  // ����Ʈ�� ������ ������ ���� ���Ҹ� �����ϴ� �Լ�

	void insert(node* pos, int data); // ����Ʈ���� pos�� ����Ű�� ������ ���ʿ� data�� �����ϴ� �Լ�
	void insertFront(int data);
	void insertBack(int data);
	node* erase(node* pos); // ����Ʈ���� pos�� ����Ű�� ���Ҹ� �����ϴ� �Լ�
	void eraseFront();
	void eraseBack();

	node* nextP(node* pos); // p�� p�� ����Ű�� ����� ���� ���� �̵���Ŵ. (��,p�� trailer�� ����Ű�� ���, �̵���Ű�� �ʴ´�)
	node* prevP(node* pos); // p�� p�� ����Ű�� ����� ���� ���� �̵���Ŵ. (��,p�� header�� ���� ��带 ����Ű�� ���, �̵���Ű�� �ʴ´�)

	void print(); // header�� ���������� trailer�� ���� ������ ���ʴ�� ����� data�� ����� �����Ͽ� ���(����Ʈ�� ����ִٸ� "Empty"�� ���)
	void find(int e); // ����Ʈ ������ e�� ������ ���� ����� ����� index�� ������������ ��� ���.(����� index�� 0���� �����Ѵ�)
				   // ����Ʈ ���� e�� ������ ���� ����� ��尡 ���ٸ� -1�� ����Ѵ�.

	void printp(node* p);
	int getData(node* p);
};

nodeList::nodeList()
{
	header = new node();
	trailer = new node();
	header->next = trailer;
	trailer->prev = header;
	header->prev = NULL;
	trailer->next = NULL;
	n = 0;
}

bool nodeList::empty()
{
	return (n == 0);
}

int nodeList::size()
{
	return n;
}

// ����Ʈ�� �Ǿ� ����(header�� ���� ���)�� �ּҸ� �����ϴ� �Լ�
node* nodeList::begin()
{
	return header->next;
}

// ����Ʈ�� �ǵ� ����(trailer)�� �ּҸ� �����ϴ� �Լ�
node* nodeList::end()
{
	return trailer;
}

// ����Ʈ�� pos�� ����Ű�� ����� ���ʿ� data�� �����ϴ� �Լ�
void nodeList::insert(node* pos, int data)
{
	node* newNode = new node();
	newNode->data = data;

	newNode->prev = pos->prev;
	newNode->next = pos;

	pos->prev->next = newNode;
	pos->prev = newNode;
	n++;
}

// ����Ʈ�� �Ǿտ� data�� �����ϴ� �Լ�
void nodeList::insertFront(int data)
{
	insert(begin(), data);
}

// ����Ʈ�� �ǵڿ� data�� �����ϴ� �Լ�
void nodeList::insertBack(int data)
{
	insert(end(), data);
}

// ����Ʈ���� pos�� ����Ű�� ��带 �����ϴ� �Լ�
node* nodeList::erase(node* pos)
{
	// node* new_p = begin();

	node* new_p = pos->prev;

	if (pos == trailer)
	{
		if (empty())
		{
			cout << "Empty" << '\n';
		}

		return pos;
	}

	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	delete pos;
	n--;
	return new_p;
}

// ����Ʈ�� �Ǿ� ���Ҹ� ����
void nodeList::eraseFront()
{
	erase(begin());
}

void nodeList::eraseBack()
{
	erase(end()->prev);
}

node* nodeList::nextP(node* pos)
{
	if (pos == trailer) // p�� trailer�� ����Ű�� ���, �̵���Ű�� �ʴ´�
		return pos;
	else
	{
		pos = pos->next;
		return pos;
	}
}

node* nodeList::prevP(node* pos)
{
	if (pos->prev == header) // p�� header�� ���� ��带 ����Ű�� ���(��, �Ǿ� ���Ҹ� ����Ű�� ���) �̵���Ű�� �ʴ´�
		return pos;
	else
	{
		pos = pos->prev;
		return pos;
	}
}

void nodeList::print()
{
	if (empty())
	{
		cout << "Empty" << endl;
		return;
	}

	node* tmp = new node;
	tmp = header->next;
	while (tmp != trailer)
	{
		cout << tmp->data << ' ';
		tmp = tmp->next;
	}
	cout << '\n';
}

void nodeList::find(int find_data)
{
	int index = 0;
	int check = false; // e�� ������ ���� ����� ��尡 �ִ��� üũ�ϴ� ����
	node* tmp = new node;
	tmp = header->next;
	while (tmp != trailer)
	{
		if (tmp->data == find_data)
		{
			cout << index << '\n';
			check = true;
		}
		tmp = tmp->next;
		index++;
	}
	if (!check) // e�� ������ ���� ����Ǿ� ���� �ʴ� ���
		cout << -1 << '\n';
}

void nodeList::printp(node* p)
{
	cout << p->data << '\n';
}

int nodeList::getData(node* p)
{
	int sum = 0;
	sum = p->data;
	sum += p->prev->data;
	sum += p->next->data;

	return sum;
}

int main(void)
{
	int testCase;
	cin >> testCase;

	while (testCase--)
	{
		int n;
		cin >> n;
		nodeList list;
		node* p = list.begin();  // ����� ������ p => position ADT �� �����س��� ��

		for (int i = 0; i < n; i++)
		{
			int num;
			cin >> num;
			list.insert(p, num);
		}

		p = list.begin();

		for (int i = 0; i < n; i++)
		{
			cout << list.getData(p) << ' ';
			p = list.nextP(p);
		}
		cout << '\n';
	}
}