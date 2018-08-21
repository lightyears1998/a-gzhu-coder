# Micrsoft Foundation Class

采用C++编写，对Win32和COM API提供面向对象的包装器

MFC头文件`\atlmfc\include`，实现文件`\atlmfc\mfc\src`，根目录类似于`C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.15.26726`

MFC不适用于Windows RT（以Win8为代表的Metro UI）

## 相关基本概念

- *Win32* includes *Win95* and *WinNT*
- *WinRT*
- *afx* Application Framework
- *sdi*, *mdi* Single / Mutiple document interface
- *ole* Object linking and embedded

### Static libarary and shared library

- static library *.lib
- shared library *.dll

### MFC库

包括各种字符集的版本、各种处理器架构的版本以及精简了控件的版本。

MFC库会根据设置[自动链接](https://docs.microsoft.com/zh-cn/cpp/mfc/mfc-library-versions#automatic-linking-of-mfc-library-versions)

[静态库命名约定](https://docs.microsoft.com/zh-cn/cpp/mfc/mfc-library-versions#mfc-static-library-naming-conventions) `uAFXcd.lib`

### 字符集

注意项目属性中的[字符集设定](https://docs.microsoft.com/zh-cn/cpp/mfc/mfc-library-versions#ansi-mbcs-and-unicode)

使用Unicode即使用UTF-16

### [文档、视图与框架](https://docs.microsoft.com/zh-cn/cpp/mfc/documents-views-and-the-framework)

- *文档* 类似于*\.docx*这样的，继承于`CDocument`
- *视图* 类似于文档中的按钮，继承于`CView`
- *框架* 视图显示于框架之中，继承于`CFrameWnd`，`CMDIFrameWnd`或`CMDIFChildWnd`
- *文档模板 Document Template*  `CSingleDocTemplate`, `CMultiDocTemplate`
- *The Application Object*
- *Thread Object* `CWinApp`继承于`CWinThread`

### 基于框架的生成：典型构建顺序

<https://docs.microsoft.com/zh-cn/cpp/mfc/sequence-of-operations-for-building-mfc-applications>

### CWinApp：应用程序类

可重载方法

- `InitInstance()`
- `Run()`
- `ExitInstance()`
- `OnIdle()`

### InitInstance

- 中心工作：创建文档模板
- 从ini文件或注册表中读取设置，最近使用的文件等
- 注册文档模板
- （MDI）创建Main frame window
- 处理命令行

关于多线程的[一点注释](https://docs.microsoft.com/zh-cn/cpp/mfc/initinstance-member-function)

## 特殊的CWinApp服务

- 注册文件关联
- GDI+
- 文件拖放
- 追踪最近使用的文件

## 链接

- [Microsft基础类：MFC和ATL](https://docs.microsoft.com/zh-cn/cpp/mfc/mfc-and-atl)
