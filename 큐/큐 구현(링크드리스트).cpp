class Queue {
public:
	Queue();
	~Queue();

	bool empty() const;
	int size() const;
	int front() const;
	void push(const int data);
	int popFront();

	void display() const;

private:
	Node* headNode;
	Node* tailNode;
	int dataSize; // ť�� ����� ������ ����
};

bool Queue::empty() const {
	if (dataSize == 0)
		return 1;
	else
		return 0;
}

int Queue::size() const {
	return dataSize;
}

int Queue::front() const {
	if (empty()) {
		return -1;
	}
	return headNode->getData();
}

void Queue::push(const int data) {
	if (empty())
	{
		headNode = tailNode = new Node(data);
		dataSize++;
		return;
	}
	Node* node = new Node(data, tailNode, NULL); // ���� �Ҵ��Ϸ��� ��� node �� ���� ��带 tail ��, ���� ��带 NULL �� ����
	tailNode->setNext(node); // tail ����� ���� ��带 node �� ����
	tailNode = node; // tail ��� �ֽ�ȭ
	dataSize++;
}

int Queue::popFront() {
	int frontData = front(); // ������ ����� ������ => ���࿡ ������ ��������� ���� �߻���
	Node* node = headNode;

	headNode = headNode->getNext(); // head ��带 ��ĭ �̵�

	// headNode == NULL �� ��� : ���ÿ��� ��尡 �� �ϳ����� ���� (head ��� �����ϰ� �ϳ����� ��) �����Ϸ��� ���
	// ��, if���� �� ���� ���ÿ� ��尡 2�� �̻� ���� �� ������ �ϴ� ����̴�.
	if (headNode != NULL)
	{
		headNode->setPrev(NULL); // head ����� ���� ��带 NULL �� ����
	}
	delete node; // ���� head ��带 �޸𸮿��� ����
	dataSize--;
	return frontData; // ������ ����� ������ ����
}

void Queue::display() const {
	if (empty())
	{
		cout << "Queue is empty";
	}
	else
	{
		cout << "size:" << size() << "\n";
		cout << "front:" << front() << "\n";
		for (auto i = headNode; i != NULL; i = i->getNext())
		{
			cout << i->getData() << " ";
		}
		cout << endl;
	}
}

