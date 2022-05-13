#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct node {
	int key;
	node* parent;
	node* left;
	node* right;
	node(int key) {
		this->key = key;
		parent = left = right = NULL;
	}
};

class BST {
private:
	node* root;
public:
	BST();
	node* search(node* curNode, int key);
	node* get_node(int key);
	void insert(int key);
	// void remove(int key);
	int size(node* parNode);
};

BST::BST()
{
	root = NULL;
}

// Ž�� ����
// 1. ��ǥ ���� ���� ����� key �� ������ Ž�� ���� (Ž�� ������ ����)
// 2. ��ǥ ���� ���� ����� key ���� ������ ���� �ڽ����� �̵��Ͽ� Ž��
// 3. ��ǥ ���� ���� ����� key ���� ũ�� ������ �ڽ����� �̵��Ͽ� Ž��


// ��ǥ key �� ������ ����� �����͸� ����;
node* BST::search(node* curNode, int key) {
	if (curNode == NULL)  // key ���� ������ ��带 ã�� ���ϸ�(= external �����) NULL �� ����
		return NULL;

	if (curNode->key == key) // ���� ����� key ���� ��ǥ key ���� ��ġ�ϴ� ���
		return curNode;  // �����ϸ� ��

	else if (curNode->key < key)   // ���� ����� key ������ ��ǥ key���� �� ū ���
		return search(curNode->right, key); // ������ ����Ʈ���� ������

	else if (curNode->key > key) // ���� ����� key ������ ��ǥ key���� �� ���� ���
		return search(curNode->left, key); // ���� ����Ʈ���� ������
}

// Ž�� ����� ������ ������� ��Ʈ���� external ������ ������ ��, external ����� �ڽ����� ���ο� ��带 �߰�
void BST::insert(int key) {
	if (search(root, key) != NULL)  // �־��� key�� �ش��ϴ� ��尡 �̹� ������ ���, �������� �ʰ� ����
		return;

	node* newNode = new node(key); // ������ ���ο� ���

	if (root == NULL) // ����ִ� ����Ž��Ʈ���� ���
	{
		root = newNode; // ������ ��带 ��Ʈ�� ����
		return;
	}

	node* curNode = root; // ���� ������ ����� ��ġ�� Ž���ϴ� ����
	node* parNode = NULL; // ���� ������ ����� �θ� Ž���ϴ� ����

	// ��Ʈ�������� �����ؼ� Ž���� �����ؼ�, ���� ������ ����� ��ġ�� ã�Ƴ���.
	// ������ ������ ���� ���� ��忡 ���� ��, ���� ����� �ڽ����� ���ο� ��带 �߰��Ѵ�.
	// <=> <�̷� ����>TreeSearch() �� ȣ���ؼ� ������ ������ ���� external ��忡 ������, ���ϵǴ� external ��� ��ġ�� ���ο� ��带 �����Ѵ�.
	while (curNode != NULL) {
		parNode = curNode;
		if (curNode->key < key) {
			curNode = curNode->right;
		}
		else {
			curNode = curNode->left;
		}
	}
	// while ���� ������ curNode �� NULL�� �ǰ�, parNode �� ���� ��尡 �Ǿ��� ����. 
	// ��, NULL ���� ������ ��ġ�� curNode �ڸ��� ���ο� ��� newNode �� �����Ѵ�. newNode �� �θ�� parNode ���� ��尡 �Ǵ� ���̴�.


	// ���� ���� ���ο� ��带 ���� ���� 
	newNode->parent = parNode;
	if (parNode->key < key) {
		parNode->right = newNode;
	}
	else {
		parNode->left = newNode;
	}
}


// curNode �� ��Ʈ ���� �ϴ� ����Ʈ���� ũ�⸦ ���� 
int BST::size(node* curNode)
{
	if (curNode == NULL)
		return 0;

	return size(curNode->left) + size(curNode->right) + 1;
}

// key ���� ������ ����� ���� �ڽĳ�带 ����
node* BST::get_node(int key)
{
	node* parNode = search(root, key);
	return parNode->left;
}

int main(void)
{
	BST b1;
	int n, m;
	cin >> n >> m;
	while (n--)
	{
		int data;
		cin >> data;
		b1.insert(data);
	}

	while (m--)
	{
		int key;
		cin >> key;
		node* curNode = b1.get_node(key); // ���� ����Ʈ���� ��Ʈ ��带 ����
		cout << b1.size(curNode) << endl; // ���� ����Ʈ���� ����� ��� 
	}
}