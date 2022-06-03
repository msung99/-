#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;


int main(void)
{
	int testCase;
	cin >> testCase;
	while (testCase--)
	{
		int n, m, question;
		cin >> n >> m >> question;

		vector<int> adj_list[1000];
		bool visited[1000];
		int min_list[1000];  // �ּڰ� ����Ʈ

		// �ʱ�ȭ �۾� (�ʱ� ����)
		fill(visited + 1, visited + n + 1, false);

		for (int i = 0; i < 100; i++)
			min_list[i] = 0;

		while (m--)
		{
			int u, v;
			cin >> u >> v;
			adj_list[u].push_back(v);
			adj_list[v].push_back(u);
		}

		// BFS 

		for (int i = 1; i <= n; i++)
		{

			if (visited[i])
				continue;

			queue<int> q;
			q.push(i);
			visited[i] = true;

			int min = q.front();  // �� conncted ������Ʈ�� �ּڰ�

			// while�� �� ������ ���� BFS�� ���� ���������� ����� �������� �� �湮ó���� �Ǿ��� ���̴�.
			// ��, ���������� �����ִ� �ش� conncted ������Ʈ�� ��� �湮ó�� �ȴ�! 
			while (!q.empty())
			{
				int cur = q.front();
				q.pop();
				for (auto nxt : adj_list[cur])
				{
					if (visited[nxt])
						continue;
					// ���� ������ ������ �������� ���� �ּڰ��� �ɼ� �ִ����� Ȯ��
					if (min > nxt)
						min = nxt;
					q.push(nxt);
					visited[nxt] = true;

					min_list[nxt] = min; // // �ּڰ� ����Ʈ�� �� ������ �����ϰ� �ִ� �ּڰ����� �ֽ�ȭ
				}
				min_list[i] = min; // �ּڰ� ����Ʈ���� ������ �����鿡 ���ؼ� �ּڰ��� �ֽ�ȭ ������, �ڽŵ� �ֽ�ȭ ������
			}
		}

		// for (int i = 0; i < 20; i++)
		//	cout << i << ":" << min_list[i] << endl;

		// ���� ����
		while (question--)
		{
			int ans;
			cin >> ans;
			cout << min_list[ans] << endl;
		}
	}
}