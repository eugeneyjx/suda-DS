#include <iostream>
#include <string>
#include <sstream>

using namespace std;
class calculator
{
	int p[201];
	int q[201];
	int r[201];
	int s[201];
	int t[402];
	string n1, n2;
	int n;
public:
	calculator(const string &a, const string &b);
	~calculator();
	void CreateList();
	void Plus();
	void Minus();
	void Multiply();
};

calculator::calculator(const string &a, const string &b)
{
	n1 = a;
	n2 = b;
	memset(p, 0, sizeof(p));
	memset(q, 0, sizeof(q));
	memset(r, 0, sizeof(r));
	memset(s, 0, sizeof(s));
	memset(t, 0, sizeof(t));
}
calculator::~calculator()
{
	memset(p, 0, sizeof(p));
	memset(q, 0, sizeof(q));
	memset(r, 0, sizeof(r));
	memset(s, 0, sizeof(s));
	memset(t, 0, sizeof(t));
}

void calculator::CreateList()
{
	stringstream ss;
	if (n1.size() > n2.size()) n = n1.size();
	else n = n2.size();
	for (int i = 0; i < n1.size(); i++)
	{
		ss << n1[n1.size() - 1 - i];
		ss >> p[i];
		ss.clear();
	}
	for (int i = 0; i < n2.size(); i++)
	{
		ss << n2[n2.size() - 1 - i];
		ss >> q[i];
		ss.clear();
	}
}

void calculator::Plus()
{
	for (int i = 0; i < n; i++)
	{
		r[i] += (p[i] + q[i]) % 10;
		r[i + 1] += (p[i] + q[i]) / 10;
	}
	for (int i = 0; i < n+1; i++)
	{
		if (r[i] >= 10)
		{
			r[i + 1] += r[i] / 10;
			r[i] %= 10;
		}
	}
	cout << "相加结果为:";
	for (int i = n; i > -1; i--)
	{
		if (i == n && r[i] == 0) continue;
		cout << r[i];
	}
	cout << endl;
}

void calculator::Minus()
{
	int x, y,t,flag=1;
	stringstream ss;
	ss << n1;
	ss >> x;
	ss.clear();
	ss << n2;
	ss >> y;
	if (x < y) flag = -1;
	for (int i = 0; i < n; i++)
	{
		if (flag*(p[i] - q[i]) < 0) s[i] += 10;
		s[i] += flag * (p[i] - q[i]);
		s[i + 1] += (flag*(p[i] - q[i])-9) / 10;
	}
	cout << "相减结果为:";
	for (int i = n - 1; i > -1; i--)
	{
		if (i == n - 1 && s[i] == 0) continue;
		cout << s[i];
	}
	cout << endl;
}

void calculator::Multiply()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			t[i + j] += (p[i] * q[j]) % 10;
			t[i + j + 1] += (p[i] * q[j]) / 10;
		}
	}
	for (int i = 0; i < n1.size() + n2.size(); i++)
	{
		if (t[i] >= 10)
		{
			t[i + 1] += t[i] / 10;
			t[i] %= 10;
		}
	}
	cout << "相乘结果为:";
	for (int i = n1.size()+n2.size()-1; i > -1; i--)
	{
		if (i == n1.size() + n2.size() - 1 && t[i] == 0) continue;
		cout << t[i];
	}
	cout << endl;
}

int main()
{
	string s1, s2;
	cout << "请输入第一个数:";
	cin >> s1;
	cout << "请输入第二个数:";
	cin >> s2;

	calculator c(s1, s2);
	c.CreateList();
	c.Plus();
	c.Minus();
	c.Multiply();
	system("pause");
}