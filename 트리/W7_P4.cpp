#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct node {
	int data;   // ����� ������� 
	int data2;  // �b�� �뷮 ������ ��
	node* parent; 
	vector<node*> childList; 

	node(int data, node* parent) {
		this->data = data;
		this->parent = parent;
	}
};

class Tree {
private:
	node* root; 
	vector<node*> nodeList; 
public:
	int find(int data, vector<node*>& list);
	Tree(int data);
	void insertNode(int parData, int data);
	int postOrder(node* curNode);  // ���� ��ȸ�� ������
	node* findNode(int data); // Ʈ���� data ���� ������ ��带 Ž���� �� ��带 ����
	void folderSize(int data, int changeData); //  �� data ��忡�ٰ� ������ �뷮 ���� �Ҵ��Ŵ 
};

Tree::Tree(int data)
{
	node* newNode = new node(data, NULL);
	root = newNode;
	nodeList.push_back(root);
}


int Tree::find(int data, vector<node*>& list) {  
	for (int i = 0; i < list.size(); i++) {
		if (list[i]->data == data)
			return i;
	}
	return -1;
}

void Tree::insertNode(int parData, int data) {
	if (find(data, nodeList) != -1) 
	{
		cout << -1 << endl;
		return;
	}

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
	return;
}

node* Tree::findNode(int data)
{
	int idx = find(data, nodeList);
	return nodeList[idx];
}

// ������ȸ�� ����Ʈ���� �� ���� �뷮�� ����� ���
int Tree::postOrder(node* curNode)
{
	if (curNode->childList.size() == 0)
		return curNode->data2; 

	int sum = 0;
	for (int i = 0; i < curNode->childList.size(); i++)
	{
		sum += postOrder(curNode->childList[i]); // curNode ����� �� ����Ʈ���� ���� �뷮�� �ջ��� sum���� ��� �߰� ���� curNode�� �� �뷮�� ����
	}
	return sum + curNode->data2; // �� ����Ʈ���� �뷮�� sum�� ��� ���ߴٸ�, ���������� �ڽ��� ���� �뷮�� ���ؾ��� �� �뷮�� �ȴ�.
}


void Tree::folderSize(int data, int folderSize) // �� ��忡�� ������ �뷮 ������ ���� �Ҵ�
{
	int idx = find(data, nodeList);
	node* curNode = nodeList[idx];
	curNode->data2 = folderSize;
}

int main(void)
{
	int size, n;
	cin >> size >> n;
	
	Tree tree(1);
	
	for (int i = 0; i < size - 1; i++)
	{
		int parData, data;
		cin >> parData >> data;
		tree.insertNode(parData, data);
	}

	// �� ��忡�� ������ �뷮 ������ ���� �Ҵ�
	for (int i = 0; i < size; i++) 
	{
		int data, changeData;
		cin >> data >> changeData;
		tree.folderSize(data, changeData);
	}

	// ������ȸ�� ����Ʈ���� �� ���� �뷮�� ����� ���
	for (int i = 0; i < n; i++)
	{
		int data;
		cin >> data;
		node* p = tree.findNode(data);
		cout << tree.postOrder(p) << endl;
	}
}