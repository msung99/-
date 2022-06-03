#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;


int main(void)
{
	int testCase;
	cin >> testCase;
	while (testCase--)
	{
		int n, m;
		cin >> n >> m;

		vector<int> adj_list[1000];  // �������� ����� ����!!! 100 ���� �����ϸ� ��������� �Ѥ� 
		bool visited[1000];
		fill(visited + 1, visited + n + 1, false);

		while (m--)
		{
			int u, v;
			cin >> u >> v;
			adj_list[u].push_back(v);
			adj_list[v].push_back(u);
		}

		// DFS
		int count = 1; //  Ȧ���϶��� ����ϵ��� ī�����ϴ� ����
		stack<int> s; // DFS �������� �������� 1 ����
		s.push(1);
		while (!s.empty())
		{
			int cur = s.top();
			s.pop();
			
			if (visited[cur])
				continue;
			
			visited[cur] = true;  // �湮ó��

			if (count % 2 == 1)
				cout << cur << ' ';
			for (int i = 0; i < adj_list[cur].size(); i++)
			{
				// ������ Ư���� �������� �־���� ���� ������ ������ ��ܿ� ��ġ�ϰ� �Ǽ�, ���� ������ ���� �湮�ϰ� ��
				int nxt = adj_list[cur][adj_list[cur].size() - 1 - i];
				if (visited[nxt])  // �̹� �湮�� �����̶�� ��ŵ
					continue;
				s.push(nxt);
			}
			count++;
		}
		cout << endl;
	}
}
