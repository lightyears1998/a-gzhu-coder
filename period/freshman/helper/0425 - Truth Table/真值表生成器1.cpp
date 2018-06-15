#include <iostream>
#include <vector>
#include <map>
using namespace std;

// 输出真值表表头
void print(const vector<char> &symbols, const string &expression)
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

// 根据各个符号的真假计算表达式的真假，忽略运算符优先级 
bool calculate(const string &exp, const map<char, bool> &mp)
{
	bool rslt = true; bool rev = false;
	char oprt = '*';
	for (unsigned i=0; i<exp.size(); ++i) 
	{
		if (exp[i] == '~') {
			rev = !rev; continue;
		}
		if (mp.find(exp[i]) != mp.end()) {
			bool cur = mp.find(exp[i])->second;
			if (rev) {
				cur = !cur;
				rev = false;
			}
			switch(oprt) {
				case '*': rslt = rslt && cur; break; 
				case '+': rslt = rslt || cur; break;
				case '%': rslt = rslt ^ cur; break;
				case '>': rslt = ((rslt==cur)||(rslt<cur)); break;
				case '^': rslt = !(rslt^cur); break;
			}
			continue;
		}
		else {
			oprt = exp[i]; continue;
		}
	}
	return rslt;
}

int main()
{
	int n; vector<char> symbols;  // 储存符号数量，符号 
	
	cin >> n; symbols.resize(n);
	for (int i=0; i<n; ++i) {
		cin >> symbols[i];
	}
	
	string expression; cin >> expression;  // 储存表达式 
	
	print(symbols, expression); 
	
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
		bool rslt = calculate(expression, mp);
		print(value, rslt);
	}
} 
