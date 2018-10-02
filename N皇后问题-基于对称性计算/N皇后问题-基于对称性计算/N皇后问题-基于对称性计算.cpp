#include <iostream>
#include <malloc.h>
#include <cstdio>
#include <cmath>
using namespace std;
const int MaxSize = 400;

typedef struct linknode//顺序栈
{
	int data[MaxSize];
	int top;
} SqStack;
SqStack *st;

void initStack(SqStack *&s)//初始化
{
	s = (SqStack *)malloc(sizeof(SqStack));
	s->top = -1;
}

bool Push(SqStack *&s, int e)//压入栈
{
	if (s->top == MaxSize - 1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool Pop(SqStack *&s)//移除栈顶元素
{
	if (s->top == -1)
		return false;
	s->top--;
	return true;
}

bool GetTop(SqStack *s, int &e)//取栈顶元素
{
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}

bool StackEmpty(SqStack *s)//判断栈是否为空
{
	return(s->top == -1);
}

void DestroyStack(SqStack *&s)//销毁栈
{
	free(s);
}

bool Check(int *qu, int t)//能放返回真，否则为假
{
	int i;
	for (i = 0; i<t; i++)//逐行判断
		if (qu[i] == qu[t] || abs(t - i) == abs(qu[t] - qu[i]))//在同一列或对角线
			return false;
	return true;
}

void Show(int *qu, int len, int Count)
{
	int i;
	cout << "第" << ++Count << "个解：";
	for (i = 0; i<len; i++)//i是行数
		cout << "(" << i << ", " << qu[i] << ") ";
	cout << endl;
}

int main()
{
	initStack(st);//初始化
	cout << "皇后问题（n<20） n=";
	int n;
	cin >> n;//输入皇后数目
	cout << n << "皇后问题求解如下：" << endl;
	int cnt = 0, row = 0;//问题的解的数目、行
	int *queen = new int[n];//开辟动态数组保存每行皇后的列位置
	queen[0] = -1;//最开始把首元素置为-1
	Push(st, 0);//把首位置压入栈
	while (!StackEmpty(st))//栈非空
	{
		GetTop(st, row);//row是当前栈顶元素值
		queen[row]++;//尝试下一列
		if (queen[row] >= n)//当前行的所有n列都已经尝试过，但是皇后没有摆放成功
			Pop(st);//栈顶元素出栈，相当于回溯到上一行
		else
		{
			if (Check(queen, row))//检查，如果能在该位置放皇后
			{
				if (row == n - 1)//试探到第n行
				{
					Show(queen, n, cnt);//输出皇后位置
					cnt++;//解法加一
				}
				else//仍需要试探
				{
					queen[row + 1] = -1;//标记-1
					Push(st, row + 1);//皇后的位置压入栈
				}
			}
		}
	}
	delete[]queen;//释放动态数组
	free(st);//销毁栈
	return 0;
}
