#include<iostream>
#include<fstream>
using namespace std;

//���ʱ����
class Node
{
public:
	int data;//ʱ��ֵ
	bool flag;//�ж��ǿ�ʼ���ǽ�����0��ʾ��ʼ��1��ʾ����
	bool operator<(Node &secondRational);//��ʱ��ֵ�Ƚ���������Ĵ�С
};

//�Ƚ�����ʱ��ֵ�Ĵ�С
bool Node::operator<(Node &secondRational)
{
	if ((this->data - secondRational.data)<0)
		return true;
	else
		return false;
}

//�������麯��
template<typename T>
void arraycopy(T source[], int sourceStartIndex, T target[], int targetStartIndex, int length);
//�ϲ����麯��
template<typename T>
void merge(T list1[], int list1Size, T list2[], int list2Size, T temp[]);
//�鲢������
template<typename T>
void mergeSort(T list[], int arraySize)
{
	if (arraySize>1)
	{
		//��������ǰ�벿������
		T *firstHalf = new T[arraySize / 2];
		arraycopy(list, 0, firstHalf, 0, arraySize / 2);
		mergeSort(firstHalf, arraySize / 2);

		//���������벿������
		int secondHalfLength = arraySize - arraySize / 2;
		T *secondHalf = new T[secondHalfLength];
		arraycopy(list, arraySize / 2, secondHalf, 0, secondHalfLength);
		mergeSort(secondHalf, secondHalfLength);

		//�ϲ���������������
		T *temp = new T[arraySize];
		merge(firstHalf, arraySize / 2, secondHalf, secondHalfLength, temp);
		arraycopy(temp, 0, list, 0, arraySize);

		delete[]temp;
		delete[]firstHalf;
		delete[]secondHalf;
	}
}

//���������鰴��С˳��ϲ���һ��������
template<typename T>
void merge(T list1[], int list1Size, T list2[], int list2Size, T temp[])
{
	int current1 = 0;
	int current2 = 0;
	int current3 = 0;

	while (current1<list1Size&&current2<list2Size)
	{
		if (list1[current1]<list2[current2])
			temp[current3++] = list1[current1++];
		else
			temp[current3++] = list2[current2++];
	}

	while (current1<list1Size)
		temp[current3++] = list1[current1++];
	while (current2<list2Size)
		temp[current3++] = list2[current2++];
}

//��һ�����鸴�Ƶ���һ��������
template<typename T>
void arraycopy(T source[], int sourceStartIndex, T target[], int targetStartIndex, int length)
{
	for (int i = 0; i<length; i++)
	{
		target[i + targetStartIndex] = source[i + sourceStartIndex];
	}
}

//���ٻ᳡������
int Greedyplan(Node f[], int n)
{
	int Count = 0;
	int maxCount = 0;
	/*
	�����ʱ�䣬����ʱ��Ϊ��ʼʱ�䣬��Count+1,Ϊ����ʱ�䣬��Count-1
	ͳ�Ƶó�����Countֵ������Countֵ����maxCount��
	��maxCountֵ��Ϊ���ٵĻ᳡��
	*/
	for (int i = 0; i<n; i++)
	{
		if (f[i].flag == 0)//����ʱ��Ϊ��ʼʱ��Count+1
		{
			Count++;
			if (Count>maxCount)//��¼��ѭ��������Countֵ
			{
				maxCount = Count;
			}
		}
		else//��Ϊ����ʱ��Count-1
		{
			Count--;
		}
	}
	return maxCount;
}

int main()
{
	//���������ļ��е�����
	fstream fin;
	fin.open("input.txt", ios::in);
	int n;
	fin >> n;
	//��������Node���͵����飬���ڴ�ſ�ʼʱ��ͽ���ʱ��
	Node *a = new Node[n];
	Node *b = new Node[n];
	for (int i = 0; i<n; i++)
	{
		fin >> a[i].data;
		fin >> b[i].data;
	}

	//����ʼʱ���ʾΪ0
	for (int j = 0; j<n; j++)
	{
		a[j].flag = 0;
	}
	//������ʱ���ʾΪ1
	for (int k = 0; k<n; k++)
	{
		b[k].flag = 1;
	}

	//�ٽ���һ��Node���͵����飬��ǰ���������е����ݸ��Ƶ���������
	Node *c = new Node[2 * n];
	arraycopy(a, 0, c, 0, n);
	arraycopy(b, 0, c, n, n);

	//������c��ʱ��ֵ��С���򣬴�����Ϊ�ȶ��Ĺ鲢����
	mergeSort(c, 2 * n);

	//�������ٻ᳡������
	int mm = Greedyplan(c, 2 * n);
	//����̨���
	//���������д�뵽����ļ�
	fstream fout;
	fout.open("output.txt", ios::out);
	fout << mm;
	fin.close();
	fout.close();
	system("pause");
	return 0;
}