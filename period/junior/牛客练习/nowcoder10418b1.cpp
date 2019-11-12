// 牛客网 - 成绩排序
// https://www.nowcoder.com/practice/0383714a1bb749499050d2e0610418b1

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

struct Student {
    unsigned index;
    string name;
    int score;
};


auto getCmp(bool isAsc) {
    return [isAsc](Student a, Student b) {
        if (a.score != b.score) {
            if (isAsc) {
                return a.score < b.score; 
            }
            return a.score > b.score;
        }
        return a.index < b.index;
    };
}

int main() {
    int numberOfStudents;
    
    while (cin >> numberOfStudents) {
        vector<Student> students(numberOfStudents);

        bool isAsc; cin >> isAsc;

        for (int i = 0; i < numberOfStudents; ++i) {
            students[i].index = i;
            cin >> students[i].name >> students[i].score;
        }
        
        sort(students.begin(), students.end(), getCmp(isAsc));

        for (int i = 0; i < numberOfStudents; ++i) {
            cout << students[i].name << " " << students[i].score << endl;
        }
    }
}
