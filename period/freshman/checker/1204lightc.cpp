/* 金融数据格式化 */
#include<iostream>
#include<string>
using namespace std;

int main()
{
	string s;
	while (getline(cin, s))
	{
		string s1; 
		s1.resize(s.size() * 2);                   // 将s1的大小调整至可以容纳足够字符
		int	n = s.find(' '), len = s.size();
		
		// 补零操作
		if(len - 1 - n == 2)
		{
			s1[0] = s[len-1];
			s1[1] = s[len-2];
			s1[2] = '.';
		}
		else
		{
			s1[0] = s[len-1];
			s1[1] = '0';
			s1[2] = '.';
		}

		// 每处理3个字符添加一个分隔符
		int f = 3, work = 0;
		for(int i = n - 1; i >= 0; i--)
		{
			s1[f] = s[i];
			f++; work++;

			if (work % 3 == 0 && i != 0) 
			{
				s1[f] = ','; f++;
			}
		}

		cout << "$";
		for(int i = f - 1; i >= 0; i--)
			cout << s1[i];
		cout << endl;
	}
}
