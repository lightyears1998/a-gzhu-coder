// 可能是比较常见的一道编程模拟题？

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

class CStudent{
public:
    CStudent(int code, int score_chinese, int score_english, int score_geography, int score_history) {
        this->code = code;
        this->score_chinese = score_chinese;
        this->score_english = score_english;
        this->score_geography = score_geography;
        this->score_history = score_history;
    }
    ~CStudent() = default;

    string show() {
        return string(
            to_string(code) + ' ' + to_string(score_chinese) + ' ' + to_string(score_english) + ' '
            + to_string(score_geography) + ' ' + to_string(score_history) + ' ' + to_string(get_average_score())
        );
    }

    int get_average_score() const {
        return (score_chinese + score_english + score_geography + score_geography) / 4;
    }

    bool operator < (const CStudent oth) const {
        return get_average_score() < oth.get_average_score();
    }

protected:
    int code;                // 学号
    int score_chinese;       // 语文成绩
    int score_english;       // 英语成绩
    int score_geography;     // 地理成绩
    int score_history;       // 历史成绩
};

int random_score() {
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    return 30 + rand() % 71;
}

int main()
{
    vector<CStudent> students;
    for (int i = 1; i <= 40; ++i) {
        students.push_back(CStudent(i, random_score(), random_score(), random_score(), random_score()));
    }

    ofstream file("student.txt");
    
    file << "学生信息" << endl;
    file << "=======" << endl;
    file << "学号 | 语文 | 英语 | 地理 | 历史 | 平均" << endl;
    int passed = 0;  // 及格人数
    for (CStudent stu : students) {
        file << stu.show() << endl;
        if (stu.get_average_score() >= 60) {
            passed++;
        }
    }
    
    file << endl;
    file << "平均分及格：" + to_string(passed) << endl;
    file << "不及格：" + to_string(40 - passed) << endl;
    file << endl;

    sort(students.begin(), students.end());
    for (CStudent stu : students) {
        file << stu.show() << endl;
    }
    file.close();
}
