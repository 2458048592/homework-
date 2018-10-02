#include<iostream>
#include<fstream>
using namespace std;

//活动的时间类
class Node
{
public:
	int data;//时间值
	bool flag;//判断是开始还是结束，0表示开始，1表示结束
	bool operator<(Node &secondRational);//按时间值比较两个对象的大小
};

//比较类中时间值的大小
bool Node::operator<(Node &secondRational)
{
	if ((this->data - secondRational.data)<0)
		return true;
	else
		return false;
}

//复制数组函数
template<typename T>
void arraycopy(T source[], int sourceStartIndex, T target[], int targetStartIndex, int length);
//合并数组函数
template<typename T>
void merge(T list1[], int list1Size, T list2[], int list2Size, T temp[]);
//归并排序函数
template<typename T>
void mergeSort(T list[], int arraySize)
{
	if (arraySize>1)
	{
		//复制排序前半部分数组
		T *firstHalf = new T[arraySize / 2];
		arraycopy(list, 0, firstHalf, 0, arraySize / 2);
		mergeSort(firstHalf, arraySize / 2);

		//复制排序后半部分数组
		int secondHalfLength = arraySize - arraySize / 2;
		T *secondHalf = new T[secondHalfLength];
		arraycopy(list, arraySize / 2, secondHalf, 0, secondHalfLength);
		mergeSort(secondHalf, secondHalfLength);

		//合并复制两部分数组
		T *temp = new T[arraySize];
		merge(firstHalf, arraySize / 2, secondHalf, secondHalfLength, temp);
		arraycopy(temp, 0, list, 0, arraySize);

		delete[]temp;
		delete[]firstHalf;
		delete[]secondHalf;
	}
}

//将两个数组按大小顺序合并入一个数组中
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

//将一个数组复制到另一个数组中
template<typename T>
void arraycopy(T source[], int sourceStartIndex, T target[], int targetStartIndex, int length)
{
	for (int i = 0; i<length; i++)
	{
		target[i + targetStartIndex] = source[i + sourceStartIndex];
	}
}

//最少会场数函数
int Greedyplan(Node f[], int n)
{
	int Count = 0;
	int maxCount = 0;
	/*
	遍历活动时间，若此时间为开始时间，则Count+1,为结束时间，则Count-1
	统计得出最大的Count值，并将Count值赋给maxCount，
	此maxCount值就为最少的会场数
	*/
	for (int i = 0; i<n; i++)
	{
		if (f[i].flag == 0)//若此时间为开始时间Count+1
		{
			Count++;
			if (Count>maxCount)//记录次循环中最大的Count值
			{
				maxCount = Count;
			}
		}
		else//若为结束时间Count-1
		{
			Count--;
		}
	}
	return maxCount;
}

int main()
{
	//读出输入文件中的数据
	fstream fin;
	fin.open("input.txt", ios::in);
	int n;
	fin >> n;
	//建立两个Node类型的数组，用于存放开始时间和结束时间
	Node *a = new Node[n];
	Node *b = new Node[n];
	for (int i = 0; i<n; i++)
	{
		fin >> a[i].data;
		fin >> b[i].data;
	}

	//将开始时间表示为0
	for (int j = 0; j<n; j++)
	{
		a[j].flag = 0;
	}
	//将结束时间表示为1
	for (int k = 0; k<n; k++)
	{
		b[k].flag = 1;
	}

	//再建立一个Node类型的数组，将前两个数组中的数据复制到此数组中
	Node *c = new Node[2 * n];
	arraycopy(a, 0, c, 0, n);
	arraycopy(b, 0, c, n, n);

	//将数组c按时间值大小排序，此排序为稳定的归并排序
	mergeSort(c, 2 * n);

	//调用最少会场数函数
	int mm = Greedyplan(c, 2 * n);
	//控制台输出
	//将结果数据写入到输出文件
	fstream fout;
	fout.open("output.txt", ios::out);
	fout << mm;
	fin.close();
	fout.close();
	system("pause");
	return 0;
}