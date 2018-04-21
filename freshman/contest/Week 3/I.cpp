#include <bits/stdc++.h>
using namespace std; 

int main()
{
	string s;
	while (getline(cin, s)) 
	{
		if (s == "#") break;
		
		int sum = 0;
		for (unsigned i=0; i<s.size(); ++i) {
			if (isalpha(s[i])) sum += (i+1)*(s[i]-'A'+1);
			else continue;
		}
		cout << sum << endl;
	}
}
