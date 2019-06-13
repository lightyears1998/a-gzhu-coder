#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;


// 返回string a是否包含b。（b为模板串）
bool StringAContainsB(string a, string b) {
    int *next = new int[b.length() + 1];

    function<void(string)> get_next = [&next](string tmp) {
        next[0] = -1;
        int i = -1, j = 0;
        while (j < int(tmp.length())) {
            if (i == -1 || tmp[i] == tmp[j]) ++i, ++j, next[j] = i;
            else i = next[i];
        }
    };
    get_next(b);

    function<bool(string, string)> kmp = [&next](string str, string tmp) {
        int i = 0, j = 0;

        while (i < int(str.length()) && j < int(tmp.length())) {
            if (j == -1 || str[i] == tmp[j]) ++i, ++j;
            else j = next[j];
        }
        return j == tmp.length();
    };
    bool matched = kmp(a, b);

    delete[] next;
    return matched;
}


// 获取环状的病毒DNA可能的链状表示。
vector<string> GetPossibleVirusDNARepresent(string virus) {
    vector<string> possible_represent;
    
    size_t length = virus.length();
    virus = virus + virus;
    for (size_t i = 0; i < length; ++i) {
        possible_represent.push_back(virus.substr(i, length));
    }
    return possible_represent;
}


// 判断人类DNA是否包含病毒DNA。
bool HumanDNAContainsVirusDNA(string human, string virus) {
    vector<string> possible_virus_represent(GetPossibleVirusDNARepresent(virus));
    
    bool matched = false;
    for (auto virus : possible_virus_represent) {
        matched = StringAContainsB(human, virus);
        if (matched) break;
    }
    return matched;
}


int main() {
    int kase;
    while (cin >> kase) {
        while (kase--) {
            string virus, human; cin >> virus >> human;
            cout << (HumanDNAContainsVirusDNA(human, virus) ? "YES" : "NO") << endl;
        }
    }
}
