#include <cctype>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include "calculator.h"
using namespace std;

struct Symbol
{
    bool isvalue;
    union {
        long double value;  // 操作数
        char optype;        // 操作符
    };
};

void show(const Symbol &syb)
{
    if (syb.isvalue) cout << syb.value;
    else cout << syb.optype;
}

vector<char> opavailable = {
    '+', '-', '*', '/', '(', ')'
};  // 定义运算符
map<char, int> oprank = {
    {'+', 2}, {'-', 2}, {'*', 4}, {'/', 4},
    {'(', -1}, {')', -1}
};  // 定义运算符优先级别
vector<Symbol> symbols, prefix_exp;

// 将字符转化为数字符号
auto tonumber = [](const string &expression, unsigned &idx) {
    long double val = 0;
    long double cur = 0.1; bool fraction = false;
    if (expression[idx] == '.') {
        fraction = true;
    }
    else val = expression[idx]-'0';
    while (idx+1<expression.size()) {
        if (isdigit(expression[idx+1])) {
            if (!fraction) {
                val = val*10 + expression[idx+1]-'0';
            }
            else {
                val += cur*(expression[idx+1]-'0');
                cur /= 10;
            }
            ++idx;
        }
        else if (expression[idx+1] == '.') {
            if (fraction) return false;
            fraction = true; ++idx;
        }
        else break;
    }

    symbols.push_back({true, val});
    return true;
};

// 将字符转化为操作符符号
auto tooptype = [](const string &expression, unsigned &idx) {
    const decltype(opavailable) &opa = opavailable;
    if (find(opa.begin(), opa.end(), expression[idx]) == opa.end())
        return false;

    symbols.push_back(Symbol{false, {.optype = expression[idx]}});
    return true;
};

bool resolve(const string &expression)
{
    symbols.clear();

    // 解析表达式为符号
    for (unsigned i=0; i<expression.size(); ++i)
    {
        if (isblank(expression[i])) continue;
        if (isdigit(expression[i]) || expression[i] == '.') {
            if (tonumber(expression, i)) continue;
            else return false;
        }
        else {
            if (tooptype(expression, i)) continue;
            else return false;
        }
    }

    // 将中缀符号转换为前缀符号
    stack<Symbol> opstack, midstack;
    for (auto it = symbols.rbegin(); it != symbols.rend(); ++it)
    {
        // 处理数字
        if (it->isvalue) {
            midstack.push(*it); continue;
        }

        // 处理括号
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

        // 处理运算符
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
        if (it -> isvalue) {
            stk.push(it->value); continue;
        }

        long double lhs = 0, rhs = 0, rslt = 0;
        if (!stk.empty()) {
            lhs = stk.top(); stk.pop();
        }
        if (!stk.empty()) {
            rhs = stk.top(); stk.pop();
        }

        switch (it -> optype) {
            case '+': rslt = lhs + rhs; break;
            case '-': rslt = lhs - rhs; break;
            case '*': rslt = lhs * rhs; break;
            case '/': rslt = lhs / rhs; break;
        }
        stk.push(rslt);
    }

    return stk.top();
}
