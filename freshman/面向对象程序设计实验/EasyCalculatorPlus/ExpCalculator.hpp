#include <cctype>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <functional>
using namespace std;

struct Symbol
{
	bool isvalue;
	union {
		long double value;  // ������
		wchar_t optype;        // ������
	};
};

class Calculator {
public:
	bool resolve(const wstring &expression)
	{
		symbols.clear();

		// �������ʽΪ����
		for (unsigned i = 0; i<expression.size(); ++i)
		{
			if (iswblank(expression[i])) continue;
			if (iswdigit(expression[i]) || expression[i] == '.') {
				if (tonumber(expression, i)) continue;
				else return false;
			}
			else {
				if (tooptype(expression, i)) continue;
				else return false;
			}
		}

		// ����׺����ת��Ϊǰ׺����
		stack<Symbol> opstack, midstack;
		for (auto it = symbols.rbegin(); it != symbols.rend(); ++it)
		{
			// ��������
			if (it->isvalue) {
				midstack.push(*it); continue;
			}

			// ��������
			if (it->optype == ')') {
				opstack.push(*it); continue;
			}
			if (it->optype == '(') {
				while (!opstack.empty() && opstack.top().optype != ')') {
					midstack.push(opstack.top());
					opstack.pop();
				}
				if (opstack.empty()) return false;
				opstack.pop(); continue;
			}

			// ���������
			while (!opstack.empty() && oprank[it->optype] < oprank[opstack.top().optype])
			{
				midstack.push(opstack.top());
				opstack.pop();
			}
			opstack.push(*it);
		}

		while (!opstack.empty()) {
			midstack.push(opstack.top());
			opstack.pop();
		}

		prefix_exp.clear();
		while (!midstack.empty()) {
			prefix_exp.push_back(midstack.top());
			midstack.pop();
		}
		return true;
	}

	long double calculate()
	{
		stack<long double> stk;
		for (auto it = prefix_exp.rbegin(); it != prefix_exp.rend(); ++it)
		{
			if (it->isvalue) {
				stk.push(it->value); continue;
			}

			long double lhs = 0, rhs = 0, rslt = 0;
			if (!stk.empty()) {
				lhs = stk.top(); stk.pop();
			}
			if (!stk.empty()) {
				rhs = stk.top(); stk.pop();
			}

			switch (it->optype) {
			case '+': rslt = lhs + rhs; break;
			case '-': rslt = lhs - rhs; break;
			case '*': rslt = lhs * rhs; break;
			case '/': rslt = lhs / rhs; break;
			}
			stk.push(rslt);
		}
		return stk.top();
	}

private:
	vector<wchar_t> opavailable = {
		'+', '-', '*', '/', '(', ')'
	};  // ���������
	
	map<wchar_t, int> oprank = {
		{ '+', 2 },{ '-', 2 },{ '*', 4 },{ '/', 4 },
	{ '(', -1 },{ ')', -1 }
	};  // ������������ȼ���

	vector<Symbol> symbols, prefix_exp;

	// ���ַ�ת��Ϊ���ַ���
	function<bool(const wstring&, unsigned&)> tonumber = [&](const wstring &expression, unsigned &idx) {
		long double val = 0;
		long double cur = 0.1; bool fraction = false;
		if (expression[idx] == '.') {
			fraction = true;
		}
		else val = expression[idx] - '0';
		while (idx + 1<expression.size()) {
			if (iswdigit(expression[idx + 1])) {
				if (!fraction) {
					val = val * 10 + expression[idx + 1] - '0';
				}
				else {
					val += cur * (expression[idx + 1] - '0');
					cur /= 10;
				}
				++idx;
			}
			else if (expression[idx + 1] == '.') {
				if (fraction) return false;
				fraction = true; ++idx;
			}
			else break;
		}

		symbols.push_back({ true, val });
		return true;
	};

	// ���ַ�ת��Ϊ����������
	function<bool(const wstring&, unsigned&)> tooptype = [&](const wstring &expression, unsigned &idx) {
		const decltype(opavailable) &opa = opavailable;
		if (find(opa.begin(), opa.end(), expression[idx]) == opa.end())
			return false;
		
		Symbol nxt; nxt.isvalue = false, nxt.optype = expression[idx];
		symbols.push_back(nxt);
		return true;
	};
};
