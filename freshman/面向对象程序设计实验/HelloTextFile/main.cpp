#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	string filename;
	cout << "�����������ļ����ļ���" << endl; cin >> filename;	
	fstream file(filename);

	int line_count = 0, char_count = 0;
	
	string str;
	while (getline(file, str))
	{
		line_count += 1;
		char_count += str.size();
	}
	cout << "����" << line_count << endl;
	cout << "�ַ������������з���" << char_count << endl;

	system("pause");
}