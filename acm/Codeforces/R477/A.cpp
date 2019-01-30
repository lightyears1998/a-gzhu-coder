#include <bits/stdc++.h> 
using namespace std;

struct Time
{
	int h, m;
	Time(int h_, int m_)
	{
		h = h_, m = m_;
		if (m>=60) {
			h += 1, m -= 60;
		}
	}
	
	int operator -(const Time t) const
	{
		if (h < t.h) return -1;
		return m-t.m + (h-t.h)*60;	
	}
	Time operator+(const int i) const 
	{
		return Time(h, m+i);
	} 
	bool operator <(const Time &t) const {
		if (h != t.h) return h < t.h;
		return m<t.m;
	}
}; 

vector<Time> vec;

int main()
{
	int n, s; cin >> n >> s;
	for (int i=0; i<n; ++i) 
	{
		int hh, mm; cin >> hh >> mm;
		vec.push_back({hh, mm}); 
	}
	vec.push_back({99, 59});
	sort(vec.begin(), vec.end());
	
	Time cur(0, 0);
	if (vec[0]-cur >= s+1) {
		cout << cur.h << ' ' << cur.m << endl;
	}
	else for (int i=0; i<n; ++i)
	{
		cur = vec[i]+s+1;
		if (vec[i+1]-cur >= s+1) {
			cout << cur.h << ' ' << cur.m << endl;	
			break;
		}
	}
}
