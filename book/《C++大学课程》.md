# 信息

《C++大学课程》这本书是kehao的

电子工业出版社2016年7月（原著第9版，Ninth Edition）

# 笔记

## 类

### 构造器

- **explicit** 禁用构造器形参的隐式类型转换

### 分离接口与实现

```cpp
// GradeBook.h
#include <string>

class GradeBook
{
public:
    explicit GradeBook(std::string);
    void setCourserName();
    std::string getCourseName() const;
    void displayMessage() const;
private:
    std::string courseName;
};

```

```cpp
// GradeBook.cpp
#include <iostream>
#include "GradeBook.h"

GradeBook::GradeBook(string name)
    : courseName(name)
{
    // ...
}

void GradeBook::setCourserName(string name) const
{
    // ...
}

```

### 链接

- [Deitel C++资源中心](http://www.deitel.com/cplusplus)
