class Node {
public:
	Node(const int data, Node* prev = NULL, Node* next = NULL);

	int getData() const; // ���� ����� ������ ����
	Node* getPrev() const;// ���� ����� ���� ��� ����
	Node* getNext() const; // ���� ����� ���� ��� ����
	void setData(const int data); // ���� ����� �����Ͱ� ����
	void setPrev(Node* node); // ���� ����� ���� ��� ����
	void setNext(Node* node); // ���� ����� ���� ��� ����

private:
	int data;
	Node* prev;
	Node* next;
};

Node::Node(const int data, Node* prev, Node* next)
{
	this->data = data;
	this->prev = prev;
	this->next = next;
}

int Node::getData() const {
	return data;
}

Node* Node::getPrev() const {
	return prev;
}

Node* Node::getNext() const {
	return next;
}

void Node::setData(const int data) {
	this->data = data;
}

void Node::setPrev(Node* node)
{
	this->prev = node;
}

void Node::setNext(Node* node)
{
	this->next = node;
}
