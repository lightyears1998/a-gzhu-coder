// toolchain.h

#ifndef TOOLCHAIN_H_
#define TOOLCHAIN_H_

#include "book.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

enum EventLevel
{
	Log, Debug, Warning, Error
};

const string event_name[4] = {
	"<日志>", "<调试>", "<警告>", "<故障>",
};

string timestamp();
void error(const string&, EventLevel = Log);
void log(const string&, EventLevel = Log);

string parse_raw_string(fstream&);
void eatline();
void show(const Book&, unsigned);

template<typename T>
void input(T &t, const string & comment = "")
{
	cout << comment << "> "; cin >> t; eatline();
}

template<>
void input<string>(string &t, const string &comment);

#endif