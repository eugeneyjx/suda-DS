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
		{               //����i��Ԫ�ش���i-1Ԫ�أ�ֱ�Ӳ��롣С�ڵĻ����ƶ����������  
			count_cmp++;
			int j = i - 1;
			int x = a[i];        //����Ϊ�ڱ������洢������Ԫ��  
			a[i] = a[i - 1];           //�Ⱥ���һ��Ԫ��  
			count_move++;
			while (x < a[j]) 
			{  //�����������Ĳ���λ��  
				count_cmp++;
				a[j + 1] = a[j];
				count_move++;
				j--;         //Ԫ�غ���  
			}
			a[j + 1] = x;      //���뵽��ȷλ��  
		}
		else count_cmp++;
	}
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	cout << "��������:" << endl;
	cout << "����ʱ��:" << total_t << "s" << endl;
	cout << "�Ƚϴ���:" << count_cmp << endl << "�ƶ�����:" << count_move << endl;
	cout << endl;
}



void ShellInsertSort(int a[], int n, int dk, int &count_cmp, int &count_move)
{
	for (int i = dk; i<n; ++i) 
	{
		count_cmp++;
		if (a[i] < a[i - dk]) 
		{          //����i��Ԫ�ش���i-1Ԫ�أ�ֱ�Ӳ��롣С�ڵĻ����ƶ����������  
			int j = i - dk;
			int x = a[i];           //����Ϊ�ڱ������洢������Ԫ��  
			a[i] = a[i - dk];         //���Ⱥ���һ��Ԫ��  
			count_move++;
			while (x < a[j]) 
			{     //�����������Ĳ���λ��  
				count_cmp++;
				a[j + dk] = a[j];
				count_move++;
				j -= dk;             //Ԫ�غ���  
			}
			a[j + dk] = x;            //���뵽��ȷλ��  
		}
	}
}
//�Ȱ�����d��n/2,nΪҪ�������ĸ�������ϣ������

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
	cout << "ϣ������:" << endl;
	cout << "����ʱ��:" << total_t << "s" << endl;
	cout << "�Ƚϴ���:" << count_cmp << endl << "�ƶ�����:" << count_move << endl;
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
		key = SelectMinKey(a, n, i, count_cmp, count_move);           //ѡ����С��Ԫ��  
		count_cmp++;
		if (key != i) 
		{
			tmp = a[i];  a[i] = a[key]; a[key] = tmp;
			count_move++;//��СԪ�����iλ��Ԫ�ػ���  
		}
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	cout << "ѡ������:" << endl;
	cout << "����ʱ��:" << total_t << "s" << endl;
	cout << "�Ƚϴ���:" << count_cmp << endl << "�ƶ�����:" << count_move << endl;
	cout << endl;
}





void HeapAdjust(int H[], int s, int length, int &count_cmp, int &count_move)
{
	int tmp = H[s];
	int child = 2 * s + 1; //���ӽ���λ�á�(i+1 Ϊ��ǰ���������Һ��ӽ���λ��)  
	while (child < length) 
	{
		count_cmp++;
		if (child + 1 <length && H[child]<H[child + 1]) 
		{ 
			// ����Һ��Ӵ�������(�ҵ��ȵ�ǰ����������ĺ��ӽ��)  
			++child;
		}
		count_cmp++;
		if (H[s]<H[child]) 
		{  
			// ����ϴ���ӽ����ڸ����  
			count_move++;
			H[s] = H[child]; // ��ô�ѽϴ���ӽ�������ƶ����滻���ĸ����  
			s = child;       // ��������s ,������������һ������λ��  
			child = 2 * s + 1;
		}
		else 
		{            // �����ǰ�������������������Һ��ӣ�����Ҫ������ֱ���˳�  
			break;
		}
		H[s] = tmp;       // ��ǰ�������Ľ��ŵ������ĺ��ӽ��λ���� 
		count_move++;
	}
}


void BuildingHeap(int H[], int length, int &count_cmp, int &count_move)
{
	//���һ���к��ӵĽڵ��λ�� i=  (length -1) / 2  
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

	//��ʼ��  
	BuildingHeap(H, length, count_cmp, count_move);//�����һ��Ԫ�ؿ�ʼ�����н��е���  
	for (int i = length - 1; i > 0; --i)
	{
		//�����Ѷ�Ԫ��H[0]�Ͷ������һ��Ԫ��  
		int temp = H[i]; H[i] = H[0]; H[0] = temp;
		count_move++;//ÿ�ν����Ѷ�Ԫ�غͶ������һ��Ԫ��֮�󣬶�Ҫ�Զѽ��е���  
		HeapAdjust(H, 0, i, count_cmp, count_move);
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	cout << "������:" << endl;
	cout << "����ʱ��:" << total_t << "s" << endl;
	cout << "�Ƚϴ���:" << count_cmp << endl << "�ƶ�����:" << count_move << endl;
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
	cout << "ð������:" << endl;
	cout << "����ʱ��:" << total_t << "s" << endl;
	cout << "�Ƚϴ���:" << count_cmp << endl << "�ƶ�����:" << count_move << endl;
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
	int privotKey = a[low];                             //��׼Ԫ��  
	while (low < high) 
	{                                   //�ӱ�����˽�������м�ɨ��  
		while (low < high  && a[high] >= privotKey)
		{
			--high;  //��high ��ָλ����ǰ���������ൽlow+1 λ�á����Ȼ�׼Ԫ��С�Ľ������Ͷ� 
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
		int privotLoc = partition(a, low, high, cmp, move);  //����һ��Ϊ��  
		QuickSort(a, low, privotLoc - 1, cmp, move);          //�ݹ�Ե��ӱ�ݹ�����  
		QuickSort(a, privotLoc + 1, high, cmp, move);        //�ݹ�Ը��ӱ�ݹ�����  
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
	cout << "��������:" << endl;
	cout << "����ʱ��:" << total_t << "s" << endl;
	cout << "�Ƚϴ���:" << count_cmp << endl << "�ƶ�����:" << count_move << endl;
	cout << endl;
}



//��r[i��m]��r[m +1 ��n]�鲢����������rf[i��n]  

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
			Merge(q, rf, i, i + s - 1, i + len - 1, count_cmp, count_move); //�Եȳ��������ӱ�ϲ�  
			i = i + len;
		}
		if (i + s < lenght) 
		{
			Merge(q, rf, i, i + s - 1, lenght - 1, count_cmp, count_move); //�Բ��ȳ��������ӱ�ϲ�  
		}
		tmp = q; q = rf; rf = tmp;
		count_move++;//����q,rf���Ա�֤��һ�˹鲢ʱ���Դ�q �鲢��rf 
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	cout << "ð������:" << endl;
	cout << "����ʱ��:" << total_t << "s" << endl;
	cout << "�Ƚϴ���:" << count_cmp << endl << "�ƶ�����:" << count_move << endl;
	cout << endl;
}




int main()
{
	int n;
	cout<<"�ó��򽫻�չʾ����һ���������򣬽������Ա���������㷨����ʱ�䣬�������ݱȽϣ�����������\n���������Ա��ȣ�(������10000)\n";
	cin >> n;
	getList(n);
	cout << "���������:" << endl;
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

	cout << "���������:" << endl;
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

	cout << "���ڽ����:" << endl;
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
