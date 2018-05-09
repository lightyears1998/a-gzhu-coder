#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	string filename;
	cout << "请输入欲打开文件的文件名" << endl; cin >> filename;	
	fstream file(filename);

	int line_count = 0, char_count = 0;
	
	string str;
	while (getline(file, str))
	{
		line_count += 1;
		char_count += str.size();
	}
	cout << "行数" << line_count << endl;
	cout << "字符数（不含换行符）" << char_count << endl;

	system("pause");
}