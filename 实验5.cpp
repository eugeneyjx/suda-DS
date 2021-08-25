#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>

using namespace std;
enum Error_code
{
	success, fail, rangeerror, overflow, underflow, range_over
};
int max_list = 10000;
template <class List_entry>
class List
{
public:
	List()
	{
		count = 0;
	}//构造函数
	int size() const;
	bool full() const;
	bool empty() const;
	void traverse(void(*visit)(List_entry&));
	Error_code retrieve(int position, List_entry& x) const;
	Error_code remove(int position, List_entry& x);
	Error_code insert(int position, const List_entry& x);
	void printout()
	{
		for (int i = 0; i < count; i++)
		{
			cout << entry[i] << " ";
		}
		cout << endl;
	}
	void ListSort()//顺序表排序
	{
		for (int i = 0; i < count - 1; ++i)
		{
			int flag = 0;
			for (int j = 0; j < count - i - 1; ++j)
			{
				if (entry[j]>entry[j + 1])
				{
					swap(entry[j], entry[j + 1]);
					flag = 1;
				}
			}
			if (flag == 0)
				break;
		}
	}
protected: //私有成员数据
	int count;
	List_entry entry[10000];//所谓contiguous是指采用数组方式存储
};

template <class List_entry>
int List <List_entry>::size() const
{
	return count;
}

template <class List_entry>
bool List <List_entry>::full() const
{
	if (count == max_list) return true;
	else return false;
}

template <class List_entry>
bool List <List_entry>::empty() const
{
	if (count == 0) return true;
	else return false;
}


template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry& x)
{
	if (full()) return overflow;//溢出
	if (position<0 || position>count)
		return range_over; //插入点错误
	for (int i = count - 1; i >= position; i--)
		entry[i + 1] = entry[i];  //移动元素（从后向前）
	entry[position] = x;	//放入元素
	count++; //增加统计个数
	return success;
}

template <class List_entry>
Error_code List<List_entry> ::remove(int position, List_entry &x)
{
	if (count == 0) return underflow;
	if (position < 0 || position >= count) return rangeerror;
	x = entry[position];
	count--;
	while (position < count - 1) {
		entry[position] = entry[position + 1];
		position++;
	}
	return success;
}

template <class List_entry>
Error_code List<List_entry> ::retrieve(int position, List_entry &x) const
//如果position值非法，返回出错信息，否则根据position的值，取得表中的第position个元素，并由x返回。
{
	if (position < 0 || position >= count)
		return rangeerror;
	x = entry[position];
	return success;
}

template <class List_entry>
void  List<List_entry>::traverse(void(*visit)(List_entry&))
{
	for (int i = 0; i<count; i++)
		(*visit)(entry[i]);
	//此处，visit函数表示指定的遍历时对每个表元素执行的具体动作
}

Error_code sequential_search(int x, List<int> a, int &count)
{ 
	for (int i = 0; i < a.size(); i++)
	{
		int m;
		a.retrieve(i, m);
		count++;
		if (m == x)
		{
			return success;
		}
	}
	count -= a.size();
	return fail;
}

Error_code binary_search_nonrecursive(const int &target, const List<int> &x)
{
	int data;
	int bottom = 0, top = x.size() - 1;
	while (bottom < top) {
		int mid = (bottom + top) / 2;
		x.retrieve(mid, data);
		if (target > data)
			bottom = mid + 1;
		else
			top = mid;
	}
	if (top < bottom) return fail;
	else {
		x.retrieve(bottom, data);
		if (data == target) return success;
		else return fail;
	}
}

Error_code   binary_search_recursive(const List<int> &x, const int &target, int bottom, int top)
{
	{
		int data;
		if (bottom < top) { // List has more than one entry.
			int mid = (bottom + top) / 2;
			x.retrieve(mid, data);
			if (data < target) // Reduce to top half of list.
				return binary_search_recursive(x, target, mid + 1, top);
			else // Reduce to bottom half of list.
				return binary_search_recursive(x, target, bottom, mid);
		}
		else if (top < bottom)
			return fail; // List is empty.
		else { // List has exactly one entry.
			x.retrieve(bottom, data);
			if (data == target)
				return success;
			else
				return fail;
		}

	}
}


