#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
	vector<int> key_list;
public:
	BST();
	node* search(node* curNode, int key);
	node* get_node(int key);
	void insert(int key);
	void remove(int key);
	
	void min(int k);  // ����Ž��Ʈ������ k��°�� ���� ������ ��� 
	int get_height(node* sub_root); // ����Ž��Ʈ������ key ���� ������ ��带 ��Ʈ ���� �ϴ� ����Ʈ���� ���̸� ���
	                      // Ʈ���� ���̴� ��� leaf �� ���� �� �ִ��� �ǹ�.
	int get_depth(node* cur);
};

BST::BST()
{
	root = NULL;
}


node* BST::search(node* curNode, int key) {
	if (curNode == NULL)  
		return NULL;

	if (curNode->key == key) 
		return curNode;  

	else if (curNode->key < key) 
		return search(curNode->right, key);

	else if (curNode->key > key) 
		return search(curNode->left, key);
}

void BST::insert(int key) {
	if (search(root, key) != NULL)  
		return;

	key_list.push_back(key); // Ű ����Ʈ key_list �� key ���� �߰� 

	node* newNode = new node(key);

	if (root == NULL)
	{
		root = newNode;
		return;
	}

	node* curNode = root; 
	node* parNode = NULL; 

	while (curNode != NULL) {
		parNode = curNode;
		if (curNode->key < key) {
			curNode = curNode->right;
		}
		else {
			curNode = curNode->left;
		}
	}
	newNode->parent = parNode;
	if (parNode->key < key) {
		parNode->right = newNode;
	}
	else {
		parNode->left = newNode;
	}
}


void BST::remove(int key) {
	node* delNode = search(root, key);
	if (delNode == NULL)
		return;

	node* parNode = delNode->parent; 
	node* childNode;


	if (delNode->left == NULL && delNode->right == NULL)
		childNode = NULL;


	else if (delNode->left == NULL && delNode->right != NULL)
		childNode = delNode->right; 

	else if (delNode->left != NULL && delNode->right == NULL)
		childNode = delNode->left;

	

	else {  
	
		childNode = delNode->right;  
		while (childNode->left != NULL)
			childNode = childNode->left;
	
		delNode->key = childNode->key;

		delNode = childNode;
		parNode = delNode->parent; 
		childNode = delNode->right;
	}


	
	// ���� ���� �����, key �� ����Ʈ key_list ���� �ش� Ű���� �����ϴ� ���� ��������.
	for (int i = 0; i < key_list.size(); i++)
	{
		if (key_list[i] == key)
			key_list.erase(key_list.begin() + i);
	}

	if (parNode == NULL) {
		root = childNode;
		root->parent = NULL;
	}

	
	else if (delNode == parNode->left) {
	
		
		parNode->left = childNode;  
		if (childNode != NULL)
			childNode->parent = parNode;
	}
	

	else { 
		parNode->right = childNode;
		if (childNode != NULL)
			childNode->parent = parNode; 
	}
	
	delete delNode; 
}

// �ּڰ� ���
void BST::min(int k)
{
	sort(key_list.begin(), key_list.end()); // �������� ������

	cout << key_list[k - 1] << endl; // �ּڰ� ���
}


node* BST::get_node(int key)
{
	node* curNode = search(root, key);
	return curNode;
}

// �ش� ��尡 ��Ʈ ����� ����Ʈ���� ���� ���ϱ� 
// main �Լ����� 1�� �� ������� ����ؾ� �Կ� ��������.
int BST::get_height(node* sub_root)
{
	int height = 0;

	if(sub_root != NULL)
	{
		height = 1 + max(get_height(sub_root->left), get_height(sub_root->right));
	}
	return height;
} 

// �ش� ����� ���� ���ϱ�
int BST::get_depth(node* cur)
{
	int count = 0;
	while (cur != root)
	{
		cur = cur->parent;
		count++;
	}

	return count;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	BST b1;
	int t;
	cin >> t;
	while (t--)
	{
		string a;
		cin >> a;
		if (a == "insert")
		{
			int data;
			cin >> data;
			b1.insert(data);
			node* cur = b1.get_node(data);
			cout << b1.get_depth(cur) << endl;
		}
		else if (a == "delete")
		{
			int data;
			cin >> data;
			node* cur = b1.get_node(data);
			cout << b1.get_depth(cur) << endl;
			b1.remove(data);
		}
		else if (a == "min")
		{
			int data;
			cin >> data;
			b1.min(data);
		}
		else if (a == "height")
		{
			int data;
			cin >> data;
			node* sub_root = b1.get_node(data); // �ش� ����Ʈ���� ��Ʈ ���
			cout << b1.get_height(sub_root) -1 << endl;  // 1 �� �A ���� ����� ����ؾ� �Կ� ��������!!!
		}
	}
}