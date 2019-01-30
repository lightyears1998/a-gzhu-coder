#include <iostream>
using namespace std;
using ll = long long;
using ld = long double;

// 注意类型模板的使用

const int mod = 1e9 + 7;

template<typename T>
T add(T x)
{
    return x;
}
template<typename T, typename... Ts>
T add(T x, Ts... y)
{
    T res = x + add(y...);
    if (res >= mod)
        res -= mod;
    return res;
}

int main()
{
    // 这题实际上还是不会做……
}
