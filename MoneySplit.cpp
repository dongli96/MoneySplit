#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//大钱（整型）和小钱（向量数组）
struct SMoney
{
	int big_money = -1;
	vector<int> small_money;
};

//接受最后的结果
string split_result;

//商和余数，商好像是quotient，原谅我的词汇量#-#
typedef struct
{
	int result;
	int remainer;
}SDivision;

//函数原型
SMoney MoneyRead();
SDivision GetRemainer(int d1, int d2);
void MoneySplit(int bm, vector<int> sm, int len);

int main()
{
	SMoney s;
	s = MoneyRead();
	if (s.big_money == -1)
	{
		return -1;
	}
	MoneySplit(s.big_money, s.small_money, s.small_money.size());
	cout << split_result << endl;
	return 0;
}

SMoney MoneyRead()
{
	SMoney m;
	//获得大钱的面值
	string big_money;
	cout << "请输入大钱的面值：";
	cin >> big_money;
	int i = 0;
	while (i < big_money.length())
	{
		if (isdigit(big_money[i]));
		else
		{
			cout << "输入错误。面值必须是整数";
			return m;
		}
		i++;
	}
	//获得小钱的面值，小钱种类不能超过五项
	vector<string> small_money(1);
	int j = 0;
	cout << "请输入小钱" << (j + 1) << "的面值：";
	cin >> small_money[0];
	while (small_money[j] != "#")
	{
		j++;
		if (j >= 5)
		{
			break;
		}
		small_money.resize(j+1);
		cout << "请输入小钱" << (j + 1) << "的面值：";
		cin >> small_money[j];
	}
	small_money.pop_back();
	int k;
	for (k = 0; k < small_money.size(); k++) 
	{
		int p = 0;
		while (p < small_money[k].length()) 
		{
			if (isdigit(small_money[k][p]));
			else
			{
				cout << "输入错误。面值必须是整数";
				return m;
			}
			p++;
		}
	}
	m.small_money.resize(small_money.size());
	for (k = 0; k < small_money.size(); k++)
	{
		(m.small_money)[k] = atoi(small_money[k].c_str());
	}
	m.big_money = atoi(big_money.c_str());
	return m;
}

SDivision GetRemainer(int d1, int d2)
{
	int result, remainer;
	result = d1 / d2;
	remainer = d1 - d2 * result;
	SDivision d;
	d.result = result;
	d.remainer = remainer;
	return d;
}

void MoneySplit(int bm, vector<int> sm, int len)
{
	SDivision d;
	d = GetRemainer(bm, sm[sm.size()-1]);
	if (d.remainer == 0)
	{
    // 我这里都是以字串的形式把结果直接输出到屏幕，C++不如python接口多，vector用着好不习惯，乃们可以改进
		split_result += string(" ", 2 * (len - sm.size())) + to_string(sm[sm.size() - 1]) + "*";
		split_result += to_string(d.result) + "\n";
		return;
	}
	int i;
	for (i = d.result; i >= 0; i--)
	{
		vector<int> new_sm = vector<int>(sm.begin(), sm.end() - 1);
		split_result += string(" ", 2 * (len - sm.size())) + to_string(sm[sm.size() - 1]) + "*";
		split_result += to_string(i);
		if (new_sm.size() == 0)
		{
			split_result += " NA\n";
			return;
		}
		split_result += "\n";
		MoneySplit(bm - i * sm[sm.size() - 1], new_sm, len);
	}
	return;
}
