#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct node {
	int data;
	node* parent;
	vector<node*> childList; // �ڽ� ������ ����Ű�� �����͵��� ���Ϳ� ����

	node(int data, node* parent)
	{
		this->data = data;
		this->parent = parent;
	}
};

class Tree {
private:
	node* root;
	vector<node*> nodeList; // Ʈ���� ������ �ּҰ��� �����ϰ� �ִ� ���� ����Ʈ
public:
	Tree(int data);
	int find(int data, vector<node*>& list); // ����� �����͵��� �����ϴ� ���� ����Ʈ���� data ���� ������ ����� �ε����� ����
	void insertNode(int parData, int data); // data ���� ������ ���ο� ��带 Ʈ���� insert
	void deleteNode(int data); // Ʈ������ data ���� ������ �ִ� ��带 ����
	void printParent(int data); // Ʈ������ data ���� ������ �ִ� ����� �θ����� ������ ���� ���
	void printChild(int data); // Ʈ������ data ���� ������ �ִ� ����� �ڽĳ����� ������ ������ ���
	void maxChild(int data); // Ʈ���� ���� �߿� ������ �ִ��� ���
	void minChild(int data);
	void printAncestors(int data);
};

Tree::Tree(int data)
{
	node* newNode = new node(data, NULL);
	root = newNode;
	nodeList.push_back(newNode);
}

// ����� �����͵��� �����ϴ� ���� ����Ʈ���� data ���� ������ ����� �ε����� ����
int Tree::find(int data, vector<node*>& list)
{
	for (int i = 0; i < list.size(); i++) 
	{
		if (data == list[i]->data)
			return i;
	}
	return -1;
}

void Tree::insertNode(int parData, int data)
{
	if (find(data, nodeList) != -1)
	{
		cout << -1 << endl;
		return;
	};

	int idx = find(parData, nodeList);
	if (idx == -1)
	{
		cout << -1 << endl;
		return;
	}
	node* parNode = nodeList[idx];
	node* newNode = new node(data, parNode);
	parNode->childList.push_back(newNode);
	nodeList.push_back(newNode);
}

void Tree::deleteNode(int data)
{
	int idx = find(data, nodeList);
	if (idx == -1)
	{
		cout << -1 << endl;
		return;
	}
	node* delNode = nodeList[idx];
	node* parNode = delNode->parent;
	for (int i = 0; i < delNode->childList.size(); i++)
	{
		delNode->childList[i]->parent = parNode;
		parNode->childList.push_back(delNode->childList[i]);
	}
	vector<node*>& child = parNode->childList;
	child.erase(child.begin() + find(data, child));
	delete nodeList[idx];
	return;
}

void Tree::printParent(int data)
{
	int idx = find(data, nodeList);
	if (idx == -1)
	{
		cout << -1 << endl;
		return;
	}
	node* curNode = nodeList[idx];
	node* parNode = curNode->parent;
	cout << parNode->data << endl;
}

void Tree::printChild(int data) {
	int idx = find(data, nodeList);
	if (idx == -1)
	{
		cout << -1 << endl;
		return;
	}
	node* curNode = nodeList[idx];
	if (curNode->childList.size() == 0)
	{
		cout << -1 << endl;
		return;
	}
	for (int i = 0; i < curNode->childList.size(); i++)
		cout << curNode->childList[i]->data << ' ';
	cout << endl;
}

void Tree::maxChild(int data)
{
	int idx = find(data, nodeList);
	if (idx == -1)
	{
		cout << -1 << endl;
		return;
	}
	node* curNode = nodeList[idx];
	if (curNode->childList.size() == 0)
	{
		cout << -1 << endl;
		return;
	}
	int max = -99999;
	for (int i = 0; i < curNode->childList.size(); i++)
	{
		if (max < curNode->childList[i]->data)
			max = curNode->childList[i]->data;
	}
	cout << max << endl;
}

void Tree::minChild(int data)
{
	int idx = find(data, nodeList);
	if (idx == -1)
	{
		cout << -1 << endl;
		return;
	}
	int min = 999999;
	vector<node*> child = nodeList[idx]->childList;
	for (int i = 0; i < child.size(); i++)
	{
		if (min < child[i]->data)
			min = child[i]->data;
	}
	cout << max << endl;
}

// ������� ���ʴ�� ���������� �ö󰡸鼭 ������ ���� ���
void Tree::printAncestors(int data)
{
	int idx = find(data, nodeList);
	if (idx == -1)
		return;
	node* curNode = nodeList[idx];
	node* parNode = curNode->parent;
	while (true)
	{
		if (parNode == root) // ��Ʈ ��带 �����ٸ� ��Ʈ ����� �����Ͱ��� ����ϰ� while�� ����
		{
			cout << parNode->data << ' ' << endl;
			return;
		}
		cout << parNode->data << ' '; // ��Ʈ ��带 ������ �������� ��� �� ��������� Ÿ�� �ö󰡸鼭 �����Ͱ� ���
		parNode = parNode->parent;
	}
}

int main(void)
{
	Tree tree(1);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n - 1; i++)
	{
		int parData, childData;
		cin >> parData >> childData;
		tree.insertNode(parData, childData);
	}

	for (int i = 0; i < m; i++)
	{
		int data;
		cin >> data;
		tree.printAncestors(data);
	}
}