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
	}//���캯��
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
	void ListSort()//˳�������
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
protected: //˽�г�Ա����
	int count;
	List_entry entry[10000];//��νcontiguous��ָ�������鷽ʽ�洢
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
	if (full()) return overflow;//���
	if (position<0 || position>count)
		return range_over; //��������
	for (int i = count - 1; i >= position; i--)
		entry[i + 1] = entry[i];  //�ƶ�Ԫ�أ��Ӻ���ǰ��
	entry[position] = x;	//����Ԫ��
	count++; //����ͳ�Ƹ���
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
//���positionֵ�Ƿ������س�����Ϣ���������position��ֵ��ȡ�ñ��еĵ�position��Ԫ�أ�����x���ء�
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
	//�˴���visit������ʾָ���ı���ʱ��ÿ����Ԫ��ִ�еľ��嶯��
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
	cout << "���������Ա��ڴ�������ĸ���(1~9999):";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x=rand()%10000;
		unordered_list.insert(i, x);
	}
	cout << "�����������:";
	unordered_list.printout();
	int m;
	cout << "�������ظ����Ҵ���:";
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
	cout << "���������˳�����:" << endl;
	cout << "���ҳɹ�ʱ���㷨ִ�еľ���ʱ��Ϊ" << suc_t / count_success*m << "s" << endl;
	cout << "����ʧ��ʱ���㷨ִ�еľ���ʱ��Ϊ" << fail_t / count_fail*m << "s" << endl;
	cout << "���ҳɹ�ʱ���ؼ��ֵ�ƽ���Ƚϴ���Ϊ" << count_compare / count_success << endl;
	cout << endl;

	unordered_list.ListSort();
	cout << "��������ɵ������Ϊ:";
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
	cout << "���������˳�����:" << endl;
	cout << "���ҳɹ�ʱ���㷨ִ�еľ���ʱ��Ϊ" << suc_t / count_success*m << "s" << endl;
	cout << "����ʧ��ʱ���㷨ִ�еľ���ʱ��Ϊ" << fail_t / count_fail*m << "s" << endl;
	cout << "���ҳɹ�ʱ���ؼ��ֵ�ƽ���Ƚϴ���Ϊ" << count_compare / count_success << endl;
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
	cout << "���������ʹ�÷ǵݹ���ֲ���:" << endl;
	cout << "���ҳɹ�ʱ���㷨ִ�еľ���ʱ��Ϊ" << suc_t / count_success*m << "s" << endl;
	cout << "����ʧ��ʱ���㷨ִ�еľ���ʱ��Ϊ" << fail_t / count_fail*m << "s" << endl;
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
	cout << "���������ʹ�õݹ���ֲ���:" << endl;
	cout << "���ҳɹ�ʱ���㷨ִ�еľ���ʱ��Ϊ" << suc_t / count_success*m << "s" << endl;
	cout << "����ʧ��ʱ���㷨ִ�еľ���ʱ��Ϊ" << fail_t / count_fail*m << "s" << endl;
	cout << endl;

	system("pause");
}


