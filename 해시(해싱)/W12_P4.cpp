// �� ������ key, value ������ ��� �ؽ��� �ϴ� �ؽ����̺��̴�.
// key ���� ������, �� ���ڶ� ������ ����. ������ value �� ���ڿ��̹Ƿ� 26�������� ��ȯ���ֵ��� �Ѵ�.

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

#define EMPTY 0  // �⼮�� ��ܿ� ���� ���
#define CHECK 1 // �⼮�� ��ܿ� ������, �⼮ ������ ���
#define NOCHECK 2 // �⼮�� ��ܿ� ������, �Ἦ ������ ���
#define AVAILABLE 3     // �⼮�� ��ܿ� ����. �⼮ �� �Ἦ ���´� ���� �������� ����.

struct entry {
	int key;
	int trans_value; // 26�������� ��ȯ�� value ��
	string value;
	int valid;

	entry() {
		key = 0;
		value = "";
		valid = EMPTY;
	}

	entry(int key, string value) {
		this->key = key;
		this->value = value;
		valid = NOCHECK;   // �⼮�� ��ܿ� �ö��ִ� ����
	}
	void erase() {
		valid = AVAILABLE; // �Ἦ ���·� ó��
	}
};


// 1. key ���� �ؽ��ؼ� Ž��,����,������ �����ϴ� �ؽ����̺�
class hashTable1 {
private:
	entry* table;
	int capacity;
	int divisor;
public:
	hashTable1(int N, int M);
	int hashFunc(int key);
	int hashFunc2(int key);

	void add(int key, string value); // �����ο� (key, value) ��Ʈ�� �л��� ���
	string delection(int key);  // �й��� key �� �л��� �⼮�ο��� ����
	void name(int key);  // �й��� key �� �л��� �̸�(value) �� ���

	void make_present(int key); // hashTable2 �� present, absent �Լ��� ȣ���ؼ� �ش� �л�(��Ʈ��)�� �⼮ �� �Ἦ ���θ� hashTable1������ �����ؾ� �ϴ°��
	void make_absent(int key);
};

hashTable1::hashTable1(int N, int M) {
	divisor = M;
	capacity = N;
	table = new entry[capacity];
}

// 1�� �ؽ��Լ�
int hashTable1::hashFunc(int key) {
	return key % capacity;
}

// 2�� �ؽ��Լ�
int hashTable1::hashFunc2(int key) {
	return divisor - (key % divisor);
}

void hashTable1::add(int key, string value){
	int index = hashFunc(key);
	int probe = 1;

	while (table[index].valid != EMPTY && probe <= capacity) {
		index = hashFunc(index + hashFunc2(key));
		probe++;
	}

	if (probe > capacity)
		return;

	table[index] = entry(key, value);
	return;
}

string hashTable1::delection(int key) {
	int index = hashFunc(key);
	int probe = 1;

	// cout << "table[index].vaild : " << table[index].valid << endl;

	while (table[index].valid != EMPTY && probe <= capacity) {
		if (table[index].valid != EMPTY && table[index].key == key)
		{
			table[index].erase();
			return table[index].value;  // ������ ��Ʈ���� value �� ����. ���ϵ� value �� hashTable2 ���� Ȱ���Ѵ�. ��, hashTable2 �� ��Ʈ���� �����ҋ� Ȱ��
		}
		index = hashFunc(index + hashFunc2(key));
		probe++;
	}

	return "";
}

void hashTable1::name(int key) {
	int index = hashFunc(key);
	int probe = 1;

	while (table[index].valid != EMPTY && probe <= capacity)
	{
		if (table[index].valid != EMPTY && table[index].key == key)
		{
			cout << table[index].value << endl;
			return;
		}
		index = hashFunc(index + hashFunc2(key));
		probe++;
	}
}

// �־��� key �� �ش��ϴ� ��Ʈ��(�л�)�� �⼮ ���·� ����
void hashTable1::make_present(int key)
{
	if (key == -1)
		return;

	int index = hashFunc(key);
	int probe = 1;

	while (table[index].valid != EMPTY && probe <= capacity)
	{
		if (table[index].valid != EMPTY && table[index].key == key)
		{
			table[index].valid = CHECK; // �⼮ 
			return;
		}
		index = hashFunc(index + hashFunc2(key));
		probe++;
	}
}

// �־��� key �� �ش��ϴ� ��Ʈ��(�л�)�� �Ἦ ���·� ����
void hashTable1::make_absent(int key)
{
	if (key == -1)
		return;

	int index = hashFunc(key);
	int probe = 1;

	while (table[index].valid != EMPTY && probe <= capacity)
	{
		if (table[index].valid != EMPTY && table[index].key == key)
		{
			table[index].valid = NOCHECK; // �Ἦ 
			return;
		}
		index = hashFunc(index + hashFunc2(key));
		probe++;
	}
}


