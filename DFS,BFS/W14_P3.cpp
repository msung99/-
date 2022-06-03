#include <iostream>
#include <queue>
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

		// BFS  <=> DFS ���� "ť" �� Ȱ���ϸ� ��!
		int count = 1; //  Ȧ���϶��� ����ϵ��� ī�����ϴ� ����
		queue<int> q; // BFS �������� �������� 1 ����
		q.push(1);
		while (!q.empty())
		{
			int cur = q.front();
			q.pop();

			if (visited[cur])
				continue;

			visited[cur] = true;  // �湮ó��

			if (count % 2 == 1)
				cout << cur << ' ';
			for (auto nxt : adj_list[cur]) // ���� �����ִ� ������ ������ ��� �����鿡 ���� Ȯ��
			{
				if (visited[nxt]) // �̹� �湮�� �����̶�� ��ŵ
					continue;
				q.push(nxt); // ó�� �湮�ϴ� �����̶�� ť�� push
			}
			count++;
		}
		cout << endl;
	}
}