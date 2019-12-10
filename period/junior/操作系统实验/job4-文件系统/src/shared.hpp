#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>


using namespace std;


// 文件备份函数
//
// 将source文件备份为destination文件。
// 若source文件不存在，则报错并终止。
// 如destination文件已存在，则报错并终止。
void backupFile(string source, string destination);


// 命令行参数助手
class CommandLineHelper {
    int argc;
    const char **argv;

public:
    CommandLineHelper(int argc, const char *argv[]) : argc(argc), argv(argv) {}

    // 取得命令行程序的名称。
    string getProgramName() {
        string path = string(argv[0]);
        string name = path.substr(max(path.find_last_of('\\'), path.find_last_of('/')) + 1);
        return name;
    }

    // 打印程序的用法。
    void printUsage() {
        cout << "用法：" << getProgramName() << " 源文件<src> 目标文件<dst>" << endl;
        cout << endl;
        cout << "需要提供两个参数<src>和<dst>，" << endl
            << "程序将<src>文件备份到<dst>目录中。" << endl;
    }

    // 返回待备份文件的路径。
    string getSourceFilePath() {
        assert(argc >= 2);
        return string(argv[1]);
    }

    // 返回备份目标文件夹的路径。
    string getDestinationPath() {
        assert(argc >= 3);
        return string(argv[2]);
    }
};


// 程序执行入口
//
// 除程序名称外，程序还需要从Shell中获取两个参数src和dst，
// 分别对应待备份文件的路径和备份目标文件夹的路径。
int main(int argc, const char * argv[]) {
    CommandLineHelper helper(argc, argv);
    
    // 提供的参数不足时，打印程序的用法。
    if (argc < 3) {
        helper.printUsage();
        return 0;
    }

    // 备份文件。
    // backupFile函数实现于各个编译单元中。
    backupFile(helper.getSourceFilePath(), helper.getDestinationPath());
}
