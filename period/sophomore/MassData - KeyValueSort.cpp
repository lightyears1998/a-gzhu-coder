#include <functional>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

string data_prefix = "huge";

struct Query {
	string key;
	int count;

	bool operator <(const Query oth) const {
		return count > oth.count;
	}
};


// DistributeQueriesIntoBucket 将数据利用哈希函数分类装配到10个桶中。
void DistributeQueriesIntoBucket() {
	hash<string> hash_fn;
	
	fstream out[10];
	for (int i = 0; i < 10; ++i) {
		string path = "bucket";
		path += "_" + to_string(i);

		out[i].open(path, ios::out);
	}

	for (int i = 0; i < 10; ++i) {
		cout << "Distributing: " << i << endl;

		string path = data_prefix + '_' + to_string(i);
		fstream in(path, ios::in);

		string query;
		while (in >> query) {
			int sign = hash_fn(query) % 10;
			out[sign] << query << "\n";
		}
	}

	for (int i = 0; i < 10; ++i) {
		out[i].close();
	}
}

// GetBucketResult 在桶中进行统计。
void GetBucketResult() {
	for (int i = 0; i < 10; ++i) {
		cout << "Calculatiing: " << i << endl;

		string path = "bucket";
		path += "_" + to_string(i);
		fstream in(path, ios::in);

		unordered_map<string, int> mp;
		
		string query;
		while (in >> query) {
			mp[query]++;
		}

		path = "result";
		path += "_" + to_string(i);
		fstream out(path, ios::out);
		vector<Query> result;
		for (auto it = mp.begin(); it != mp.end(); ++it) {
			result.push_back(Query{it->first, it->second});
		}

		sort(result.begin(), result.end());

		for (auto it = result.begin(); it != result.end(); ++it) {
			out << it->key << " " << it->count << endl;
		}
	}
}

// GetTotalResult 合并各个桶中统计的结果。
void GetTotalResult() {
	cout << "Merging." << endl;

	fstream in[10];
	for (int i = 0; i < 10; ++i) {
		string path = "result";
		path += "_" + to_string(i);
		in[i].open(path, ios::in);
	}
	
	fstream out("result", ios::out);

	vector<string> query(10);
	vector<int> count(10);

	bool bucket_has_been_read[10]; for (int i = 0; i < 10; ++i) {
		bucket_has_been_read[i] = true;
	}

	while (true) {
		for (int i = 0; i < 10; ++i) {
			if (bucket_has_been_read[i]) {
				if (in[i] >> query[i] >> count[i]) {
					bucket_has_been_read[i] = false;
				}
			}
		}
		
		int max_count_index = -1;
		for (int i = 0; i < 10; ++i) {
			if (!bucket_has_been_read[i]) {
				if (max_count_index == -1 || count[max_count_index] < count[i]) {
					max_count_index = i;
				}
			}
		}
		
		if (max_count_index != -1) {
			out << query[max_count_index] << " " << count[max_count_index] << "\n";
			bucket_has_been_read[max_count_index] = true;
		} else {
			break;  // 所有桶已清空。
		}
	}

	cout << "Done." << endl;
}

int main()
{
    DistributeQueriesIntoBucket();
	GetBucketResult();
	GetTotalResult();
}
