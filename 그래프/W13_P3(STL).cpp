#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main(void)
{
	vector<int> adj_list[2001];
	
	int t, n, a;
	cin >> t >>  n;
	for (int i = 0; i < n; i++)  // �� ������ Ǯ�� ������ ������ �Ԏ����� �ʿ䰡 ����. �Է¹��� ������ ������ �� ��������! �������
	{
		cin >> a;  // a�� �Է°��� ó������ �ӽú���. (������� �Է°��� ó��)
	}
	while (t--)
	{

		string a;
		cin >> a;
		if (a == "insertEdge")
		{
			int u, v;
			int check = 0;
			cin >> u >> v;

			for (int i = 0; i < adj_list[u].size(); i++)  // �� ������ �մ� ������ �̹� �����ϴ��� üũ
			{
				if (adj_list[u][i] == v)  // ���� (u, v) �� �̹� �����ϴ� ���
				{
					cout << "Exist" << endl;
					check = 1;
				}
			}
			if (check == 0)
			{
				adj_list[u].push_back(v);
				adj_list[v].push_back(u);
			}
		}
		else if (a == "eraseEdge")
		{
			int u, v;
			int check = 0;
			int index = 0;
			cin >> u >> v;

			for (int i = 0; i < adj_list[u].size(); i++)  // �� ������ �մ� ���� (u, v) �� �����ϴ��� ã�� ����
			{
				 // �� ������ �մ� ���� (u, v) �� �����Ѵٸ� 
				if (adj_list[u][i] == v)
					check = 1;
			}
			
			// �� ������ �մ� ���� (u, v) �� �����Ѵٸ� ������
			if (check == 1)
			{
				// ������ ������ �� ��������Ʈ���� ���° �ε����� ����Ǿ� �ִ����� ���
				// 
				// => find(adj_list[u].begin(), adj_list[u].end(), v) : adj_list[u] ���Ϳ��� ������ v �� �ε��� ���ͷ����͸� ����.
				// ������ v�� �ε��� ���� ���� �ʹٸ�, ������� begin() ���� ������ 
				int index1 = find(adj_list[u].begin(), adj_list[u].end(), v) - adj_list[u].begin();
				int index2 = find(adj_list[v].begin(), adj_list[v].end(), u) - adj_list[v].begin();

				adj_list[u].erase(adj_list[u].begin() + index1);   // ����
				adj_list[v].erase(adj_list[v].begin() + index2);
			}
			// �������� �ʴ´ٸ�
			else
			{
				cout << "None" << endl;
			}
		}
		else if (a == "SumAdjacentNode")
		{
			int v;
			cin >> v;
			int sum = 0;
			int check = 0;

			if (adj_list[v].size() == 0)  // ���� v �� ����� ������ �������� �ʴ� ���
			{
				cout << "None" << endl;
				check = 1;
			}

			if (check == 0)
			{
				for (int i = 0; i < adj_list[v].size(); i++)
				{
					sum += adj_list[v][i];
				}
				cout << sum << endl;
			}
		}
	}
}