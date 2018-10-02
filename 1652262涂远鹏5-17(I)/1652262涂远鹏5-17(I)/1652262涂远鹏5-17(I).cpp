#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
const int MAX = 50;
int board[MAX][MAX];  //记录方格被监视情况
int root[MAX][MAX];      //记录机器人位置
int best[MAX][MAX];
int m, n;             //矩阵为 m * n
int k = 0;                //机器人个数
int bestk = 10000;
int t = 0;            //被监视的方格个数
int t1, t2, more;
int dx[] = { 0, 1, -1, 0, 0 }; //原位置及四个方向
int dy[] = { 0, 0, 0,  1, -1 };

void change(int i, int j)
{
	root[i][j] = 1;  //放置机器人
	k++;
	for (int d = 0; d <= 4; d++)     //原位置及周围被监视
	{
		int p = i + dx[d];
		int q = j + dy[d];
		board[p][q]++;
		if (board[p][q] == 1)
			t++;
	}
}

//恢复被监视前的状态
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
	do  //找到未被监视的方格
	{
		j++;
		if (j > n)
		{
			i++;
			j = 1;
		}
	} while (board[i][j] != 0 && i <= n);

	if (i>n)  //到达叶结点，复制最优解
	{
		if (k < bestk)
		{
			bestk = k;
			for (int i = 1; i <= m; i++)
				for (int j = 1; j <= n; j++)
					best[i][j] = root[i][j];
		}
	}
	if (k + (t1 - t) / 5 >= bestk)  //剪枝
		return;
	if (i< n - 1 && (k + (t2 - t) / 5 >= bestk))  //剪枝
		return;
	if (i<n)
	{
		change(i + 1, j);  //放置机器人，并改变状态
		backtrack(i, j);
		restore(i + 1, j); //撤销机器人，并恢复状态
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
	for (int i = 0; i <= n + 1; i++)      //最外层一圈为1
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