#include <iostream>
#include <string>
#include <map>
using namespace std;


int main(void)
{
	map<string, string> list; // ȸ������ ���¸� �����ϴ� ����Ʈ
	map<string, string> hash;

	int t;
	cin >> t;
	while(t--)
	{
		string a;
		cin >> a;
		if (a == "signup")
		{
			string key, value;
			cin >> key >> value;
			if (hash.count(key) == 1) // �̹� ȸ�����Ե� ���
			{
				cout << "Invalid" << endl;
			}
			else
			{
				hash.insert(make_pair(key, value));
				list.insert(make_pair(key, "logout"));  // "�α׾ƿ�" ���·� ������!!!!!!!!!!!!!!
				cout << "Submit" << endl;
			}
		}
		else if (a == "login")
		{
			string key, value;
			cin >> key >> value;

			if (hash.count(key) == 0) // �������� �ʴ� ���̵��� ���
			{
				cout << "Invalid" << endl;
			}
			else if (hash[key] != value) // ��й�ȣ�� ��ġ���� �ʴ� ���
			{
				cout << "Invalid" << endl;
			}
			else if (list[key] == "login" && hash[key] == value)  // �Ƶ� ��� ��� ��ġ������ �̹� �α��� ������ ���
			{
				cout << "Quit" << endl;
			}
			else if (list[key] == "logout" && hash[key] == value) // �̴� ��� ��� ��ġ�ϰ� �α׾ƿ� ������ ���
			{
				list[key] = "login"; // �α��� ���·� �ٲ�
				cout << "Submit" << endl;
			}
		}
		else if (a == "logout")
		{
			string key;
			cin >> key;
			list[key] = "logout"; // �α׾ƿ� ���·� �ٲ�
			cout << "Submit" << endl;
		}
	}
}