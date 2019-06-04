#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>

using namespace std;


// 使用除留余数法和线性探查法的哈希表
// 不能插入负数
class HashTable
{
private:
    int size;
    int *table;

    // 获取number在除留余数法中定义的哈希表键key
    int getKey(int number)
    {
        return number % size;
    }

    // 获取当前key在线性探查法中定义的相邻的下一个key
    int getNextKey(int key)
    {
        return (key + 1) % size;
    }

public:
    HashTable(int size) {
        assert(size > 0);
        this->table = new int[size];
        this->size = size;
        memset(this->table, -1, sizeof(int)*size);
    } 

    ~HashTable() {
        delete[] table;
    }


    // 向哈希表中插入number
    void Insert(int number) {
        int key = getKey(number);
        while (table[key] != -1 && table[key] != number) {
            key = getNextKey(key);
        }
        table[key] = number;
    }


    // 查找哈希表中是否存在number
    void Find(int number) {
        int key = getKey(number);
        while (table[key] != -1 && table[key] != number) {
            key = getNextKey(key);
        }
        if (table[key] == number) {
            cout << "302 - Found number " << number << " at key " << key << "." << endl; 
        }
        else {
            cout << "404 - Number " << number << " not found." << endl;
        }
    }    


    // 展示哈希表
    void Show() {
        cout << '[' << size << ']' << ' ';
        for (int i = 0; i < size; ++i) {
            cout << table[i] << ' ';
        }
        cout << endl;
    }
};


// 生成随机数
vector<int> Generate10RandomNumbers()
{
    vector<int> random_numbers;
    for (int i = 0; i < 10; ++i)
        random_numbers.push_back(rand());
    return random_numbers;
}


// 打印数字
void ShowNumbers(vector<int> numbers)
{
    for (int number : numbers)
    {
        cout << number << ' ';
    }
    cout << endl;
}



int main()
{
    vector<int> random_numbers(Generate10RandomNumbers());
    
    cout << "产生的随机数为：" << endl;
    for (int number : random_numbers) {
        cout << number << ' ';
    }
    cout << endl;

    HashTable hash_table_length_13(13);
    HashTable hash_table_legnth_15(15);

    cout << "对表长度为13的哈希表：" << endl;
    for (int number : random_numbers) {
        hash_table_length_13.Insert(number);
        hash_table_length_13.Find(number);
    }
    hash_table_length_13.Show();

    cout << "对表长度为15的哈希表：" << endl;
    for (int number : random_numbers) {
        hash_table_legnth_15.Insert(number);
        hash_table_legnth_15.Find(number);
    }
    hash_table_legnth_15.Show();
}
