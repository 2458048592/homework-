#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<fstream>
#include<iostream>
using namespace std;
struct vellager
{
	int other[105], s;
} vec[105];
bool endpointer[105];
bool can[105];
bool use[105];
int m, n, send;
void flag(int x, int tot)
{
	if (x > n)
	{
		if (tot > send)
		{
			send = tot;
			memcpy(endpointer, use, n + 1);
		}
		return;
	}
	if (!can[x] && !use[x])
	{
		use[x] = true;
		bool now[105];
		memcpy(now, can, n + 1);
		for (int j = 0; j < vec[x].s; j++)
			can[vec[x].other[j]] = true;
		flag(x + 1, tot + 1);
		use[x] = false;
		memcpy(can, now, n + 1);
	}
	flag(x + 1, tot);
}
int main()
{
	
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	infile >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int x, y; 
		infile >> x >> y;
		if (!vec[x].other[0]) vec[x].s = 0;
		if (!vec[y].other[0]) vec[y].s = 0;
		vec[x].other[vec[x].s++] = y;
		vec[y].other[vec[y].s++] = x;
	}
	flag(1, 0);
	outfile << send << endl;
	for (int i = 1; i <= n; i++)
	{
		if(i-1)
			outfile <<" "<< endpointer[i];
		else
			outfile << endpointer[i];
	}
	infile.close();
	outfile.close();
	return 0;
}