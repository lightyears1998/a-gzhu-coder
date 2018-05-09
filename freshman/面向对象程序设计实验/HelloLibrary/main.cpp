#include "book.h"
#include "toolchain.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const static string dat_path = "book.txt";
const static string log_path = "log.txt";
ofstream log_file;
fstream file;
vector<Book> books;

void init();
void menu();
void explore();
void append();
void locate();
void erase();
void dispose();

int main()
{
	init();

	while (true)
	{
		menu();

		int choice; input(choice);
		switch (choice)
		{
		case 1: explore(); break;
		case 2: append(); break;
		case 3: locate(); break;
		case 4: erase(); break;
		case 0: exit(0); break;
		default: cout << "Noops" << endl; system("pause");
		}
	}

	system("pause");
}

void init()
{
	log_file.open(log_path, ios::app);
	if (!log_file.is_open()) {
		error("无法打开日志文件", Error);
		exit(-1);
	}
	clog.rdbuf(log_file.rdbuf());

	file.open(dat_path, ios::in);
	if (file.is_open()) {
		log("图书记录已经存在");

		// 从文件中读取图书信息
		while (true)
		{
			Book nxt;

			nxt.title = parse_raw_string(file);
			nxt.press = parse_raw_string(file);
			nxt.author = parse_raw_string(file);
			file.read((char*)&nxt.price, sizeof(double));
 
			if (!file.eof())
				books.push_back(nxt);
			else break;
		}

		log(string("从文件中读取") + to_string(books.size()) + string("条记录"));
	}
	else log("图书记录不存在");

	atexit(dispose);
	
	log("程序初始化");
	log("关键文件初始化成功");
}

void menu()
{
	system("cls");
	cout << "神奇的图书管理系统" << endl; 
	cout << "1 - 浏览图书" << endl; 
	cout << "2 - 添加图书" << endl; 
	cout << "3 - 以编号查询图书" << endl; 
	cout << "4 - 以编号删除图书" << endl; 
	cout << "0 - 退出" << endl;
}

void explore()
{
	for (unsigned i=0; i<books.size(); ++i) {
		show(books[i], i);
	}
	log("浏览图书记录");

	system("pause");
}

void append()
{
	Book nxt;
	input(nxt.title, "书名");
	input(nxt.press, "出版社");
	input(nxt.author, "作者");
	input(nxt.price, "价格");
	books.push_back(nxt);

	cout << "已添加图书: " << nxt.title << endl;
	system("pause");

	log(string("添加图书") + nxt.title);
}

void locate()
{
	unsigned idx; input(idx, "图书编号");
	if (idx >= books.size())
	{
		cout << "不存在编号为" << idx << "的图书" << endl;
		system("pause");

		log(string("找不到编号为") + to_string(idx) + string("的图书"));
		return;
	}
	show(books[idx], idx);
	system("pause");

	log(string("显示标题为") + books[idx].title + string("的图书")); 
}

void erase()
{
	unsigned idx; input(idx, "图书编号");
	if (idx >= books.size())
	{
		cout << "不存在编号为" << idx << "的图书" << endl;
		system("pause");

		log(string("找不到编号为") + to_string(idx) + string("的图书"));
		return;
	}
	books.erase(books.begin() + idx);

	log(string("删除标题为") + books[idx].title + string("的图书")); 

}

void dispose()
{
	log("准备将更改保存到文件");

	file.close();
	file.open(dat_path, ios::out | ios::trunc);
	file.seekp(0, ios::beg);
	for (unsigned i=0; i<books.size(); ++i)
	{
		file.write(books[i].title.c_str(), strlen(books[i].title.c_str())+1);
		file.write(books[i].press.c_str(), strlen(books[i].press.c_str())+1);
		file.write(books[i].author.c_str(), strlen(books[i].author.c_str())+1);
		file.write((char *)&books[i].price, sizeof(double));
	}

	log("程序终止");
	file.close();
	log_file.close();
}