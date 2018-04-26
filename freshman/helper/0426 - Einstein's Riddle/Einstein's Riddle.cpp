#include <iostream>
#include <iomanip> 
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
using namespace std;

// ����Ϊ�����ַ�����ţ��Ϳ�����һ��6*5�����־�������ʾһ�ֿ��ܵ����� 
int status[6][5];
map<int, string> word {
	{0, "British"}, {1, "Swedish"}, {2, "Danish"}, {3, "Norvegian"}, {4, "German"},
	{5, "One"}, {6, "Two"}, {7, "Three"}, {8, "Four"}, {9, "Five"},
	{10, "Red"}, {11, "White"}, {12, "Blue"}, {13, "Yellow"}, {14, "Green"},
	{15, "Milk"}, {16, "Beer"}, {17, "Tea"}, {18, "Water"}, {19, "Coffee"},
	{20, "PallMall"}, {21, "BlueMaster"}, {22, "Blend"}, {23, "Dunhill"}, {24, "Prince"},
	{25, "Bird"}, {26, "Dog"}, {27, "Horse"}, {28, "Cat"}, {29, "Fish"},
};
map<string, int> index {
	{"British", 0}, {"Swedish", 1}, {"Danish", 2}, {"Norvegian", 3}, {"German", 4},
	{"One", 5}, {"Two", 6}, {"Three", 7}, {"Four", 8}, {"Five", 9},
	{"Red", 10}, {"White", 11}, {"Blue", 12}, {"Yellow", 13}, {"Green", 14},
	{"Milk", 15}, {"Beer", 16}, {"Tea", 17}, {"Water", 18}, {"Coffee", 19},
	{"PallMall", 20}, {"BlueMaster", 21}, {"Blend", 22}, {"Dunhill", 23}, {"Prince", 24},
	{"Bird", 25}, {"Dog", 26}, {"Horse", 27}, {"Cat", 28}, {"Fish", 29},
};

const int same=0, lft=-1, rght=1, near=2;

struct rule
{
	int lhs, rhs; 
	int type;  // �ο������same, lft, rght, near���� 
	rule(int lhs_, int rhs_, int type_) {
		lhs = lhs_, rhs = rhs_, type = type_;
	} 
};

vector<rule> rules;

void init();
bool check(int);
void print();

int main()
{
	init();  // ��ʼ�� 
	
	// ö�����п��ܵ�״̬
	do {
		if (!check(1)) continue;  // ���ݹ��������ĵ�0�к͵�1�У������������������ö����һ����� 
		do {
			if (!check(2)) continue;
			do {
				if (!check(3)) continue;
				do {
					if (!check(4)) continue;
					do {
						if (check(5)) {
							print();
						}
					} while (next_permutation(status[5], status[5]+5));
				} while (next_permutation(status[4], status[4]+5));
			} while (next_permutation(status[3], status[3]+5));
		} while (next_permutation(status[2], status[2]+5));
	} while (next_permutation(status[1], status[1]+5));  // ö�پ���ĵ�һ�����п��ܳ��ֵ���� 
}

// ����ʼ״̬���󣬲��Ҵ������� 
void init()
{
	// ���״̬����
	for (int i=0; i<30; ++i) {
		status[i/5][i%5] = i;
	}
	
	// �������� 
	rules.push_back({index["Danish"], index["Red"], same});
	rules.push_back({index["Swedish"], index["Dog"], same});
	rules.push_back({index["British"], index["Tea"], same});
	rules.push_back({index["Green"], index["White"], lft});
	rules.push_back({index["Green"], index["Coffee"], same});
	rules.push_back({index["PallMall"], index["Bird"], same});
	rules.push_back({index["Yellow"], index["Dunhill"], same});
	rules.push_back({index["Three"], index["Milk"], same});
	rules.push_back({index["Norvegian"], index["One"], same});
	rules.push_back({index["Blend"], index["Cat"], near});
	rules.push_back({index["Horse"], index["Dunhill"], near});
	rules.push_back({index["BlueMaster"], index["Beer"], same});
	rules.push_back({index["German"], index["Prince"], same});
	rules.push_back({index["Norvegian"], index["Blue"], near});
	rules.push_back({index["Blend"], index["Water"], near});
}

// �������ǰlevel���Ƿ���Ϲ��� 
bool check(int level)
{
	for (unsigned i=0; i<rules.size(); ++i) {
		int lhs = rules[i].lhs, rhs = rules[i].rhs;
		int Lrow = lhs/5, Lcol, Rrow = rhs/5, Rcol;
		for (int i=0; i<5; ++i) {
			if (status[Lrow][i] == lhs) 
				Lcol = i;
			if (status[Rrow][i] == rhs)
				Rcol = i;
		}
		if (max(Lrow, Rrow) > level) continue;
		
		switch(rules[i].type) { 
			case same: {
				if (Lcol != Rcol) return false;
				break;
			}
			case lft: {
				if (status[1][Lcol]-status[1][Rcol]!=-1)
					return false;
				break;
			}
			case near: {
				if (abs(status[1][Lcol]-status[1][Rcol]) != 1)
					return false;
				break;
			}
		}
	}
	return true;
}

// ��ӡ����Ҫ��ľ��� 
void print()
{
	string head[6] = {
		"Nation", "Number", "Colour", "Drink", "Smoke", "Pet"
	};
	for (int i=0; i<6; ++i) {
		cout << setw(6) << left << head[i] << ":    ";
		for (int j=0; j<5; ++j) {
			cout << setw(11) << left << word[status[i][j]];
		}
		cout << endl;
	}
	cout << endl;
}
