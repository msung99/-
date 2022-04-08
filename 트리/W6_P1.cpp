#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct node {
	int data;
	node* parent; // �θ� ��带 ����Ű�� ������ ����
	vector<node*> childList;  // �ڽ� ������ ����Ű�� ������ ����

	node(int data, node* parent) {
		this->data = data;
		this->parent = parent;
	}
};

class Tree {
private:
	node* root;  // Ʈ���� root�� �����ϴ� ������ ����
	vector<node*> nodeList; // Ʈ���� ��� ����� �����͸� �����ϴ� ����
public:
	int find(int data, vector<node*>& list); // ��������� ���Ϳ��� Ư�� ��带 ã�� �Լ�
	Tree(int data);
	void insertNode(int parData, int data); // data�� �����ϴ� ��带 �����Ͽ� parData�� �ڽ����� �����ϴ� �Լ�
	void deleteNode(int data);  // data�� �����ϴ� ��带 �����ϴ� �Լ�
	void printParent(int data); // data�� �����ϴ� ����� �θ� ����ϴ� �Լ�
	void printChild(int data); // data�� �����ϴ� ����� �ڽĵ��� ����ϴ� �Լ�
	void maxChild(int data);
};

Tree::Tree(int data)
{
	node* newNode = new node(data, NULL);
	root = newNode;
	nodeList.push_back(root);
}


int Tree::find(int data, vector<node*>& list) {  // ��� ������ ���Ϳ��� Ư�� ����� �ε����� ã���Լ�
	for (int i = 0; i < list.size(); i++) {
		if (list[i]->data == data) // ��带 ã���� ���, �ε����� ����
			return i;
	}
	return -1;
}

// data�� �����ϴ� ��带 �����Ͽ� parData�� �ڽ����� �����ϴ� �Լ�
void Tree::insertNode(int parData, int data) {
	if (find(data, nodeList) != -1)  // ���� ������ ���(data ���)�� �̹� �����ϴ� ���
	{
		cout << -1 << endl;
		return;
	}

	int idx = find(parData, nodeList); // nodeList���� �θ� ����� �ε����� ã�� 
	if (idx == -1)  // �θ� ���(parData ���)�� �������� �ʴ� ���
	{
		cout << -1 << endl;
		return;
	}

	node* parNode = nodeList[idx];
	node* newNode = new node(data, parNode); // ���� ������ ��带 �����ϰ�, �θ� parNode�� ����
	parNode->childList.push_back(newNode);  // parNode�� �ڽ� ���� ����Ʈ�� newNode�� ����
	nodeList.push_back(newNode); // ��ü ��� ���� ����Ʈ�� ���ο� ��� newNode �� ����
	return;
}

// data�� ������ ��带 ����
void Tree::deleteNode(int data) {
	int idx = find(data, nodeList);
	if (idx == -1)
	{
		cout << -1 << endl;
		return;
	}
	node* delNode = nodeList[idx];
	if (delNode == root)
	{
		cout << -1 << endl;
		return;
	}

	node* parNode = delNode->parent;
	for (int i = 0; i < delNode->childList.size(); i++) {
		parNode->childList.push_back(delNode->childList[i]); // �����Ϸ��� ����� �ڽĵ��� parNode�� �ڽ����� ����
		delNode->childList[i]->parent = parNode; // �����Ϸ��� ����� �ڽĵ��� �θ� parNode�� ����
	}
	vector<node*>& child = parNode->childList;
	child.erase(child.begin() + find(data, child)); // ��ü ��� ���Ϳ��� delNode�� ����
	delete nodeList[idx]; // delNode �Ҵ� ����
	return;
}

void Tree::printParent(int data) {   // data�� �����ϴ� ����� �θ��� �����͸� ����ϴ� �Լ� 
	int idx = find(data, nodeList);
	if (idx == -1)
	{
		cout << -1 << endl;
		return;
	}
	node* curNode = nodeList[idx];
	cout << curNode->parent->data << endl;
}

// data ���� ������ ��忡 ���� child�� �����͵��� ��� ���
void Tree::printChild(int data) {
	int idx = find(data, nodeList);
	if (idx == -1)
	{
		cout << -1 << endl;
		return;
	}
	
	vector<node*>& child = nodeList[idx]->childList;
	if (child.size() == 0)
	{
		cout << -1 << endl;
		return;
	}
	for (int i = 0; i < child.size(); i++)
		cout << child[i]->data << " ";
	cout << endl;
}
void Tree::maxChild(int data)
{
	int max = -10000;
	int idx = find(data, nodeList);
	if (idx == -1)
	{
		cout << -1 << endl;
		return;
	}
	vector<node*> child = nodeList[idx]->childList;
	if (child.size() == 0)
	{
		cout << -1 << endl;
		return;
	}

	for (int i = 0; i < child.size(); i++)
	{
		if (max < child[i]->data)
			max = child[i]->data;
	}
	cout << max << endl;
}

int main(void)
{
	Tree tree(1);
	int testCase;
	cin >> testCase;
	while (testCase--)
	{
		string command;
		cin >> command;
		if (command == "insert")
		{
			int data1, data2;
			cin >> data1 >> data2;
			tree.insertNode(data1, data2);
		}
		else if (command == "delete")
		{
			int data;
			cin >> data;
			tree.deleteNode(data);
		}
		else if (command == "parent")
		{
			int data;
			cin >> data;
			tree.printParent(data);
		}
		else if (command == "child")
		{
			int data;
			cin >> data;
			tree.printChild(data);
		}
		else if (command == "maxChild")
		{
			int data;
			cin >> data;
			tree.maxChild(data);
		}
	}
}