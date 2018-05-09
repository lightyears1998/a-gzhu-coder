#include "toolchain.h"

string timestamp()
{
	time_t current;
	time(&current);

	string stamp = string(ctime(&current));
	stamp = "[" + stamp.substr(0, stamp.size()-1) + "]";
	return stamp;
}

void error(const string &comment, EventLevel level)
{
	cerr << timestamp() << ' ' << event_name[level] << ' ' << comment << endl;
}

void log(const string &comment, EventLevel level)
{
	clog << timestamp() << ' ' << event_name[level] << ' ' << comment << endl;
}

string parse_raw_string(fstream &file)
{
	char buf[2048]; memset(buf, 0, sizeof(buf));
	unsigned tail = 0;
	while (!file.eof() && file.read(buf+tail, 1))
	{
		if (buf[tail] == '\0') break;
		++tail;
	}
	return string(buf);
}

void show(const Book &book, unsigned idx)
{
	cout << "<-- " << idx << endl;
	cout << "������" << book.title << endl;
	cout << "�����磺" << book.press << endl;
	cout << "���ߣ�" << book.author << endl;
	cout << "�۸�" << book.price << endl;
	cout << "-->" << endl;
}

template<>
void input<string>(string &t, const string &comment)
{
	cout << comment << "> "; getline(cin, t);
}

void eatline()
{
	cin.clear();
	while (cin.get() != '\n') continue;
}