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

枚举类型可用于创建符号常量（新的类型名和枚举量），可用枚举来定义switch语句中的符号常量。

```cpp
enum spectrum {red, orange, yellow, green, blue, violet, indigo, ultraviolet};

spectrum band = spectrum(3); // green

```

可以创建多个值相同的枚举量

每个枚举都有取值范围，可以将枚举变量中的任何整数值赋给枚举变量，即使这个值不是枚举值。

枚举的取值范围的计算：开区间，(min(比最小枚举值小的最大的2的幂次, -1), 比最大枚举值大的最小的2的幂次)

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

两者其一：在函数声明前附加inline，在函数定义前附加inline；可将内联函数放置于头文件中；同一个函数的所有内联定义都必须相同。

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

### 第9章：内存模型和名称空间

自给自足原则，包含防护原则

#### 包含防护（guarding）

```cpp
#ifndef THIS_HEADER_H_
#define THIS_HEADER_H_
// 类的定义

#endif

```

#### 存储持续性

- 自动储存持续性
- 静态存储持续性 自动默认初始化为0（零初始化）
- 线程存储持续性 thread_local
- 动态存储持续性 new/delete

编译期间执行常量表达式初始化，运行期间执行动态初始化。

#### 作用域与链接性

内部链接性在翻译单元内共享，外部链接性在翻译单元之间共享，无链接性为局部变量

- 文件作用域
- 函数原型作用域

#### register

显式地指明变量的储存性是自动的。

#### extern

单定义规则 在多个文件中使用到外部变量的情况下，只需在一个文件中包含该变量的定义，但在其他文件中要使用extern关键字来声明它。

#### static

修饰变量时，在文件作用域中表示内部链接性，在局部声明中表示静态储存持续性。

修饰函数时，可将函数的链接性设置为内部；静态函数将覆盖外部定义。

#### const

在全局变量中，用const修饰，等同于用const static进行修饰，表示内部连续性。

使用extern关键字修饰const表示外部连续性，此时所有用到该变量的翻译单元都必须使用extern关键字标记，同时只有一个文件可对其初始化。

#### 其他关键字

- *cv-限定符* const和volatile
- *mutable* 即使一个结构或类是const的，某个成员也可以被修改

#### 语言链接性

C语言链接性：
```cpp
extern "C" void spaff(int);
```

C++语言链接性：
```cpp
extern void spaff(int);
extern "C++" void spaff(int);

```

#### 动态储存分配

##### new

单值变量的列表初始化：
```cpp
int *pin = new int{ 6 };

```

new失败时引发std::bad_alloc，在旧的标准中返回空指针。

##### 定位new运算符（placement new）

手动指定分配的内存起点，而不是在堆中自动管理。不跟踪已使用哪些内存，不能使用delete删除。

```cpp
char buf[200];

int *p = new(buf) type_name;

```

#### 名称空间

区分声明区域，潜在作用域和作用域。

命名空间可以是全局的，也可以从属于另一个命名空间。

命名空间是开放的。

区分未限定的名称和限定的名称。

##### using

```cpp
using Jill::fetch;     // using声明
using namespace std;   // using编译指令

```

若使用using声明，局部名称将隐藏全局名称，但仍可使用作用域解析操作符。

using编译指令是可传递的。

可以**通过使用未命名的名称空间**来实现链接性为内部的静态变量。未命名的名称空间于全局变量类似，但不能使用using声明或using编译指令使它在其他位置可用。

例如，

```cpp
static int counts;
int other();

int main() {};
int other() {};

```

它采用命名空间的实现是：

```cpp
namespace
{
	int counts;
}
int other();

int main() {};
int other() {};

```

#### 内联名称空间

自动将内层的标识符放至外层作用域

```cpp
namespace X {
inline namespace Y {
void foo();
}  // namespace Y
}  // namespace X

```

### 第10章：类与对象

注意到定义于类声明中的函数都成为内联函数，也可以在类声明之外定义成员函数，使之成为内联函数。

```cpp
class Stock
{
private:
	void set_tot();
}

inline void Stock::set_tot()
{
	...
}

```

#### 构造函数和析构函数

```cpp

Stock stock("Nano Element", 2, 3);
Stock stock = ("Nano Element", 2, 3); // 可能会创建临时变量
Stock stock {"Nano Element", 2, 3};

```

可以使用列表初始化；

可以使用std::initialize_list的类，表示任意长度的列表。

#### 类作用域

