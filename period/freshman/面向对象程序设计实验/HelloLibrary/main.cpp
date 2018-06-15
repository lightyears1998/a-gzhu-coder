// main.cpp

#include "book.h"
#include "toolchain.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const static string dat_path = "bookf.dat";
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
		error("�޷�����־�ļ�", Error);
		exit(-1);
	}
	clog.rdbuf(log_file.rdbuf());

	file.open(dat_path, ios::in);
	if (file.is_open()) {
		log("ͼ���¼�Ѿ�����");

		while (true)
		{
			Book nxt;

			nxt.serial = parse_raw_string(file);
			nxt.title = parse_raw_string(file);
			nxt.press = parse_raw_string(file);
			nxt.author = parse_raw_string(file);
			file.read((char*)&nxt.price, sizeof(double));
 
			if (!file.eof())
				books.push_back(nxt);
			else break;
		}

		log(string("���ļ��ж�ȡ") + to_string(books.size()) + string("����¼"));
	}
	else log("ͼ���¼������");

	atexit(dispose);
	
	log("������ɳ�ʼ��");
}

void menu()
{
	system("cls");
	cout << "�����ͼ�����ϵͳ" << endl; 
	cout << "1 - ���ͼ��" << endl; 
	cout << "2 - ���ͼ��" << endl; 
	cout << "3 - �Ա�Ų�ѯͼ��" << endl; 
	cout << "4 - �Ա��ɾ��ͼ��" << endl; 
	cout << "0 - �˳�" << endl;
}

void explore()
{
	for (unsigned i=0; i<books.size(); ++i) {
		show(books[i], i);
	}
	log("���ͼ���¼");

	system("pause");
}

void append()
{
	Book nxt;
	input(nxt.serial, "���");
	input(nxt.title, "����");
	input(nxt.press, "������");
	input(nxt.author, "����");
	input(nxt.price, "�۸�");
	books.push_back(nxt);

	cout << "�����ͼ��: " << nxt.title << endl;
	system("pause");

	log(string("���ͼ��") + nxt.title);
}

void locate()
{
	string serial; input(serial, "ͼ����");
	for (auto it = books.begin(); it != books.end(); ++it)
	{
		if (it->serial == serial) {
			show(*it, it-books.begin());
			system("pause");

			log(string("��ʾ����Ϊ") + serial + string("��ͼ��"));
			return;
		}
	}
	cout << "�����ڱ���Ϊ" << serial << "��ͼ��" << endl;
	system("pause");

	log("�����ڱ���Ϊ" + serial + "��ͼ��");
}

void erase()
{
	string serial; input(serial, "ͼ����");
	for (auto it = books.begin(); it != books.end(); ++it)
	{
		if (it->serial == serial) {
			books.erase(it);
			cout << "ɾ���˱��Ϊ" << serial << "��ͼ��" << endl;
			system("pause");

			log(string("ɾ������Ϊ") + serial + string("��ͼ��"));
			return;
		}
	}
	cout << "�����ڱ��Ϊ" << serial << "��ͼ��" << endl;
	system("pause");

	log(string("�Ҳ������Ϊ") + serial + string("��ͼ��"));
	return;
}

void dispose()
{
	log("׼�������ı��浽�ļ�");

	file.close();
	file.open(dat_path, ios::out | ios::trunc);
	file.seekp(0, ios::beg);
	for (unsigned i=0; i<books.size(); ++i)
	{
		file.write(books[i].serial.c_str(), strlen(books[i].serial.c_str()) + 1);
		file.write(books[i].title.c_str(), strlen(books[i].title.c_str()) + 1);
		file.write(books[i].press.c_str(), strlen(books[i].press.c_str()) + 1);
		file.write(books[i].author.c_str(), strlen(books[i].author.c_str()) + 1);
		file.write((char *)&books[i].price, sizeof(double));
	}

	log("������ֹ");
	file.close();
	log_file.close();
}