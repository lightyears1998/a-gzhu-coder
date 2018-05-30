#include <bits/stdc++.h>
using namespace std;

vector<string> colors = {
	"purple", "green", "blue", "orange", "red", "yellow"	
};

vector<string> names = {
	"Power", "Time", "Space", "Soul", "Reality", "Mind"
};

bool showed[6]; 

int main()
{
	int n; cin >> n;
	int m = 6-n;
	 
	for (int i=0; i<n; ++i) {
		string str; cin >> str;
		int pos = find(colors.begin(), colors.end(), str) - colors.begin();	
		showed[pos] = true;
	}
	
	cout << m << endl;
	for (int i=0; i<6; ++i) {
		if (!showed[i]) {
			cout << names[i] << endl;
		}
	}
} 
