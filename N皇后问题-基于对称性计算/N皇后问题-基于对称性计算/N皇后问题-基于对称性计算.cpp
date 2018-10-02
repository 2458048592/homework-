#include <iostream>
#include <malloc.h>
#include <cstdio>
#include <cmath>
using namespace std;
const int MaxSize = 400;

typedef struct linknode//˳��ջ
{
	int data[MaxSize];
	int top;
} SqStack;
SqStack *st;

void initStack(SqStack *&s)//��ʼ��
{
	s = (SqStack *)malloc(sizeof(SqStack));
	s->top = -1;
}

bool Push(SqStack *&s, int e)//ѹ��ջ
{
	if (s->top == MaxSize - 1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool Pop(SqStack *&s)//�Ƴ�ջ��Ԫ��
{
	if (s->top == -1)
		return false;
	s->top--;
	return true;
}

bool GetTop(SqStack *s, int &e)//ȡջ��Ԫ��
{
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}

bool StackEmpty(SqStack *s)//�ж�ջ�Ƿ�Ϊ��
{
	return(s->top == -1);
}

void DestroyStack(SqStack *&s)//����ջ
{
	free(s);
}

bool Check(int *qu, int t)//�ܷŷ����棬����Ϊ��
{
	int i;
	for (i = 0; i<t; i++)//�����ж�
		if (qu[i] == qu[t] || abs(t - i) == abs(qu[t] - qu[i]))//��ͬһ�л�Խ���
			return false;
	return true;
}

void Show(int *qu, int len, int Count)
{
	int i;
	cout << "��" << ++Count << "���⣺";
	for (i = 0; i<len; i++)//i������
		cout << "(" << i << ", " << qu[i] << ") ";
	cout << endl;
}

int main()
{
	initStack(st);//��ʼ��
	cout << "�ʺ����⣨n<20�� n=";
	int n;
	cin >> n;//����ʺ���Ŀ
	cout << n << "�ʺ�����������£�" << endl;
	int cnt = 0, row = 0;//����Ľ����Ŀ����
	int *queen = new int[n];//���ٶ�̬���鱣��ÿ�лʺ����λ��
	queen[0] = -1;//�ʼ����Ԫ����Ϊ-1
	Push(st, 0);//����λ��ѹ��ջ
	while (!StackEmpty(st))//ջ�ǿ�
	{
		GetTop(st, row);//row�ǵ�ǰջ��Ԫ��ֵ
		queen[row]++;//������һ��
		if (queen[row] >= n)//��ǰ�е�����n�ж��Ѿ����Թ������ǻʺ�û�аڷųɹ�
			Pop(st);//ջ��Ԫ�س�ջ���൱�ڻ��ݵ���һ��
		else
		{
			if (Check(queen, row))//��飬������ڸ�λ�÷Żʺ�
			{
				if (row == n - 1)//��̽����n��
				{
					Show(queen, n, cnt);//����ʺ�λ��
					cnt++;//�ⷨ��һ
				}
				else//����Ҫ��̽
				{
					queen[row + 1] = -1;//���-1
					Push(st, row + 1);//�ʺ��λ��ѹ��ջ
				}
			}
		}
	}
	delete[]queen;//�ͷŶ�̬����
	free(st);//����ջ
	return 0;
}
