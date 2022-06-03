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

		vector<int> adj_list[201];
		bool visited[201];
		int max_list[201];  
		
		fill(visited + 1, visited + n + 1, false);

		for (int i = 0; i < 201; i++)
			max_list[i] = -1;

		while (m--)
		{
			int u, v;
			cin >> u >> v;
			adj_list[u].push_back(v);
			adj_list[v].push_back(u);
		}

		// BFS
		for (int i = n; i >= 1 ; i--)  // �ּڰ� ���Ҷ��� �ٸ��� <=> for���� �Ųٷ� ��������!  
		{                              // �Ųٷ� �������� �ش� ������, �����ִ� connected ������Ʈ���� �ڱⰡ �ִ��� �ǰ� �� connected ������Ʈ�� �ٸ� �����鿡�� �ڽ��� ���� �ִ��� ���İ� �ȴ�
			if (visited[i]) 
				continue;  

			queue<int> q;
			q.push(i);
			visited[i] = true;

			int max = q.front(); 

			while (!q.empty())
			{
				int cur = q.front();
				q.pop();
				for (auto nxt : adj_list[cur])
				{
					if (visited[nxt])
						continue;
					
					if (max < nxt)
						max = nxt;
					q.push(nxt);
					visited[nxt] = true;
					
					max_list[nxt] = max;
				}
				max_list[i] = max; 
			}
		}

		while (question--)
		{
			int ans;
			cin >> ans;
			cout << max_list[ans] << endl;
		}
	}
}