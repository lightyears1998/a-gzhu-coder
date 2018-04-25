#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
using namespace std;
 
map<char, int> priority {
	{'~', 9}, {'*', 8}, {'+', 6},
	{'%', 6}, {'>', 4}, {'^', 2},
};  // 定义运算符优先级 
// 我查了一些资料，没有查到这些运算符的优先级是怎样的，(lll￢ω￢) 
// 仿照C++运算符的优先级给这些运算符定义了它们的优先级 

vector<char> symbols;  // 储存变量符号 

void print(const string&); 
void print(const vector<bool>&, bool);
string convert(const string&);
bool calculate(const string&, const map<char, bool>&);

int main()
{
	int n;
	cin >> n; symbols.resize(n);
	for (int i=0; i<n; ++i) {
		cin >> symbols[i];
	}
	
	string infix_exp; cin >> infix_exp;  // 取得输入的中缀表达式 
	string postfix_exp = convert(infix_exp);  // 计算相应的前缀表达式 
	
	print(infix_exp);  // 打印表头 
	
	for (int i=(1<<n)-1; i>=0; --i)  // 枚举可能的符号值 
	{
		vector<bool> value;
		for (int j=(1<<(n-1)); j; j>>=1) {
			value.push_back(i&j);
		}
		
		map<char, bool> mp;  // 将符号与真假对应起来 
		for (unsigned i=0; i<symbols.size(); ++i) {
			mp[symbols[i]] = value[i];
		}
		bool rslt = calculate(postfix_exp, mp);
		print(value, rslt);
	}
} 

// 输出真值表表头
void print(const string &expression)
{
	int length = 0;
	for (char ch : symbols) {
		cout << ch << ' '; length += 2;
	}
	cout << '|' << ' '; length += 2;
	cout << expression << endl; length += expression.size();
	
	while (length--) cout << '-';
	cout << endl;
}

// 输出真值表中的一行 
void print(const vector<bool> &value, bool rslt)
{
	for (bool val : value) {
		cout << (val ? 'T' : 'F') << ' ';
	}
	cout << '|' << ' ';
	cout << (rslt ? 'T' : 'F') << endl;
}

// 计算中缀表达式相应的前缀表达式 
string convert(const string &infix_exp)
{
	string postfix_exp;
	stack<char> rslt, oprt;  // 中间结果栈，操作符栈
	
	for (int i=infix_exp.size()-1; i>=0; --i)
	{
		if (find(symbols.begin(), symbols.end(), infix_exp[i]) != symbols.end()) {
			// 操作数进入中间结果栈 
			rslt.push(infix_exp[i]);
		}
		else if (infix_exp[i]=='(' || infix_exp[i]==')')
		{
			if (infix_exp[i] == ')') {
				// 右括号入中间结果栈 
				oprt.push(infix_exp[i]);
			}
			else {
				// 弹出上一个左括号之前的操作符，抛弃这对括号 
				while (oprt.top() != ')') {
					rslt.push(oprt.top());
					oprt.pop();
				}
				oprt.pop();
			}
		}
		else {
			// 操作符根据优先级别选择操作 
			while (!oprt.empty() && oprt.top()!=')' && priority[infix_exp[i]] < priority[oprt.top()]) 
			{
				rslt.push(oprt.top());
				oprt.pop();
			}
			oprt.push(infix_exp[i]);
		}
	}
	
	while (!oprt.empty()) {
		rslt.push(oprt.top());
		oprt.pop();
	}
	
	while (!rslt.empty()) {
		postfix_exp.push_back(rslt.top());
		rslt.pop();
	}
	return postfix_exp;
}

// 根据各个符号的真假计算前缀表达式的真假 
bool calculate(const string &exp, const map<char, bool> &mp)
{
	stack<char> stk;
	for (int i=exp.size()-1; i>=0; --i)
	{
		if (find(symbols.begin(), symbols.end(), exp[i]) != symbols.end()) {
			// 操作数直接入栈
			stk.push(mp.find(exp[i])->second); 
		}
		else {
			// 一元运算（只有‘~’） 
			if (exp[i] == '~') {
				bool cur = stk.top(); stk.pop();
				cur = !cur;
				stk.push(cur); continue;
			}
			
			// 二元运算
			bool lhs = stk.top(); stk.pop();
			bool rhs = stk.top(); stk.pop();
			bool rslt; 
			switch (exp[i]) {
				case '*': rslt = lhs && rhs; break; 
				case '+': rslt = lhs || rhs; break;
				case '%': rslt = lhs ^ rhs; break;
				case '>': rslt = ((lhs==rhs)||(lhs<rhs)); break;
				case '^': rslt = !(lhs^rhs); break;
			}
			stk.push(rslt);
		}
	}
	return stk.top();
}

