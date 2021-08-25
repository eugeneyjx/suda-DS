#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

bool cmp(int a, int b)
{

	return a > b;

}

void getList(int n)
{
	int list[10000];
	for (int i = 0; i < n; i++)
	{
		list[i] = rand() % 10000;
	}
	ofstream fout1("unordered_list.txt");
	for (int i = 0; i < n; i++)
	{
		stringstream ss;
		string temp;
		ss << list[i];
		ss >> temp;
		fout1 << temp << endl;
	}
	sort(list, list + n);
	ofstream fout2("ascending_list.txt");
	for (int i = 0; i < n; i++)
	{
		stringstream ss;
		string temp;
		ss << list[i];
		ss >> temp;
		fout2 << temp << endl;
	}
	sort(list, list + n, cmp);
	ofstream fout3("descending_list.txt");
	for (int i = 0; i < n; i++)
	{
		stringstream ss;
		string temp;
		ss << list[i];
		ss >> temp;
		fout3 << temp << endl;
	}
}

void print(int a[],int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void InsertSort(string fname, int n)
{
	
	ifstream fin(fname);
	int a[10000];
	while (fin.eof() == false)
	{
		for (int i = 0; i < n; i++)
		{
			fin >> a[i];
		}
	}
	
	int count_cmp = 0, count_move = 0;
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	for (int i = 1; i<n; i++) 
	{
		if (a[i] < a[i - 1])
		{               //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入  
			count_cmp++;
			int j = i - 1;
			int x = a[i];        //复制为哨兵，即存储待排序元素  
			a[i] = a[i - 1];           //先后移一个元素  
			count_move++;
			while (x < a[j]) 
			{  //查找在有序表的插入位置  
				count_cmp++;
				a[j + 1] = a[j];
				count_move++;
				j--;         //元素后移  
			}
			a[j + 1] = x;      //插入到正确位置  
		}
		else count_cmp++;
	}
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	cout << "插入排序:" << endl;
	cout << "运行时间:" << total_t << "s" << endl;
	cout << "比较次数:" << count_cmp << endl << "移动次数:" << count_move << endl;
	cout << endl;
}



void ShellInsertSort(int a[], int n, int dk, int &count_cmp, int &count_move)
{
	for (int i = dk; i<n; ++i) 
	{
		count_cmp++;
		if (a[i] < a[i - dk]) 
		{          //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入  
			int j = i - dk;
			int x = a[i];           //复制为哨兵，即存储待排序元素  
			a[i] = a[i - dk];         //首先后移一个元素  
			count_move++;
			while (x < a[j]) 
			{     //查找在有序表的插入位置  
				count_cmp++;
				a[j + dk] = a[j];
				count_move++;
				j -= dk;             //元素后移  
			}
			a[j + dk] = x;            //插入到正确位置  
		}
	}
}
//先按增量d（n/2,n为要排序数的个数进行希尔排序

void ShellSort(string fname, int n) 
{
	ifstream fin(fname);
	int a[10000];
	while (fin.eof() == false)
	{
		for (int i = 0; i < n; i++)
		{
			fin >> a[i];
		}
	}
	
	int count_cmp = 0, count_move = 0;
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	int dk = n / 2;
	while (dk >= 1) 
	{
		ShellInsertSort(a, n, dk, count_cmp, count_move);
		dk = dk / 2;
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	cout << "希尔排序:" << endl;
	cout << "运行时间:" << total_t << "s" << endl;
	cout << "比较次数:" << count_cmp << endl << "移动次数:" << count_move << endl;
	cout << endl;
}


int SelectMinKey(int a[], int n, int i, int &count_cmp, int &count_move)
{
	int k = i;
	for (int j = i + 1; j< n; ++j) 
	{
		if (a[k] > a[j]) k = j;
		count_cmp++;
	}
	return k;
}

void SelectSort(string fname, int n) 
{
	ifstream fin(fname);
	int a[10000];
	while (fin.eof() == false)
	{
		for (int i = 0; i < n; i++)
		{
			fin >> a[i];
		}
	}

	int count_cmp = 0, count_move = 0;
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	int key, tmp;
	for (int i = 0; i< n; ++i) 
	{
		key = SelectMinKey(a, n, i, count_cmp, count_move);           //选择最小的元素  
		count_cmp++;
		if (key != i) 
		{
			tmp = a[i];  a[i] = a[key]; a[key] = tmp;
			count_move++;//最小元素与第i位置元素互换  
		}
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	cout << "选择排序:" << endl;
	cout << "运行时间:" << total_t << "s" << endl;
	cout << "比较次数:" << count_cmp << endl << "移动次数:" << count_move << endl;
	cout << endl;
}





void HeapAdjust(int H[], int s, int length, int &count_cmp, int &count_move)
{
	int tmp = H[s];
	int child = 2 * s + 1; //左孩子结点的位置。(i+1 为当前调整结点的右孩子结点的位置)  
	while (child < length) 
	{
		count_cmp++;
		if (child + 1 <length && H[child]<H[child + 1]) 
		{ 
			// 如果右孩子大于左孩子(找到比当前待调整结点大的孩子结点)  
			++child;
		}
		count_cmp++;
		if (H[s]<H[child]) 
		{  
			// 如果较大的子结点大于父结点  
			count_move++;
			H[s] = H[child]; // 那么把较大的子结点往上移动，替换它的父结点  
			s = child;       // 重新设置s ,即待调整的下一个结点的位置  
			child = 2 * s + 1;
		}
		else 
		{            // 如果当前待调整结点大于它的左右孩子，则不需要调整，直接退出  
			break;
		}
		H[s] = tmp;       // 当前待调整的结点放到比其大的孩子结点位置上 
		count_move++;
	}
}


void BuildingHeap(int H[], int length, int &count_cmp, int &count_move)
{
	//最后一个有孩子的节点的位置 i=  (length -1) / 2  
	for (int i = (length - 1) / 2; i >= 0; --i)
		HeapAdjust(H, i, length, count_cmp, count_move);
}


void HeapSort(string fname, int length)
{
	ifstream fin(fname);
	int H[10000];
	while (fin.eof() == false)
	{
		for (int i = 0; i < length; i++)
		{
			fin >> H[i];
		}
	}

	int count_cmp = 0, count_move = 0;
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	//初始堆  
	BuildingHeap(H, length, count_cmp, count_move);//从最后一个元素开始对序列进行调整  
	for (int i = length - 1; i > 0; --i)
	{
		//交换堆顶元素H[0]和堆中最后一个元素  
		int temp = H[i]; H[i] = H[0]; H[0] = temp;
		count_move++;//每次交换堆顶元素和堆中最后一个元素之后，都要对堆进行调整  
		HeapAdjust(H, 0, i, count_cmp, count_move);
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	cout << "堆排序:" << endl;
	cout << "运行时间:" << total_t << "s" << endl;
	cout << "比较次数:" << count_cmp << endl << "移动次数:" << count_move << endl;
	cout << endl;

}


void BubbleSort(string fname, int n) 
{
	ifstream fin(fname);
	int a[10000];
	while (fin.eof() == false)
	{
		for (int i = 0; i < n; i++)
		{
			fin >> a[i];
		}
	}

	int count_cmp = 0, count_move = 0;
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	for (int i = 0; i< n - 1; ++i) 
	{
		for (int j = 0; j < n - i - 1; ++j) 
		{
			count_cmp++;
			if (a[j] > a[j + 1])
			{
				int tmp = a[j]; 
				a[j] = a[j + 1];  
				a[j + 1] = tmp;
				count_move++;
			}
		}
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	cout << "冒泡排序:" << endl;
	cout << "运行时间:" << total_t << "s" << endl;
	cout << "比较次数:" << count_cmp << endl << "移动次数:" << count_move << endl;
	cout << endl;
}


void swap(int *a, int *b)

{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}



int partition(int a[], int low, int high, int &cmp, int &move)
{
	int privotKey = a[low];                             //基准元素  
	while (low < high) 
	{                                   //从表的两端交替地向中间扫描  
		while (low < high  && a[high] >= privotKey)
		{
			--high;  //从high 所指位置向前搜索，至多到low+1 位置。将比基准元素小的交换到低端 
			cmp++;
		}
		swap(&a[low], &a[high]);
		move++;
		while (low < high  && a[low] <= privotKey)
		{
			++low;
			cmp++;
		}
		swap(&a[low], &a[high]);
		move++;
	}
	return low;
}


void QuickSort(int a[], int low, int high, int &cmp, int &move)
{
	if (low < high) 
	{
		int privotLoc = partition(a, low, high, cmp, move);  //将表一分为二  
		QuickSort(a, low, privotLoc - 1, cmp, move);          //递归对低子表递归排序  
		QuickSort(a, privotLoc + 1, high, cmp, move);        //递归对高子表递归排序  
	}
}

void QuickSortPackage(string fname, int n)
{
	ifstream fin(fname);
	int a[10000];
	while (fin.eof() == false)
	{
		for (int i = 0; i < n; i++)
		{
			fin >> a[i];
		}
	}

	int count_cmp = 0, count_move = 0;
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	QuickSort(a, 0, n - 1, count_cmp, count_move);

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	cout << "快速排序:" << endl;
	cout << "运行时间:" << total_t << "s" << endl;
	cout << "比较次数:" << count_cmp << endl << "移动次数:" << count_move << endl;
	cout << endl;
}



//将r[i…m]和r[m +1 …n]归并到辅助数组rf[i…n]  

void Merge(int *r, int *rf, int i, int m, int n, int &count_cmp, int &count_move)
{
	int j, k;
	for (j = m + 1, k = i; i <= m && j <= n; ++k) 
	{
		count_cmp++; count_move++;
		if (r[j] < r[i]) rf[k] = r[j++];
		else rf[k] = r[i++];
	}
	while (i <= m)
	{
		rf[k++] = r[i++];
		count_cmp++; count_move++;
	}

	while (j <= n)
	{
		rf[k++] = r[j++];
		count_cmp++; count_move++;
	}
}



void MergeSort(int *r, int *rf, int lenght)
{
	int count_cmp = 0, count_move = 0;
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	int len = 1;
	int *q = r;
	int *tmp;
	while
		(len < lenght) 
	{
		int s = len;
		len = 2 * s;
		int i = 0;
		while (i + len <lenght)
		{
			Merge(q, rf, i, i + s - 1, i + len - 1, count_cmp, count_move); //对等长的两个子表合并  
			i = i + len;
		}
		if (i + s < lenght) 
		{
			Merge(q, rf, i, i + s - 1, lenght - 1, count_cmp, count_move); //对不等长的两个子表合并  
		}
		tmp = q; q = rf; rf = tmp;
		count_move++;//交换q,rf，以保证下一趟归并时，仍从q 归并到rf 
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	cout << "冒泡排序:" << endl;
	cout << "运行时间:" << total_t << "s" << endl;
	cout << "比较次数:" << count_cmp << endl << "移动次数:" << count_move << endl;
	cout << endl;
}




int main()
{
	int n;
	cout<<"该程序将会展示对于一个无序，升序，降序线性表各个排序算法所需时间，表内数据比较，交换次数。\n请输入线性表长度：(不多于10000)\n";
	cin >> n;
	getList(n);
	cout << "对于无序表:" << endl;
	cout << endl;
	InsertSort("unordered_list.txt", n);
	//ShellSort("unordered_list.txt",n);
	SelectSort("unordered_list.txt", n);
	HeapSort("unordered_list.txt", n);
	BubbleSort("unordered_list.txt", n);
	QuickSortPackage("unordered_list.txt", n);

	ifstream fin1("unordered_list.txt");
	int a[10000], b[10000];
	while (fin1.eof() == false)
	{
		for (int i = 0; i < n; i++)
		{
			fin1 >> a[i];
		}
	}
	MergeSort(a, b, n);

	cout << "对于升序表:" << endl;
	cout << endl;
	InsertSort("ascending_list.txt", n);
	//ShellSort("ascending_list.txt",n);
	SelectSort("ascending_list.txt", n);
	HeapSort("ascending_list.txt", n);
	BubbleSort("ascending_list.txt", n);
	QuickSortPackage("ascending_list.txt", n);

	ifstream fin2("ascending_list.txt");
	int c[10000], d[10000];
	while (fin2.eof() == false)
	{
		for (int i = 0; i < n; i++)
		{
			fin2 >> c[i];
		}
	}
	MergeSort(c, d, n);

	cout << "对于降序表:" << endl;
	cout << endl;
	InsertSort("descending_list.txt", n);
	//ShellSort("descending_list.txt",n);
	SelectSort("descending_list.txt", n);
	HeapSort("descending_list.txt", n);
	BubbleSort("descending_list.txt", n);
	QuickSortPackage("descending_list.txt", n);

	ifstream fin3("descending_list.txt");
	int e[10000], f[10000];
	while (fin3.eof() == false)
	{
		for (int i = 0; i < n; i++)
		{
			fin3 >> e[i];
		}
	}
	MergeSort(e, f, n);

	system("pause");
}
