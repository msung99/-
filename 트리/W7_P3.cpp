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

	void preOrder(node* curNode, int count);
	void postOrder(node* curNode, int count);
	node* findNode(int data);
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

node* Tree::findNode(int data)
{
	int idx = find(data, nodeList);
	return nodeList[idx];
}

void Tree::preOrder(node* curNode, int count)
{
	cout << count << ' ';
	for (int i = 0; i < curNode->childList.size(); i++)
	{
		preOrder(curNode->childList[i], count + 1);
	}
}

void Tree::postOrder(node* curNode, int count)
{
	for (int i = 0; i < curNode->childList.size(); i++)
	{
		postOrder(curNode->childList[i], count + 1);
	}
	cout << count << ' ';
}

int main(void)
{
	int testCase, n;
	cin >> testCase;
	while (testCase--)
	{
		Tree tree(1);
		cin >> n;
		for (int i = 0; i < n - 1; i++)
		{
			int parData, data;
			cin >> parData >> data;
			tree.insertNode(parData, data);
		}

		node* root = tree.findNode(1);
		tree.postOrder(root, 0);
	}
	cout << endl;
}