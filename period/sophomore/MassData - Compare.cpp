#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<ctime>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<functional>
#include<map>

using namespace std;

hash<string> hash_fn;

const int M = 10240000;
const int m = M / 64;
const int LENGTH = 5;
const int FILE_LIMIT = 256;

// 产生随机文件
void GenerateRandomFile(string path)
{
	ofstream file1(path, ios::out | ios::binary);
	assert(file1.is_open());
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < LENGTH; ++j) {
			char s = rand() % 26 + 97;
			file1.write((char*)&s, sizeof(char));
		}
		
		if (i % m == 0)
			cout << i << "  " << double(i) / M * 100 << "%" << endl;
	}
	file1.close();
}

// 分配到256个文件
void DistributeToFile(string path) 
{
	ofstream txt1[FILE_LIMIT];
	for (int i = 0; i < FILE_LIMIT; i++)
	{
		string filename = path + "_";
		filename += to_string(i);
		
		txt1[i].open(filename, ios::out | ios::binary);
	}

	ifstream infile1(path, ios::in | ios::binary);
	assert(infile1.is_open());

	while (true)
	{
		char buf[LENGTH + 1];
		infile1.read(buf, LENGTH);
		buf[LENGTH] = '\0';

		if (!infile1.good()) break;

		string url = buf;
		int order = hash_fn(url) % FILE_LIMIT;

		txt1[order].write(buf, 1);
	}
	
	for (int i = 0; i < FILE_LIMIT; ++i) {
		txt1[i].close();
	}
}


// 遍历文件求交集
void Intersect(string path1, string path2)
{
	ofstream result("result", ios::out);
	assert(result.is_open());
	for (int i = 0; i < FILE_LIMIT; ++i) {
		string in1file = path1 + "_" + to_string(i);
		string in2file = path2 + "_" + to_string(i);

		ifstream in1(in1file, ios::binary);
		ifstream in2(in2file, ios::binary);
		assert(in1.is_open());
		assert(in2.is_open());

		map<string, bool> table;

		while (true) {
			char buf[LENGTH + 1];
			in1.read(buf, LENGTH);
			buf[LENGTH] = '\0';

			if (!in1.good()) break;

			string url = buf;
			table[url] = true;
		}

		while (true) {
			char buf[LENGTH + 1];
			in2.read(buf, LENGTH);
			buf[LENGTH] = '\0';

			if (!in2.good()) break;

			string url = buf;

			static int count = 0;
			if (table[url] == true) {
				result << url << endl;
			}
		}

		in1.close(), in2.close();
	}
	result.close();
}

int main()
{
	srand(unsigned(time(0)));
	
	GenerateRandomFile("file1");
	GenerateRandomFile("file2");

	DistributeToFile("file1");
	DistributeToFile("file2");

	Intersect("file1", "file2");
}
