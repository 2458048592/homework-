#include<iostream>
#include<fstream>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int n, c, a[10000], b[10000], d[10000], i, sum = 0;
bool pd;

void print(int dep, ofstream *outfile)
{
	int j;
	for (j = 1; j <= dep; ++j)
		(*outfile) <<d[j]<<" ";
	(*outfile) << endl;
	return;
}

void dfs(int dep, ofstream *outfile)
{
	int r;
	if (pd == 1) return;
	for (r = 1; r <= n; ++r)
		if (!b[r] && c - a[r] >= 0)
		{
			if (pd == 1) return;
			c -= a[r];
			d[dep] = a[r];//d是记录数组
			b[r] = 1;
			if (c == 0) //如果找到一组解，直接输出，完成任务
			{
				if (pd == 0)
					print(dep, outfile);
				pd = 1;
				return;
			}
			else dfs(dep + 1, outfile);
			if (pd == 1) return;
			c += a[r];//回溯一步
			b[r] = 0;
		}
}

int main()
{
	ifstream infile;
	infile.open("input.txt", ios::in);
	infile >> n >> c;//初始化集合元素个数n和目标值c 
	ofstream outfile;
	outfile.open("output.txt", ios::out);
	for (i = 1; i <= n; ++i)
	{
		infile>>a[i];
		sum += a[i];
	}
	if (sum<c)
	{
		outfile << "No solution!" << endl;;
		return 0;
	}
	memset(d, 0, sizeof(d));
	memset(b, 0, sizeof(b));
	pd = 0;
	dfs(1,&outfile);
	if (!pd) outfile << "No solution!" << endl;
	outfile.close();
	infile.close();
	return 0;
}