// 2. value ���� �ؽ��ؼ� Ž��, ����, ������ �����ϴ� �ؽ����̺�

class hashTable2 {
private:
	entry* table;
	int capacity;
	int divisor;
public:
	hashTable2(int N, int M);
	int hashFunc(int key);
	int hashFunc2(int key);

	int toInt(string key);
	void add(int key, string value); // �����ο� (key, value) ��Ʈ�� �л��� ���
	void delection(string value);
	int present(string value);
	int absent(string value);
};

hashTable2::hashTable2(int N, int M) {
	divisor = M;
	capacity = N;
	table = new entry[capacity];
}

// 1�� �ؽ��Լ�
int hashTable2::hashFunc(int key) {
	return key % capacity;
}

// 2�� �ؽ��Լ�
int hashTable2::hashFunc2(int key) {
	return divisor - (key % divisor);
}

// �ش� ���ڿ��� 26�������� ��ȯ
int hashTable2::toInt(string key) {
	int num = 0;
	for (int i = 0; i < key.length(); i++) {
		num += int(key[i] - 97) * pow(26, i);
	}
	//  
	return num;
}

void hashTable2::add(int key, string value) {
	int rearValue = toInt(value);
	int index = hashFunc(rearValue);
	int probe = 1;

	while (table[index].valid != EMPTY && probe <= capacity) {
		index = hashFunc(index + hashFunc2(rearValue));
		probe++;
	}

	if (probe > capacity)
		return;

	table[index] = entry(key, value);
	return;
}

void hashTable2::delection(string value)
{
	int rearValue = toInt(value);
	int index = hashFunc(rearValue);
	int probe = 1;

	// ������ key �� �ؽ����̺��� ã�Ƴ���(Ž��)
	while (table[index].valid != EMPTY && probe <= capacity) {
		if (table[index].valid != EMPTY && table[index].value == value) // ������ ��Ʈ���� ã�Ƴ� ��� 
		{
			table[index].valid = EMPTY; // EMPTY ó��(= ������ ��ܿ��� ����)
			return;
		}
		index = hashFunc(index + hashFunc2(rearValue));
		probe++;
	}
	return;
}

int hashTable2::present(string value) {
	int realValue = toInt(value);
	int index = hashFunc(realValue);
	int probe = 1;

	while (table[index].valid != EMPTY && probe <= capacity)
	{
		if (table[index].value == value && table[index].valid != EMPTY)
		{
			table[index].valid = CHECK; // �⼮ ���·� ������
			cout << table[index].key << endl; // �ش� �л��� �й��� ���
			return table[index].key;  // ���ϵ� key �� hashTable �� ������ ��Ʈ���� �⼮ ó���ϱ� ���� Ȱ��
		}
		index = hashFunc(index + hashFunc2(realValue));
		probe++;
	}

	cout << "Invalid" << endl;  // �⼮�ο� �������� ���� ���
	return -1;
}

int hashTable2::absent(string value)
{
	int realValue = toInt(value);
	int index = hashFunc(realValue);
	int probe = 1;

	while (table[index].valid != EMPTY && probe <= capacity)
	{
		if (table[index].value == value && table[index].valid != EMPTY)
		{
			if (table[index].value == value && table[index].valid != EMPTY)
			{
				table[index].valid = NOCHECK;
				cout << table[index].key << endl;
				return table[index].key; // ���ϵ� key �� hashTable �� ������ ��Ʈ���� �⼮ ó���ϱ� ���� Ȱ��
			}
			index = hashFunc(index + hashFunc2(realValue));
			probe++;
		}
	}
	cout << "Invalid" << endl;
	return -1;
}

int main(void)
{
	int t;
	cin >> t;
	hashTable1 h1(500000, 13);
	hashTable2 h2(500000, 13);

	while (t--)
	{
		string a;
		cin >> a;
		if (a == "add")
		{
			int x;
			string s;
			cin >> x >> s;
			h1.add(x, s);
			h2.add(x, s);
		}
		else if (a == "delete")
		{
			int x;
			cin >> x;
			string value = h1.delection(x);
			h2.delection(value);
		}
		else if (a == "name")
		{
			int x;
			cin >> x;
			h1.name(x);
		}
		else if (a == "present")
		{
			string s;
			cin >> s;
			int key = h2.present(s);
			h1.make_present(key);
		}
		else if (a == "absent")
		{
			string s;
			cin >> s;
			int key = h2.absent(s);
			h1.make_absent(key);
		}
	}
}