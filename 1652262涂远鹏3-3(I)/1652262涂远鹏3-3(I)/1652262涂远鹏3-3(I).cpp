#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define  MAXN 100
int sum[MAXN];
int mins[MAXN][MAXN], maxs[MAXN][MAXN];
int n, stone[MAXN];

int sums(int i, int j) {
	if (i + j >= n) {
		return sums(i, n - i - 1) + sums(0, (i + j) % n);
	}
	else {
		return sum[i + j] - (i > 0 ? sum[i - 1] : 0);
	}
}

void getBest(int& minnum, int& maxnum) {
	//初始化，没有合并，花费为0
	for (int i = 0; i < n; ++i) {
		mins[i][0] = maxs[i][0] = 0;
	}
	//还需进行合并次数
	for (int j = 1; j < n; ++j) {
		for (int i = 0; i < n; ++i) {
			mins[i][j] = INT_MAX;
			maxs[i][j] = 0;
			for (int k = 0; k < j; ++k) {
				mins[i][j] = min(mins[i][k] + mins[(i + k + 1) % n][j - k - 1] + sums(i, j), mins[i][j]);
				maxs[i][j] = max(maxs[i][k] + maxs[(i + k + 1) % n][j - k - 1] + sums(i, j), maxs[i][j]);

			}
		}
	}
	minnum = mins[0][n - 1];
	maxnum = maxs[0][n - 1];
	for (int i = 0; i < n; ++i) {
		minnum = min(minnum, mins[i][n - 1]);
		maxnum = max(maxnum, maxs[i][n - 1]);
	}

}

int main() {
	FILE *inputfile, *outputfile;
	inputfile = fopen("input.txt", "r");
	outputfile = fopen("output.txt", "w");
	fscanf(inputfile,"%d", &n);
	for (int i = 0; i < n; ++i)
		fscanf(inputfile,"%d", &stone[i]);

	sum[0] = stone[0];
	for (int i = 1; i < n; ++i) {
		sum[i] = sum[i - 1] + stone[i];
	}
	int minnum, maxnum;
	getBest(minnum, maxnum);
	fprintf(outputfile,"%d\n%d", minnum, maxnum);
	return 0;
}