#include <iostream>
using namespace std;

int main() {
	int size, n;

	cin >> size >> n;

	int** arr = new int* [size] {};

	for (int i = 0; i < size; i++) {
		arr[i] = new int[size] {};
	}

	int x, y;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cin >> x;
			arr[i][j] = x;
		}
	}


	for (int i = 0; i < n; i++) {
		int index2 = 0;
		int index3 = 0;
		int size2 = 0;
		int size3 = 0;
		cin >> x >> y;
		int* arr2 = new int[size] {}; // ���� ģ���� �����ϴ� �迭
		int* arr3 = new int[size] {};  // ģ���� ģ���� �����ϴ� �迭
		for (int j = 0; j < size; j++) {
			if (arr[x - 1][j] == 1) {
				arr2[index2] = j;
				size2++;
				index2++;
			}
		}

		// 1�� ã����� �ش� �� ��ǥ�� ������ ���� �迭 arr2 �� ���ؼ� �� Ž���� �����ؼ�, �� �ȿ��� 1�� ã�� �� �� ��ǥ�� arr3 �迭�� ��Ƴ���.
		// ����1 : ģ���� ��(arr2) ���� �ڱ� �ڽ�(x-1)�� ã���� �������ִ� ��
		// ����2 : ����ģ��(arr2[j])�� ģ��(arr[j][k])�� ã�Ƴ�
		// ���� 3 : ����2�� ���� ã�Ƴ� ģ���� ģ���� �ڽ��� ģ���̰ų� ������ ������� �������ִ� �� ( 0�� �ƹ��� ���谡 ���ٴ� ���̱� ����. 1�� ���� ģ���� ���̰�, 2�� ���� ������ ����̴�.)
		for (int j = 0; j < size2; j++) {
			for (int k = 0; k < size; k++) {
				if (k != x - 1 && arr[arr2[j]][k] == y + 1 && arr[x - 1][k] == 0) {
					bool flag = true; // arr3 �迭�� ������ ģ���� ģ���� �ߺ��ؼ� �� �����ϴ� ��Ȳ�� �����ϱ� ���� 
					for (int t = 0; t < size3; t++) {
						if (arr3[t] == k + 1)  // ã�Ƴ� ģ���� ģ���� �̹� arr3 �迭�� ������ִ� ���
							flag = false;
					}
					// arr3 �迭�� �� Ž���غôµ�, ã�Ƴ� ģ���� ģ���� arr3 �� ��� �����ص� ������ ����� �����Ѵ�.
					if (flag) {
						arr3[index3] = k + 1;
						size3++;
						index3++;
					}

				}
			}
		}
		// arr3 ���� ���������� ģ���� ģ���� �༮�� ��ȣ�� ���δ�. �̶� �������� ����� ���� sorting ������ �����Ѵ�.
		for (int j = 0; j < size3 - 1; j++) {
			for (int k = j + 1; k < size3; k++) {
				if (arr3[j] > arr3[k]) {
					int temp = arr3[j];
					arr3[j] = arr3[k];
					arr3[k] = temp;
				}
			}
		}
		if (size3 == 0)
			cout << 0 << endl;
		else {
			for (int j = 0; j < size3; j++) {
				cout << arr3[j] << " ";
			}
			cout << endl;
		}
	}


}