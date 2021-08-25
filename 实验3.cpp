#include <queue>
#include <iostream>
#include <cstdio>
#include <string>
#include <stack>

using namespace std;


void initialize(queue<char> &p)
{
	string s;
	int i = 0,flag=1;
	while (flag)
	{
		getline(cin, s);
		for (i = 0; i < s.size(); i++)
		{
			if (!(isdigit(s[i]) || s[i] == 'J' || s[i] == 'K' || s[i] == 'Q' || s[i] == 'A'))
			{
				cout << "含有非法字符，请重新输入！" << endl;
				break;
			}
			if (i == s.size() - 1) flag = 0;
		}
	}
	for (i = 0; i < s.size(); i++)
	{
		p.push(s[i]);
	}
}

bool check(string s, char c)
{
	int i = 0;
	if (s == "") return false;
	while (i<s.size())
	{
		if (s[i] == c) return true;
		i++;
		if (i == s.size()) return false;
	}
}

string showcards(queue<char> p)
{
	
	string s;
	while (!p.empty())
	{
		s += p.front();
		p.pop();
	}
	return s;
}

void playcards(string player, queue<char> &A, stack<char> &table)
{
	string s = "";
	char tempcard;
	stack<char> tempcards;
	cout << "玩家"<<player<<"的手牌:" << showcards(A) << endl;
	if (check(s, A.front()))
	{
		tempcard = A.front();
		A.pop();
		cout << "玩家"<<player<<"出牌:" << tempcard << endl;
		tempcards.push(tempcard);
		while (table.top() != tempcard)
		{
			tempcards.push(table.top());
			table.pop();
			s.pop_back();
		}
		tempcards.push(table.top());
		table.pop();
		s.pop_back();
		cout << "玩家"<<player<<"收回:";
		while (!tempcards.empty())
		{
			A.push(tempcards.top());
			cout << tempcards.top();
			tempcards.pop();
		}
		cout << endl;
	}
	else
	{
		cout << "玩家"<<player<<"出牌:" << A.front() << endl;
		s += A.front();
		table.push(A.front());
		A.pop();
	}
	cout << "玩家"<<player<<"的手牌:" << showcards(A) << endl;
	cout << "当前桌面上的牌:" << s << endl;
	cout << endl;
}

void main_process(queue<char> &A, queue<char> &B, stack<char> &table)
{
	string s = "";
	char tempcard;
	stack<char> tempcards;
	cout << "------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout << "游戏开始!" << endl;
	while (!(A.empty() || B.empty()))
	{
		playcards("A", A, table);
		playcards("B", B, table);
	}
	string winner;
	if (A.empty()) winner = "B";
	else if (B.empty()) winner = "A";
	cout << "游戏结束！" << endl << winner << "获胜！" << endl;
}

void main()
{
	queue<char> A, B;
	stack<char> table;
	cout << "欢迎来到小猫钓鱼游戏。\n游戏规则：\n玩家分为A和B，每人手里有n张牌，两人轮流出牌并依次排列在桌面上，\n每次出掉手里的第1张牌，出牌后如果发现桌面上有跟刚才打出的牌的数字相同的牌，\n则把从相同的那张牌开始的全部牌按次序放在自己手里的牌的末尾。当一个人手中的牌先出完时，游戏结束，对方获胜。" << endl;
	cout << "请输入玩家手牌，只允许数字及J,Q,K,A,且连续不用空格隔开，如:23JKA" << endl;
	cout << "请输入玩家A的手牌:" << endl;
	initialize(A);
	cout << "请输入玩家B的手牌:" << endl;
	initialize(B);
	main_process(A, B, table);
	system("pause");
}