像下面这样定义常量是不可行的，因为类的定义只是描述了对象的形式，并没有创建对象，也就没有存放值的空间。

```cpp
class Backery
{
private:
	const int Months = 12;
	double cost[Months];
}

```

做法是为类声明一个枚举类型，或者使用static来修饰

```cpp
class Backery
{
private:
	enum {Month = 12}; // 并不会创建类数据成员，即对象实例中不包含枚举
	double cost[Months];
}

```

```cpp
class Backery
{
private:
	static const int Months = 12;
	double cost[Months];
}

```

作用域内枚举可以防止名称冲突

```cpp

// 可能产生名称冲突
enum egg {Small, Medium, Large, Jumbo};
enum t_shirt { Small, Medium, Large, Jumbo};

// 下列枚举的作用域为类

enum class egg {Small, Medium, Large, Jumbo};
enum struct t_shirt {Small, Medium, Large, Jumbo};

egg choice = egg::Small;

```

作用域类枚举不能隐式转换为整型，可指定底层枚举类型。

```cpp
enum class : short pizza{Small, Medium, Large, XLarge};

```

### 第11章：使用类

不要返回指向局部变量和临时对象的引用。

#### 运算符重载

```cpp
class Time
{
public:
	Time opearator +(const Time&) const;
}

Time opearator +(double, const Time&) const;

```

1. 重载后的运算符至少有一个是用户定义的操作类型
2. 重载运算符不会改变结合性和优先级
3. 只能重载现有运算符
4. 不能重载sizeof运算符、成员运算符、成员指针运算符、作用域解析运算符、三元条件运算符、RTTI运算符以及强制类型转换运算符
5. 下列运算符只能通过成员函数重载：赋值运算符、函数调用运算符、下标运算符、通过指针访问类成员的运算符（->）

重载运算符需要小心二义性。

#### 友元

友元函数、友元类、友元成员函数

重载二元运算符常常需要友元

#### 创建友元函数

1. 将函数放置在类声明中，并使用*friend*修饰
2. 定义函数时，不使用*friend*修饰

即使友元函数在类中声明，但它不是类成员函数，不能通过成员运算符来调用。即使友元函数不是成员函数，但它与成员函数的访问权限相同。

只要在类外访问类的私有数据，就需要友元。

#### 类的自动转换和强制类型转换

自动转换在不兼容的类型中不发生。

1. **由其他类型转换**：接受一个参数的构造函数可以作为转换函数。*explicit*可以用于指定显式强制类型转换。
2. **转换成其他类型**：`operator int()` `operator double()` *explicit*可以用于指定显式强制类型转换。

### 第12章：类和动态内存分配

> “开始时还是正常的，但逐渐变得异常，最终导致了灾难性的后果。”

不能在类中初始化静态成员变量（声明只是描述如何分配内存，但不分配内存）；静态数据成员为const整型或枚举型除外。

#### 特殊成员函数

1. 默认构造函数 `Time() = default;`
2. 默认析构函数 
3. 复制构造函数 `Time(const Time &);` 逐个复制数据成员
4. 赋值运算符
5. 地址运算符

静态类成员函数，不能通过对象进行调用。

#### 在构造函数中使用new

如果使用new来初始化指针成员，则应该在析构函数中使用delete；new和delete必须相互兼容

#### 返回对象

编程陷阱预防：返回const对象

```cpp
// 如果为force的类型定义了operator +()
net = force1 + force2;
force1 + force2 = net;

```

#### 定位new运算符

定位new运算符不能与常规delete运算符配合使用，
删除对象时需要显式调用对象的析构函数。

#### 嵌套声明

在类中嵌套结构或类声明，可以使作用域仅限于类中。

#### 成员初始化列表和类内初始化

类中定义的const常量，可以初始化，但不能给它赋值。

只有构造函数可以使用成员初始化列表语法。

使用成员初始化列表的例子：
```cpp
Queue::Queue(int qs) : qsize(qs) {
	front = rear = NULL;
	items = 0;
}

```

成员初始化列表初始化的对象不仅仅限于常量；但常量和被声明为引用的类成员也必须使用成员初始化语法。

C++11的类内初始化允许初始化以更直观的形式初始化：
```cpp
class Classy
{
	int mem1 = 10;
	const int mem2 = 20;
}

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

**flags**

- setioflags(ios_base::fixed|ios::showpoint)
- setprecision(2)

文件IO **ofstream**

```cpp
ofstream fout = open(name);
fout.close();

```
