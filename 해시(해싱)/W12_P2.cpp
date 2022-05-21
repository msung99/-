#include <iostream>
#include <cmath>
#define EMPTY 0   // ȸ������ ��ü�� �������� ���� ���. ��, �ش� ���� ����ִ� ���
#define LOGIN 1   // ȸ�������� ���� �α��α��� �� ���
#define LOGOUT 2  // ȸ�������� ������, �α׾ƿ� ������ ���
#define SIGNED 3  // ȸ�����Ը� 
using namespace std;

struct entry {
	int key;
	string value;
	int valid;

	entry() {
		key = 0;
		value = "";
		valid = EMPTY;
	}

	// �־��� ���ڿ��� 26������ ��ȯ
	int tolnt(string key) {
		int num = 0;
		for (int i = 0; i < key.length(); i++) {
			num = num + (key[i] - 97) * pow(26, i);
		}
		return num;
	}

	entry(string key, string value) {
		this->key = tolnt(key);
		this->value = value;
		valid = SIGNED;
	}

	void erase() {
		valid = LOGOUT;
	}
};

class hashTable {
private:
	entry* table;
	int capacity;
	int divisor;
public:
	hashTable(int N, int M);
	int hashFunc(int key);
	int hashFunc2(int key);
	int toInt(string key);
	void signUp(string key, string value);
	void logout(string key);
	void login(string key, string value);
};

hashTable::hashTable(int N, int M) {
	divisor = M;
	capacity = N;
	table = new entry[capacity];
}

// 1�� �ؽ��Լ�
int hashTable::hashFunc(int key) {
	return key % capacity;
}

// 2�� �ؽ��Լ�
int hashTable::hashFunc2(int key) {
	return divisor - (key % divisor);
}

// �־��� ���ڿ��� 26������ ��ȯ
int hashTable::toInt(string key) {
	int num = 0;
	for (int i = 0; i < key.length(); i++) {
		num += static_cast<int>((key[i] - 97)) * pow(26, i);
	}
	return num;
}

// ȸ������
void hashTable::signUp(string key, string value) {
	int realKey = toInt(key);  // // �츮�� ã�ƾ��� ��Ʈ���� key (= ã�ƾ��� ȸ���� ���̵�). 26������ ������ key ��
	int index = hashFunc(realKey);
	int probe = 1;

	// ���ڸ��� ã�Ƽ� Ž���� ����. Ž���� ������ ã�Ƴ� ���ڸ��� ��Ʈ�� �����Ѵ�.
	while (table[index].valid != EMPTY && probe <= capacity) {
		if (table[index].key == realKey) // �̹� ȸ�����Ե� ���̵��� ���. ��, key ���� ������ ��Ʈ���� �̹� �迭�� �����ϴ� ���
		{
			cout << "Invalid" << endl;  // �̹� ȸ������ �������ϱ�, ȸ������ ���� �ʰ� ����
			return;
		}
		index = hashFunc(index + hashFunc2(realKey)); // ���� �ؽ��� Ȱ���� �浹 ����
		probe++;
	}
	if (probe > capacity)
		return;

	// ȸ������ �õ�
	table[index] = entry(key, value); // Ž�� ������ ���� ã�Ƴ� ���ڸ��� ��Ʈ���� ���� 
	cout << "Submit" << endl;
	return;
}

// �α׾ƿ� => �־��� key ���� ���̵�� ������ ȸ���� ã�Ƴ��� �α׾ƿ� ��Ų��.
void hashTable::logout(string key) {
	int realKey = toInt(key); // �츮�� ã�ƾ��� ��Ʈ���� key (= ã�ƾ��� ȸ���� ���̵�)
	int index = hashFunc(realKey);
	int probe = 1;

	// Ž���ϴ� �ش� ���� ��Ʈ���� ������ �����Ͱ� ����Ǿ� �ִ� ��Ʈ�����ų�(= ȸ������o, �α���x), ��Ʈ���� ����Ǿ� �ִ� ���(= ȸ������o, �α���o) �� Ž���� ����
	while (table[index].valid != EMPTY && probe <= capacity) {
		if (table[index].key == realKey && table[index].valid == LOGIN) // �α׾ƿ��� �ؾ��� ����� ã�� ��� 
		{
			table[index].erase();  // �α׾ƿ�
			cout << "Submit" << endl;
			return;
		}
		index = hashFunc(index + hashFunc2(realKey)); // ���� �ؽø� Ȱ���� �浹�� �����ϸ鼭 �α׾ƿ��� ��ų �ٿ� ����� Ž���� ����
		probe++;
	}
	return;
}

void hashTable::login(string key, string value) {
	int realKey = toInt(key);
	int index = hashFunc(realKey);
	int probe = 1;
	while (table[index].valid != EMPTY && probe <= capacity) {

		// ���̵�� ��й�ȣ�� ��ġ������, �ش� ������ �̹� �α��� �Ǿ��ִ� ������ ���
		if (table[index].valid == LOGIN && table[index].key == realKey && table[index].value == value) {
			cout << "Quit" << endl;
			return;
		}

		// ���̵�� ��й�ȣ ���� ��ġ�ϰ�, �ش� ������ ���� �α׾ƿ� �� ������ ���
		else if ((table[index].valid == LOGOUT || table[index].valid == SIGNED) && table[index].key == realKey && table[index].value == value) {
			table[index].valid = LOGIN;
			cout << "Submit" << endl;
			return;
		}

		// ��й�ȣ�� ��ġ���� �ʴ� ���
		else if (table[index].key == realKey && table[index].value != value) {

			cout << "Invalid" << endl;
			return;
		}
		index = hashFunc((index + hashFunc2(realKey))); //capacity�� �Ѿ�� �������� ������ֱ� �����̴�.

		probe++;
	}

	// �������� �ʴ� ����(���̵�)�� ���
	cout << "Invalid" << endl;
	return;
}

int main() {
	int a;
	cin >> a;
	hashTable t{ 200000, 7 };

	string in;
	string x;
	string y;
	for (int i = 0; i < a; i++) {
		cin >> in;
		if (in == "signup") {
			cin >> x >> y;
			t.signUp(x, y);
		}
		else if (in == "login") {
			cin >> x >> y;
			t.login(x, y);
		}
		else if (in == "logout") {
			cin >> x;
			t.logout(x);
		}

	}
}