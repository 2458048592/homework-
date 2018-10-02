#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
const int MAX = 50;
int board[MAX][MAX];  //��¼���񱻼������
int root[MAX][MAX];      //��¼������λ��
int best[MAX][MAX];
int m, n;             //����Ϊ m * n
int k = 0;                //�����˸���
int bestk = 10000;
int t = 0;            //�����ӵķ������
int t1, t2, more;
int dx[] = { 0, 1, -1, 0, 0 }; //ԭλ�ü��ĸ�����
int dy[] = { 0, 0, 0,  1, -1 };

void change(int i, int j)
{
	root[i][j] = 1;  //���û�����
	k++;
	for (int d = 0; d <= 4; d++)     //ԭλ�ü���Χ������
	{
		int p = i + dx[d];
		int q = j + dy[d];
		board[p][q]++;
		if (board[p][q] == 1)
			t++;
	}
}

//�ָ�������ǰ��״̬
void restore(int i, int j)
{
	root[i][j] = 0;
	k--;
	for (int d = 0; d <= 4; d++)
	{
		int p = i + dx[d];
		int q = j + dy[d];
		board[p][q]--;
		if (board[p][q] == 0)
			t++;
	}
}

void backtrack(int i, int j)
{
	do  //�ҵ�δ�����ӵķ���
	{
		j++;
		if (j > n)
		{
			i++;
			j = 1;
		}
	} while (board[i][j] != 0 && i <= n);

	if (i>n)  //����Ҷ��㣬�������Ž�
	{
		if (k < bestk)
		{
			bestk = k;
			for (int i = 1; i <= m; i++)
				for (int j = 1; j <= n; j++)
					best[i][j] = root[i][j];
		}
	}
	if (k + (t1 - t) / 5 >= bestk)  //��֦
		return;
	if (i< n - 1 && (k + (t2 - t) / 5 >= bestk))  //��֦
		return;
	if (i<n)
	{
		change(i + 1, j);  //���û����ˣ����ı�״̬
		backtrack(i, j);
		restore(i + 1, j); //���������ˣ����ָ�״̬
	}
	if (j<m && (board[i][j + 1] == 0 || board[i][j + 2] == 0))
	{
		change(i, j + 1);
		backtrack(i, j);
		restore(i, j + 1);
	}
	if (board[i + 1][j] == 0 && board[i][j + 1] == 0)
	{
		change(i, j);
		backtrack(i, j);
		restore(i, j);
	}
}

void compute()
{
	more = m / 4 + 1;
	if (m % 4 == 3)
		more++;
	else if (m % 4 == 2)
		more += 2;
	t2 = m * n + more + 4;
	t1 = m * n + 4;
	memset(board, 0, sizeof(board));
	memset(root, 0, sizeof(root));
	for (int i = 0; i <= n + 1; i++)      //�����һȦΪ1
	{
		board[i][m + 1] = 1;
		board[i][0] = 1;
	}
	
	for (int i = 0; i <= m + 1; i++)
	{
		board[n + 1][i] = 1;
		board[n + 1][0] = 1;
	}

	if (n == 1 && m == 1)
		cout << 1 << endl;
	else
		backtrack(1, 0);
}

int main()
{
	ifstream fin("input.txt");
	fin >> m;
	fin >> n;
	ofstream fout("output.txt");
	compute();

	fout << bestk << endl;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			fout << best[i][j] << " ";
		fout << endl;
	}
	fout << endl;
	fin.close();
	fout.close();
	return 0;
}