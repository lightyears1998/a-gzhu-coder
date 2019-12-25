#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <string>

using namespace std;

class IOHelper {
private:
	istream& in;
	ostream& out;

	string getline() {
		string line;
		std::getline(cin, line);
		return line;
	}

public:
	IOHelper(istream& in, ostream& out) : in(in), out(out) {
		out << "模拟时间片轮转进程调度法" << endl;
		out << "==================" << endl;
	}

	bool question(const string& hint) {
		bool answer;
		bool ok = false;
		do {
			out << hint << " [y/n] >> ";
			string line = getline();

			if (line.length() > 0) {
				if (tolower(line[0]) == 'y') {
					answer = true, ok = true;
				}
				else if (tolower(line[0]) == 'n') {
					answer = false, ok = true;
				}
			}
			if (!ok) {
				out << "请输入y或n。" << endl;
			}
			else return answer;
		} while (!ok);
		return false;
	}

	int nextInt(const string& hint) {
		out << hint << ">> ";
		string line = getline();
		
		int ret;
		try {
			ret = stoi(line);
		}
		catch(const std::invalid_argument&) {
			ret = -1;
		}
		return ret;
	}

	string getline(const string& hint) {
		out << hint << ">> ";
		return getline();
	}
};

#endif // !UTIL_HPP
