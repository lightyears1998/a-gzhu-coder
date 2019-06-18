#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const long long TEST = 8;
const long long MINI = 1024LL * 1024;        // ~ 64MiB
const long long HUGE = 1024LL * 1024 * 256;  // ~ 1GiB

// GenerateData 生成测试数据。
// 测试数据命名形如“prefix_0”。
void GenerateData(const string prefix, int size) {
    srand(unsigned(time(nullptr)));
    for (long long i = 0; i < 10; ++i) {
        string path = prefix + '_' + to_string(i);
        fstream out(path, ios::out);

        for (int j = 0; j < size; ++j) {
            int random = rand();
            out << random << '\n';

            if (j % (1024 * 1024) == 0) {
                cout << "Producing: " << path << " " << float(j) / size * 100 << "%." << endl;
            }
        }
        out.close();
    }
    cout << "Done." << endl;
}

int main() {
    GenerateData("test", TEST);
    // GenerateData("mini", MINI);
    // GenerateData("huge", HUGE);
}
