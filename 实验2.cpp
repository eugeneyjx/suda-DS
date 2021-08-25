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
	while (s[i] != '#') //从整个表达式开头一个字一个字开始循环，直到# 
	{
		if (isdigit(s[i]) || s[i] == '.')  //如果是数字 
		{
			output += s[i]; //把这个数字加进output的字符串里 
			if (!(isdigit(s[i + 1]) || s[i + 1] == '.')) output += ' '; //如果下一位不是数字或者小数点 就在输出字符串里加上一个空格 表示这个数字已经结尾了 
		}
		else if (s[i] == '*' || s[i] == '/') //如果是*或/ 
		{
			while (!symbols.empty())
			{
				if (symbols.top() == '*' || symbols.top() == '/')//检查栈顶是否也是*或/ 
				{
					output += symbols.top();//如果是，把栈顶元素弹出，并加入输出字符串，再把新来的*或/压入栈中 
					output += ' ';
					symbols.pop();
				}
				else break;
			}
			symbols.push(s[i]);//如果不是，就直接压入栈 
		}
		else if (s[i] == '(') symbols.push(s[i]);//如果是（，直接压入栈 
		else if (s[i] == '+' || s[i] == '-')//如果是+或- 
		{
			while (!symbols.empty())
			{
				if (symbols.top() == '*' || symbols.top() == '/' || symbols.top() == '+' || symbols.top() == '-')//检查前一位是否是*或/或+或-，同理 
				{
					output += symbols.top();
					output += ' ';
					symbols.pop();
				}
				else break;
			}
			symbols.push(s[i]);
		}
		else if (s[i] == ')')//如果是） 
		{
			while (!symbols.empty())
			{
				if (symbols.top() != '(')//则弹栈直到碰到（ 
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
	while (!symbols.empty())//最后检查栈是否空 
	{
		output += symbols.top();//全部弹入字符串里 
		output += ' ';
		symbols.pop();
	}
	return output;
}

double calculator(const string &s)
{
	stack<double> calc;//定义一个栈 
	double x, y;
	int n = s.size(), i = 0;//n为表达式长度 
	double tempdigit;
	string tempstr;
	while (i<n)//从表达式开头循环到结尾 
	{
		tempstr = "";
		while (isdigit(s[i]) || s[i] == '.') //判断当前这一位是不是数字或者. 
		{
			tempstr += s[i];//如果是就暂时存储起来，直到把整个数字都识别出来，例如3.5就从3 . 5 这样的顺序识别下去直到下一位不是数字，这样就获得了一个完整的数字 
			i++;
			if (s[i] == ' ')//识别到空格时，说明上一个数字已经完整识别 
			{
				stringstream ss;
				ss << tempstr;
				ss >> tempdigit;//此处操作为把字符串格式的数字转为数字 
				calc.push(tempdigit);//并压入栈中 
			}
		}
		switch (s[i])//如果识别到操作符 
		{
		case '+': x = calc.top(); calc.pop(); y = calc.top(); calc.pop(); calc.push(y + x); break;//拿出栈顶两个元素，分别赋值给x，y ，做加减乘除，再压入栈中 
		case '-': x = calc.top(); calc.pop(); y = calc.top(); calc.pop(); calc.push(y - x); break;
		case '*': x = calc.top(); calc.pop(); y = calc.top(); calc.pop(); calc.push(y*x); break;
		case '/': x = calc.top(); calc.pop(); y = calc.top(); calc.pop(); calc.push(y / x); break;
		}
		i++;
	}
	return calc.top();//最后栈中剩下的值为结果，返回结果 
}

bool iscorrect(const string &s)
{
	stack<char> brackets;
	for (int i = 0; i<s.size(); i++)
	{
		if (s[i] == '(') brackets.push(s[i]);
		if (!(isdigit(s[i]) || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '#' || s[i] == '.' || s[i] == '(' || s[i] == ')'))
		{
			cout << "含有非法字符，请重新输入" << endl;
			return false;
		}
		else if (s[i] == ')')
		{
			if (brackets.empty())
			{
				cout << "括号没有成对，请重新输入" << endl;
				return false;
			}
			else brackets.pop();
		}
	}
	if (s == "" || s == " " || s == "\n")
	{
		cout << "无输入，请重新输入" << endl;
	}
	if (s[s.size() - 1] != '#')
	{
		cout << "没有以#结尾，请重新输入" << endl;
		return false;
	}

	if (brackets.empty()) return true;
	else return false;
}

int main()
{
	int flag = 1;
	cout << "请输入算式表达式,并以#结尾：";
	string s;
	while (flag)
	{
		cin >> s;
		if (iscorrect(s)) flag = 0;
	}
	string r = midfixtopostfix(s);
	cout << "后缀表达式为:" << r << endl;
	cout << "结果为:" << calculator(r) << endl;
	system("pause");
}
