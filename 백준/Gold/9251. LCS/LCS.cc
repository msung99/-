#include <bits/stdc++.h>
using namespace std;

int d[1005][1005];
/*
d[i][j] = a의 i-1번쨰 글자와 b의 j-1번쨰 글자까지 최장 공통 부분수열
최장 공통 부분수열을 보존하기 위해 2중 for문을 사용
d[i][j] => if(a[i-1] == b[j-1]) 이면 d[i-1][j-1] + 1
d[i][j] => if(a[i-1] != b[j-1]) 이면 max(d[i-1][1], d[i][j-1])
초기값은 d[1][1] 에 있고 a[0] 과 b[0] 가 같을 떄와 a[0] 와 b[0] 가 다를때 각각 다른 값을 저장
*/

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	string a, b;
	cin >> a >> b;
	int len_a = a.length();
	int len_b = b.length();

	for (int i = 1; i <= len_a; i++) {
		for (int j = 1; j <= len_b; j++) {
			if (a[i - 1] == b[j - 1])
				d[i][j] = d[i - 1][j - 1] + 1;
			else
				d[i][j] = max(d[i - 1][j], d[i][j - 1]);
		}
	}
	cout << d[len_a][len_b];
}