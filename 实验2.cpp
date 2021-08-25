#include <iostream>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

string midfixtopostfix(string &s)
{
	int i = 0;
	stack<char> symbols;
	string output = "";
	while (s[i] != '#') //���������ʽ��ͷһ����һ���ֿ�ʼѭ����ֱ��# 
	{
		if (isdigit(s[i]) || s[i] == '.')  //��������� 
		{
			output += s[i]; //��������ּӽ�output���ַ����� 
			if (!(isdigit(s[i + 1]) || s[i + 1] == '.')) output += ' '; //�����һλ�������ֻ���С���� ��������ַ��������һ���ո� ��ʾ��������Ѿ���β�� 
		}
		else if (s[i] == '*' || s[i] == '/') //�����*��/ 
		{
			while (!symbols.empty())
			{
				if (symbols.top() == '*' || symbols.top() == '/')//���ջ���Ƿ�Ҳ��*��/ 
				{
					output += symbols.top();//����ǣ���ջ��Ԫ�ص���������������ַ������ٰ�������*��/ѹ��ջ�� 
					output += ' ';
					symbols.pop();
				}
				else break;
			}
			symbols.push(s[i]);//������ǣ���ֱ��ѹ��ջ 
		}
		else if (s[i] == '(') symbols.push(s[i]);//����ǣ���ֱ��ѹ��ջ 
		else if (s[i] == '+' || s[i] == '-')//�����+��- 
		{
			while (!symbols.empty())
			{
				if (symbols.top() == '*' || symbols.top() == '/' || symbols.top() == '+' || symbols.top() == '-')//���ǰһλ�Ƿ���*��/��+��-��ͬ�� 
				{
					output += symbols.top();
					output += ' ';
					symbols.pop();
				}
				else break;
			}
			symbols.push(s[i]);
		}
		else if (s[i] == ')')//����ǣ� 
		{
			while (!symbols.empty())
			{
				if (symbols.top() != '(')//��ջֱ�������� 
				{
					output += symbols.top();
					output += ' ';
					symbols.pop();
				}
				else break;
			}
			symbols.pop();
		}
		i++;
	}
	while (!symbols.empty())//�����ջ�Ƿ�� 
	{
		output += symbols.top();//ȫ�������ַ����� 
		output += ' ';
		symbols.pop();
	}
	return output;
}

double calculator(const string &s)
{
	stack<double> calc;//����һ��ջ 
	double x, y;
	int n = s.size(), i = 0;//nΪ���ʽ���� 
	double tempdigit;
	string tempstr;
	while (i<n)//�ӱ��ʽ��ͷѭ������β 
	{
		tempstr = "";
		while (isdigit(s[i]) || s[i] == '.') //�жϵ�ǰ��һλ�ǲ������ֻ���. 
		{
			tempstr += s[i];//����Ǿ���ʱ�洢������ֱ�����������ֶ�ʶ�����������3.5�ʹ�3 . 5 ������˳��ʶ����ȥֱ����һλ�������֣������ͻ����һ������������ 
			i++;
			if (s[i] == ' ')//ʶ�𵽿ո�ʱ��˵����һ�������Ѿ�����ʶ�� 
			{
				stringstream ss;
				ss << tempstr;
				ss >> tempdigit;//�˴�����Ϊ���ַ�����ʽ������תΪ���� 
				calc.push(tempdigit);//��ѹ��ջ�� 
			}
		}
		switch (s[i])//���ʶ�𵽲����� 
		{
		case '+': x = calc.top(); calc.pop(); y = calc.top(); calc.pop(); calc.push(y + x); break;//�ó�ջ������Ԫ�أ��ֱ�ֵ��x��y �����Ӽ��˳�����ѹ��ջ�� 
		case '-': x = calc.top(); calc.pop(); y = calc.top(); calc.pop(); calc.push(y - x); break;
		case '*': x = calc.top(); calc.pop(); y = calc.top(); calc.pop(); calc.push(y*x); break;
		case '/': x = calc.top(); calc.pop(); y = calc.top(); calc.pop(); calc.push(y / x); break;
		}
		i++;
	}
	return calc.top();//���ջ��ʣ�µ�ֵΪ��������ؽ�� 
}

bool iscorrect(const string &s)
{
	stack<char> brackets;
	for (int i = 0; i<s.size(); i++)
	{
		if (s[i] == '(') brackets.push(s[i]);
		if (!(isdigit(s[i]) || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '#' || s[i] == '.' || s[i] == '(' || s[i] == ')'))
		{
			cout << "���зǷ��ַ�������������" << endl;
			return false;
		}
		else if (s[i] == ')')
		{
			if (brackets.empty())
			{
				cout << "����û�гɶԣ�����������" << endl;
				return false;
			}
			else brackets.pop();
		}
	}
	if (s == "" || s == " " || s == "\n")
	{
		cout << "�����룬����������" << endl;
	}
	if (s[s.size() - 1] != '#')
	{
		cout << "û����#��β������������" << endl;
		return false;
	}

	if (brackets.empty()) return true;
	else return false;
}

int main()
{
	int flag = 1;
	cout << "��������ʽ���ʽ,����#��β��";
	string s;
	while (flag)
	{
		cin >> s;
		if (iscorrect(s)) flag = 0;
	}
	string r = midfixtopostfix(s);
	cout << "��׺���ʽΪ:" << r << endl;
	cout << "���Ϊ:" << calculator(r) << endl;
	system("pause");
}
