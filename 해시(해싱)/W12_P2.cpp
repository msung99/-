#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

#define NOITEM 0  // �α׾ƿ� ����. �Ǵ� ȸ������ ���� �ȵȻ���
#define ISITEM 1  // ȸ�������� ���� ���� �α��α����� �� ���� 
#define AVAILABLE 2 // ȸ�����Ը� �� ����. ���� �α����� �ȵ� ����

struct entry {
	int key;
	string value;
	int valid;

	entry() {
		key = 0;
		value = "";
		valid = NOITEM;
	}

	entry(int key, string value) {
		this->key = key;
		this->value = value;
		valid = ISITEM;
	}

	void erase() {
		valid = AVAILABLE;
	}
};

class hashTable {
private:
	entry* table;
	int capacity;
	int hashFnc(int key);
public:
	hashTable(int N);
	void put(int key, string value);
	void erase(int key);
	void find(int key, string value);
	int get_num_key(string key);
};

hashTable::hashTable(int N) {
	capacity = N;
	table = new entry[capacity];
	return;
}

int hashTable::hashFnc(int key) {
	cout << "hashFnc:" << key % capacity << endl;
	return key % capacity;
}

// ȸ������
void hashTable::put(int  key, string value) {
	int index = hashFnc(key);

	// ���� ȸ�������� �ȵǾ��ִٸ� ȸ������ �õ�
	if (table[index].valid == NOITEM)
	{
		table[index] = entry(key, value);
		table[index].valid = AVAILABLE; // ȸ������ ǥ���� ����
		//cout << "put�� submit" << endl;
		cout << "Submit" << endl;
		return;
	}

	// AVAILABLE : �̹� ȸ�������� �Ǿ��ִ� ����.
	// ISITEM : �̹� ȸ�����Ե��ִ� ���� ����, ���� �ش� ������ ���� �α��α��� ���ִ� ���� 
	else if (table[index].valid == ISITEM || table[index].valid == AVAILABLE)
	{
		//cout << "put�� invalid" << endl;
		cout << "Invalid" << endl;
		return;
	}
}

// �α׾ƿ�
void hashTable::erase(int key) {
	int index = hashFnc(key);
	
	table[index].erase();
		
	//cout << "erase�� submit" << endl;
	cout << "Submit" << endl;
	return;
}

// �α��� �õ��ϱ�
void hashTable::find(int key, string value) {

	int index = hashFnc(key);

	// �������� �ʴ� ���̵��̰ų�, s�� ��й�ȣ�� ��ġ���� �ʴ� ���
	if (table[index].valid == NOITEM || table[index].value != value)
	{
		//cout << "find�� invalid" << endl;
		cout << "Invalid" << endl;  // �α��� ����
		return;
	}

	// ���̵�, ��й�ȣ ���� ��ġ������, �ش� ���̵� ���� �α��� ������ ���
	else if (table[index].valid == ISITEM && table[index].key == key && table[index].value == value)
	{
		//cout << "find�� quit" << endl;
		cout << "Quit" << endl;
		return;
	}

	// ���̵� ��й�ȣ ���� ��ġ�ϰ�, �α׾ƿ��� ����( = AVAILABLE ) �� ��� 
	else if (table[index].valid == AVAILABLE && table[index].key == key && table[index].value == value)
	{
		table[index] = entry(key, value); // �α��� ��û�� �����Ѵ�.
		
		//cout << "find�� submit" << endl;
		cout << "Submit" << endl;
		return;
	}
}

// �־��� ���ڿ��� 26�������� ��ȯ
int hashTable::get_num_key(string key) {
	int count = 0;
	int multi = 1;

	for (int i = 0; key[i]; ++i)
	{
		count += (key[i] - 'a') * multi;
		multi = multi * 26;
	}
	return count;
}

int main(void)
{
	hashTable h(200003);
	int t;
	cin >> t;
	while (t--)
	{
		string command;
		cin >> command;

		if (command == "signup")
		{
			string id, password;
			cin >> id >> password;
			int my_id = h.get_num_key(id);
			h.put(my_id, password);
		}
		else if (command == "login")
		{
			string id, password;
			cin >> id >> password;
			int my_id = h.get_num_key(id);
			h.find(my_id, password);
		}
		else if (command == "logout")
		{
			string id;
			cin >> id;
			int my_id = h.get_num_key(id);
			h.erase(my_id);
		}
	}
}