int main()
{
	List<int> unordered_list;
	int n;
	cout << "请输入线性表内存放整数的个数(1~9999):";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x=rand()%10000;
		unordered_list.insert(i, x);
	}
	cout << "已生成无序表:";
	unordered_list.printout();
	int m;
	cout << "请输入重复查找次数:";
	cin >> m;
	Error_code result;
	int count_success=0, count_fail=0, count_compare=0;
	clock_t start_t, end_t;
	double suc_t=0, fail_t=0;
	for (int i = 0; i < m; i++)
	{
		start_t = clock();
		result = sequential_search(rand()%10000, unordered_list, count_compare);
		if (result == 0)
		{
			end_t = clock();
			suc_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;
			count_success++;
		}
		if (result == 1)
		{
			end_t = clock();
			fail_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;
			count_fail++;
		}
	}
	cout << endl;
	cout << "在无序表中顺序查找:" << endl;
	cout << "查找成功时，算法执行的绝对时间为" << suc_t / count_success*m << "s" << endl;
	cout << "查找失败时，算法执行的绝对时间为" << fail_t / count_fail*m << "s" << endl;
	cout << "查找成功时，关键字的平均比较次数为" << count_compare / count_success << endl;
	cout << endl;

	unordered_list.ListSort();
	cout << "排序后，生成的有序表为:";
	unordered_list.printout();
	cout << endl;

	count_success = 0, count_fail = 0, count_compare = 0;
	suc_t = 0, fail_t = 0;
	for (int i = 0; i < m; i++)
	{
		start_t = clock();
		result = sequential_search(rand() % 10000, unordered_list, count_compare);
		if (result == 0)
		{
			end_t = clock();
			suc_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;
			count_success++;
		}
		else if (result == 1)
		{
			end_t = clock();
			fail_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;
			count_fail++;
		}
	}
	cout << "在有序表中顺序查找:" << endl;
	cout << "查找成功时，算法执行的绝对时间为" << suc_t / count_success*m << "s" << endl;
	cout << "查找失败时，算法执行的绝对时间为" << fail_t / count_fail*m << "s" << endl;
	cout << "查找成功时，关键字的平均比较次数为" << count_compare / count_success << endl;
	cout << endl;

	suc_t = 0, fail_t = 0;
	for (int i = 0; i < m; i++)
	{
		start_t = clock();
		result = binary_search_nonrecursive(rand() % 10000, unordered_list);
		if (result == 0)
		{
			end_t = clock();
			suc_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;
			count_success++;
		}
		else if (result == 1)
		{
			end_t = clock();
			fail_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;
			count_fail++;
		}
	}
	cout << "在有序表中使用非递归二分查找:" << endl;
	cout << "查找成功时，算法执行的绝对时间为" << suc_t / count_success*m << "s" << endl;
	cout << "查找失败时，算法执行的绝对时间为" << fail_t / count_fail*m << "s" << endl;
	cout << endl;
	
	suc_t = 0, fail_t = 0;
	for (int i = 0; i < m; i++)
	{
		start_t = clock();
		result = binary_search_recursive(unordered_list, rand() % 10000, 0, unordered_list.size()-1);
		if (result == 0)
		{
			end_t = clock();
			suc_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;
			count_success++;
		}
		else if (result == 1)
		{
			end_t = clock();
			fail_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;
			count_fail++;
		}
	}
	cout << "在有序表中使用递归二分查找:" << endl;
	cout << "查找成功时，算法执行的绝对时间为" << suc_t / count_success*m << "s" << endl;
	cout << "查找失败时，算法执行的绝对时间为" << fail_t / count_fail*m << "s" << endl;
	cout << endl;

	system("pause");
}


