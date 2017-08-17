# 安装和配置

Visual Studio是一个功能全面的集成开发环境。
微软为学生提供了免费的Visual Studio： Visual Studio Community。

在微软的官方网站可以获得最新的[VS Community](https://www.visualstudio.com/zh-hans/free-developer-offers/)。截至17年8月，最新版本是Visual Studio 2017 Community。

Visual Studio支持C/C++、C#等多种编程语言。要利用Visual Studio Community编译C/C++的源代码，需要安装3个组件：

* **Visual C++核心功能** 勾选此项，才能在Visual Studio中新建C/C++项目。

* **VC++ 工具集(x86,x64)** 包含使用MSVC编译器编译C++源代码必须的头文件和其他依赖，缺少此项可能无法编译C++语言的程序（以VC++ 2017 v141 工具集为例，我们熟悉的iostream头文件位于C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.11.25503\include\iostream）

* **Windows SDK** 包含使用MSVC编译器编译C源代码必须的头文件和其他依赖，缺少此项可能无法编译C语言程序（以Windows 10 SDK 15063为例，我们熟悉的stdio.h头文件位于C:\Program Files (x86)\Windows Kits\10\Include\10.0.15063.0\ucrt\studio.h）

其他项目都不是必须的。
如果选择使用工作负载中的“Visual C++的桌面开发”，一般会自动安装上面的三个组件，同时为你安装一些可选功能，Simple and easy~

# 编译和运行

Visual Studio使用“解决方案”(solution)和“项目”(project)来管理源代码。
简单地说，“解决方案”可以包含多个“项目”，一个“项目”可以是C/C++项目，也可以是C#项目、Python项目。“项目”必须放在“解决方案”中。

为了运行我们的代码，我们需要新建一个C/C++项目，添加自己的代码，然后编译它。

我们可以一步到位创建C/C++项目和包含它的解决方案。
从工具栏中选择 “文件” -> “新建” -> “项目...”，这会打开新建项目窗口。展开窗口左边的“Visual C++”节点，选择节点下的“通用”，在右侧选择“空项目”。选择一个你喜欢的名字然后确认。

![一步到位创建解决方案和项目](https://blog.qfstudio.net/wp-content/uploads/2017/08/gzhu-coder-creating_solution_and_projecgt.png)

接下来添加代码文件。
在“解决方案资源管理器”（如果你看不到它，在工具栏上点击“视图”，再点击“解决方案资源管理器”它就会跑出来啦）中对在项目标签上点击右键，然后选择 “添加” -> “新项目”，在创建新项目的窗口中展开“Visual C++”节点，选择“代码”标签，在右侧窗口中选择“C++源文件(.cpp)”，给它一个你喜欢的名字，然后确认。（如果要创建C语言文件，可以将后缀名从cpp改为c）

![添加代码文件1](https://blog.qfstudio.net/wp-content/uploads/2017/08/gzhu-coder-creating_source_file.png)

![添加代码文件2](https://blog.qfstudio.net/wp-content/uploads/2017/08/gzhu-coder-creating_source_file_c.png)

在代码编辑器中输入你的代码，这里有一些可以参考的代码，可以帮助你测试VS是否被正确配置。

C语言：

```c
#include <stdio.h>

int main(void){
	printf("Hello Visual Studio.");
	getchar();
	
	return 0;
}

```

C++语言：

```cpp
#include <iostream>

int main(){
	std::cout<<"Hello Visual Studio.";
	std::getchar();

	return 0;
}
```

源代码需要编译才能运行，在VS中，可以通过构建项目完成对源代码的编译。
在工具栏中选择“构建”，然后“构建解决方案”。

构建解决方案之后可以以调试模式运行程序。
在工具栏中选择“调试”，然后“现在开始调试”；或者直接使用“本地调试”。

如果一切顺利，应该可以看见程序运行的命令行窗口。

如果遇到问题，请参考下面的内容。也可以给我issue或者通过其他途径联系我，虽然不一定能解决问题，但我一定尽力帮忙。


# 可能遇到的问题

## 已经安装了三项必需组件，但不能编译C/C++项目

之前没有安装必需组件就建立了解决方案和C/C++项目，再启动Installer安装必需组件后发现原有的解决方案仍然不能编译。

### 原因

解决方案没有使用新添加的组件。

### 解决

最简单的办法是建立新的解决方案。

## 编译器忽略了需要编译的源代码

构建项目时输出窗口没有显示源代码被编译，但没有出现构建错误，并且在运行（调试）时提示找不到目标文件。

### 原因

我的理解是，Visual Studio通过添加文件时选择的文件类型判断文件类型。
向项目添加源代码时，必须选择正确的文件类型。
（如果添加源文件时使用的后缀名是txt，即使之后将txt改为c或cpp，编译器也不会对它进行编译。）

### 解决

如果通过添加“新文件”的方式向项目中添加文件，确保选择了正确的文件类型或者输入正确的后缀名。
例如，添加C++源文件需要选择的文件类型是“C++文件(.cpp)”

如果通过添加“存在的文件”的方式向项目中添加文件，源文件必需具有c或cpp后缀名。

## UTF8中含有中文字符时，源文件不能编译而代码感知无错误提示

在我的电脑上，版本15.3.0的Visual Studio编译器不能正确处理以无BOM的UTF-8编码的文件。
如果你的代码使用无BOM的UTF编码保存，并且在代码中含有中文字符，即使代码编辑器没有检查出错误，也很可能会在编译期间出现一些莫名其妙的错误。
这些错误主要围绕在中文字符附近，可能是……它想学习中文吧。其中一个明显的错误是：

> Warning	C4819:	The file contains a character that cannot be represented in the current code page (936). Save the file in Unicode format to prevent data loss	Compatibility	c:\users\light\documents\visual studio 2017\projects\compatibility\source\day1-ex1-clargsreq-brhole.c	1	

### 原因

我的理解是，MSVC编译器依靠UTF8编码前面的BOM标记来识别UTF8编码。当UTF8编码的文件不带有BOM标记时，MSVC编译器将文件识别的本地操作系统的编码，也就是gb2312编码。这种情况下，MSVC编译器不能正确识别在中文符后面的换行符。

### 解决

以带BOM的UTF8编码重新保存文件。

选择工具栏中的“文件” -> “另存为...” -> 在“保存”按钮的下拉菜单中选择“以其他编码保存”，然后选择“带签名的UTF8 - 代码页65001”编码。

![另存为](https://blog.qfstudio.net/wp-content/uploads/2017/08/gzhu-coder-save-as.png)

![以其他编码保存](https://blog.qfstudio.net/wp-content/uploads/2017/08/gzhu-coder-save-as-advanced.png)
