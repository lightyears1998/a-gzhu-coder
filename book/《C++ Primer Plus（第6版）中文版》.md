## 信息

人民邮电出版社2012年7月第1版

## 笔记

### 第3章：处理数据

- 常量表 `climits`

#### 转义序列

- `\ooo`
- `\xhhh`
- Unicode `\u00000000`
- ISO 10464 `\U0000000000000000`

#### wchar_t、char16_t和char32_t

宽字符常量和宽字符串L前缀

```cpp
wchar_t bob = L'P';
wcout << L"tall" << endl;

char16_t ch1 = u'q';
char32_t ch2 = U'\U0000222B';
```

#### 强制类型转换

```cpp
(type)name
type(name)

static_cast<type>(name)

```

### 第4章：复合类型

列表初始化数组时可以省略等号，可不在大括号内包含任何东西即可将所有元素置零。

#### 字符串类型

c-string:

- strcat();
- strcpy();

string:

+
+=

#### 原始字符串

默认定界符 `R"(... )"`

自定义定界符可在默认定界符之间加入除空格、括号、斜杠、控制字符（制表符等）之外的任意字符。
例如 `R"+*(... )+*"`

字符串前缀的组合顺序任意

#### 位字段

```cpp
struct torgle_register
{
	unsigned int SN: 4;
	unsigned int   : 4; // 不使用的位
	bool goodIn    : 4;
	bool goodTorgle: 4;
};

```

#### 共用体/联合

匿名共用体：

```cpp
struct widget
{
	char brand[20];
	int type;
	union
	{
		long id_num;
		char id_char[20];
	}
}
``` 

#### 枚举

```cpp
enum spectrum {red, orange, yellow, green, blue, violet, indigo, ultraviolet};

spectrum band = spectrum(3); // green

```

#### 指针

小心：
```cpp
int* p1, p2;
int *p1, *p2;

```

方括号数组表示法/指针表示法

#### new & delete

- 使用delete[]释放new[]申请的内存
- 不要释放已经释放的内存
- 对空指针使用delete是安全的。

#### Vector, Array

中括号语法不检查下标越界，成员函数at()检查下标越界

### 第5章：循环和关系表达式

使用术语“顺序”代替“顺序点”。

延时循环：
```cpp
int sec; cin >> sec;
clock_t start = clock();
clock_t delay = sec * CLOCKS_PER_SEC;
while (clock() - start < delay) continue;
cout << "Done." << endl;

```

范围循环：
```cpp
for (int x : {3, 5, 7, 9, 11})
{
	cout << x << endl;
}

```

### 第6章：分支语句和逻辑运算符

生产环境中的bool表达式 `value == varible`

### 第7章：函数——C++的编程模块

"容忍逻辑上无法自圆其说的观点正是人类思维活动的特点"

### 第8章 函数探幽

#### 内联函数

两者其一：在函数声明前附加inline，在函数定义前附加inline

#### 函数参数与临时变量、引用参数和const

仅当参数为const引用时，才生成临时变量。

#### 函数模板

```cpp
template <typename T>
void swap(T &a, T &b) { };

```

实例化是编译器为函数模板生成具体代码的过程，具体化是编写函数模板的过程。

显式实例化在函数原型声明中以template修饰，显示具体化在函数原型中以template<>修饰。

显式具体化和显式实例化
```cpp
// 非模板形式
void swap(job &a, job &b) { };

// 模板形式
template <typename T>
void swap(T &a, T &b) { };

// 显式具体化形式
template <> void swap(job &a, job &b) { };
template <> void swap<job>(job &a, job &b) { };

// 显式示例化声明
template void swap<int> (int, int);

```

编译器确认可行函数的过程：完全匹配和最佳匹配、提升转换、标准转换、用户定义转换。“最具体”指找到可行函数需要的转换最少。

引导编译器做出选择：在模板函数和非模板函数同时存在时，`lesser<>()`引导编译器选择模板函数版本而不是非模板函数。

#### decltype

用于确认变量的类型：
```cpp
template <typename T1, typename T2>
void ft(T1 x, T2 y)
{
	decltype(x+y) xpy = x + y;
}
```

结合后置返回类型声明函数的返回类型：
```
template <typename T1, typename T2>
auto h(T1 x, T2 y) -> decltype(x + y)
{ /* 函数体 */ };


##### decltype确认类型的顺序

1. 对于没有使用括号的标识符，与标识符的类型相同
2. 对于函数调用，与函数的返回值类型相同
3. 对于左值，为指向其类型的引用
4. 对于表达式，与表达式的类型相同

```cpp
double xx;
decltype((xx)) w; // double &
decltype(xx)   u; // dooble

```

### 附：输入输出工具

**cin**;

- `getline(buf, num)` 丢弃换行符
- `get(buf, num)` 换行符留在输入队列中
- `get()` 读取一个字符
- `clear()`
- `fail(), eof()` 检测到EOF后，cin的failbit和eofbit都置1；

get()（不是getline()）读取空行后设置失效位(failbit)

get(), getline()输入行的字符比指定容量多时，将设置失效位

```cpp
cin.get(name, ArSize).get();

```

**cout, wcout**;

- `put()`
- `setf(ios_base::fixed, ios_base::floatfield);`

文件IO **ofstream**

```cpp
ofstream fout = open(name);
fout.close();

```
