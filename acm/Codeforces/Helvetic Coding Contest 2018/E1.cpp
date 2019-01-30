#include <bits/stdc++.h>
using namespace std;

struct line {
	pair<int, int> a, b;
};

int R, B; 
vector<pair<int, int>> rebel, base;
vector<int> match;
vector<line> lines;

double cp(double x1, double y1, double x2, double y2) {
	return x1*y2-x2*y1;
}

bool intersect(line &one, line &two) {
	double x1 = one.a.first, y1 = one.a.second;
	double x2 = one.b.first, y2 = one.b.second;
	double x3 = two.a.first, y3 = two.a.second;
	double x4 = two.b.first, y4 = two.b.second;
	return cp(x2-x1,y2-y1,x3-x1,y3-y1)*cp(x2-x1,y2-y1,x4-x1,y4-y1) <= 0 && 
		cp(x4-x3,y4-y3,x1-x3,y1-y3)*cp(x4-x3,y4-y3,x2-x3,y2-y3) <= 0;
}

bool judge()
{
	lines.clear();
	for (unsigned i=0; i<match.size(); ++i) {
		lines.push_back({rebel[i], base[match[i]]});
	}
	
	bool ok = true;
	for (unsigned i=0; ok && i<lines.size(); ++i) {
		for (unsigned j=i+1; ok && j<lines.size(); ++j) {
			if (intersect(lines[i], lines[j])) ok = false;
		}
	}
	return ok;
}

int main()
{
	cin >> R >> B;
	
	if (R != B) {
		cout << "No" << endl;
		return 0;
	}
	
	for (int i=0; i<R; ++i) {
		int x, y; cin >> x >> y; 
		rebel.push_back({x, y});
	}
	for (int j=0; j<B; ++j) {
		int x, y; cin >> x >> y;
		base.push_back({x, y});
	}
	
	match.resize(R);
	iota(match.begin(), match.end(), 0);
	
	bool matched = false;
	do {
		matched = judge();
	} while (!matched && next_permutation(match.begin(), match.end()));
	
	cout << (matched ? "Yes" : "No") << endl;
}
