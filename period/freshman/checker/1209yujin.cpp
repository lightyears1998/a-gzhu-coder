/* n个整数相加，注意变量的初始化 */
#include <iostream>
#include <string>
using namespace std;

void yxt(string a, string b, string &s)
{
	int right, left;
	int t = -1, k = 0;
	for (int i = a.size() - 1, j = b.size() - 1; i >= 0 || j >= 0; i--, j--)
	{
		if (i >= 0)    right = a[i] - 48;
		else        right = 0;
		if (j >= 0)    left = b[j] - 48;
		else        left = 0;
		char q = (right + left + k) % 10 + 48;
		k = (right + left + k) / 10;
		s += q;
	}
	if (k != 0) s += (k + 48);
	for (int i = 0;i<s.size() / 2;i++)
	{
		char q = s[i];
		s[i] = s[s.size() - 1 - i];
		s[s.size() - 1 - i] = q;
	}
}

int main()
{
	string a, b, s;
	int n;
	while (cin >> n)
	{
        s = "";
		cin >> a >> b;
		yxt(a, b, s);
		cout << s << endl;
		while (n - 2)
		{
			cin >> a;
			b = s; s = "";
			yxt(a, b, s);
			cout << s << endl;
			n--;
		}
	}
}
