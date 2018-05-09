#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	fstream file(__FILE__);

	int line_count = 0, char_count = 0;
	
	string str;
	while (getline(file, str))
	{
		line_count += 1;
		char_count += str.size();

		cout.width(2);
		cout << right << line_count << "  " << str << endl;
	}
	cout << "行数" << line_count << endl;
	cout << "字符数（不含换行符）" << char_count << endl;

	system("pause");
}