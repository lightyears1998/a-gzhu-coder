#include <iostream>
#include <string>
#include <list>
using namespace std;

struct student
{
	string name;
	int code;
};

int main()
{
	list<student> lst;
	
	// 创建student对象 
	student a {"Xiaoming", 01};
	student b {"Xiaoliang", 02};
	student c {"Xiaozhang", 03};
	student d {"Miss Li", 99};
	
	// 添加元素
	lst.push_back(c);                // c
	lst.push_front(a);               // a - c
	lst.push_back(d);                // a - c - d
	lst.insert(++lst.begin(), b);    // a - b - c - d
	
	// 创建迭代器 
	list<student>::iterator it = lst.begin();  // 相当于指向链表开头的指针 
	
	// 浏览元素
	while (it != lst.end())
	{
		cout << it->name << ' ' << it->code << endl;
		++it;  // 相当与指针后移一位 
	}
 	
 	cout << "--------------------------------" << endl;
 	
	// 删除元素
	lst.pop_back(); // 删除末尾第一个元素
	// lst.erase(--lst.end())  // 同样是删除末尾第一个元素 
	for (list<student>::iterator it = lst.begin(); it != lst.end(); ++it)
	{
		cout << it->name << ' ' << it->code << endl;
		// lst.erase(it)  删除it指向的元素 
	}
} 
