#include <bits/stdc++.h>
using namespace std;

string name[200];

int main()
{
	int tot = 0;
	while (cin >> name[tot]) {
		if (name[tot] != ".") ++tot;
		else break;
	}
	
	if (tot>13) {
		cout << name[1] << " and " << name[13] << " are inviting you to dinner..." << endl;
	}
	else if (tot>1) {
		cout << name[1] << " is the only one for you..." << endl;
	}
	else cout << "Momo... No one is for you ..." << endl;
}
