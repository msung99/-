#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

int main(void)
{
	map<string, string> list2;  // �⼮ ���¸� �����ϴ� ����Ʈ

	map<string, string> hash1;
	map<string, string> hash2;
	int present = 0; // ���� �⼮ ���¼�

	int t;
	cin >> t;
	while (t--)
	{
		string a;
		cin >> a;
		if (a == "add")
		{
			string key, value;
			cin >> key >> value;
			hash1.insert(make_pair(key, value));
			hash2.insert(make_pair(value, key));

			list2.insert(make_pair(value, "absent"));  // 0 : NOITEM, 1 : �⼮, 2 : �Ἦ
		}
		else if (a == "delete")
		{
			string key;
			cin >> key;
			string key2 = hash1[key];
			if (list2[key2] == "present") // �⼮ ������ ���
			{
				// cout << "delete ȣ��" << endl;
				present--;
			}
			hash1.erase(key);
			hash2.erase(key2);
			list2.erase(key2);

			//auto key2 = hash1.find(key);
		}
		else if (a == "name")
		{
			string key;
			cin >> key;
			cout << hash1[key] << endl;
		}
		else if (a == "present")
		{
			string key;
			cin >> key;
			if (hash2.count(key) == 1)  // count(key) : �־��� key�� ��� ������ ����.  => 0 �Ǵ� 1�� ����
			{
				cout << hash2[key] << endl;
				if (list2[key] == "absent") // �Ἦ ������ ���
				{
					// cout << "present ȣ��" << endl;
					list2[key] = "present"; // �⼮ ���·� ����
					present++;
				}
			}
			else
			{
				cout << "Invalid" << endl;
			}
		}
		else if (a == "absent")
		{
			string key;
			cin >> key;
			if (hash2.count(key) == 1)
			{
				cout << hash2[key] << endl;
				if (list2[key] == "present") // �⼮ ������ ���
				{
					// cout << "absent ȣ��" << endl;
					list2[key] = "absent";
					present--;
				}
			}
			else
			{
				cout << "Invalid" << endl;
			}
		}
	}
	cout << present << endl;
}