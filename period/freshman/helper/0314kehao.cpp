#include <iostream>
using namespace std;

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a%b);
}

const int mod = 1e9+7;
int fpow(int a, int b)
{
	int ans = 1, base = a % b;
	while (b) 
	{
		if (b&1) {
			ans *= base, ans %= mod;
		}
		base *= base, base %= mod;
		b >>= 1;
	}
	return ans;
}

int main()
{
	cout << gcd(4, 2) << endl;
	cout << gcd(1, 99) << endl;
	
	cout << fpow(2, 22) << endl;
	cout << fpow(3, 4) << endl;
}
