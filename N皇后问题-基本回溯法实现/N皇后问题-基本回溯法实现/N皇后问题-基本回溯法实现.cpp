#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;
static int n, x[1000];
static long sum;
void OutPut()
{
	for (int i = 1; i <= n; ++i)
		cout<<"("<<i<<","<<x[i]<<") ";
	cout << endl;
}

int Place(int k)
{
	for (int j = 1; j < k; ++j)
		if (abs(k - j) == abs(x[k] - x[j]) || x[j] == x[k])
			return 0;
	return 1;
}

void BackTrack1(int t)
{
	if (t > n)
	{
		sum++;
		OutPut();
	}
	else
	{
		for (int i = 1; i <= n; ++i)
		{
			x[t] = i;
			if (Place(t))
				BackTrack1(t + 1);
		}
	}
}

void BackTrack()
{
	int k=1;
	x[1] = 0;
	while (k >= 1)
	{
		x[k] += 1;
		while ((x[k] <= n) && !(Place(k)))
			x[k] += 1;
		if (x[k] <= n)
		{
			if (k == n)
			{
				sum++;
				OutPut();
			}
			else
			{
				k++;
				x[k] = 0;
			}
		}   
		else
			k--;
	}
}

int main()
{
	//ifstream fin("input.txt");
	//ofstream fout("output.txt");
	int nn;
	cout << "请输入皇后数目：" << endl;
	cin>> nn;
	//fin >> nn;
	n = nn;
	sum = 0;
	cout <<nn<< "个皇后的排列可以为(一行坐标表示一种排列方法)：" << endl;
	for (int i = 0; i <= n; ++i)
		x[i] = 0;
	BackTrack();
	cout <<nn << "个皇后的排列方法数为："<<sum;
	//fout<<sum;
	return 0;
}
