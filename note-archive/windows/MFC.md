# Micrsoft Foundation Class

采用C++编写，对Win32和COM API提供面向对象的包装器，早期名称Application Frameworks(AFX)。

MFC头文件`\atlmfc\include`，实现文件`\atlmfc\mfc\src`，根目录类似于`C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.15.26726`

MFC不适用于Windows RT（以Win8为代表的Metro UI）

源文件的后缀名为`cpp`

## Chapter 1 相关基本概念

- *Win32* includes *Win95* and *WinNT*
- *WinRT*
- *afx* Application Framework
- *sdi*, *mdi* Single / Mutiple document interface
- *ole* Object linking and embedded

### Static libarary and shared library

- Static library *.lib
- Shared library *.dll

### MFC库

包括各种字符集的版本、各种处理器架构的版本以及精简了控件的版本。

MFC库会根据设置[自动链接](https://docs.microsoft.com/zh-cn/cpp/mfc/mfc-library-versions#automatic-linking-of-mfc-library-versions)

[静态库命名约定](https://docs.microsoft.com/zh-cn/cpp/mfc/mfc-library-versions#mfc-static-library-naming-conventions) `uAFXcd.lib`

### 字符集

注意项目属性中的[字符集设定](https://docs.microsoft.com/zh-cn/cpp/mfc/mfc-library-versions#ansi-mbcs-and-unicode)

使用Unicode即使用UTF-16

多字节字符（char）与宽字节字符（w_char）

- 多字节 一个字符对应一个字节；注意到一个“字”可能由多个字节组成
- 宽字节 一个字符对应多个字节，一个“字”对应一个字节

### [文档、视图与框架](https://docs.microsoft.com/zh-cn/cpp/mfc/documents-views-and-the-framework)

- *文档* 类似于*\.docx*这样的，继承于`CDocument`
- *视图* 类似于文档中的按钮，继承于`CView`
- *框架* 视图显示于框架之中，继承于`CFrameWnd`，`CMDIFrameWnd`或`CMDIFChildWnd`
- *文档模板 Document Template*  `CSingleDocTemplate`, `CMultiDocTemplate`
- *The Application Object*
- *Thread Object* `CWinApp`继承于`CWinThread`

### CWinApp：应用程序类

可重载方法

- `InitInstance()`
- `Run()`
- `ExitInstance()`
- `OnIdle()`

#### InitInstance

- 中心工作：创建文档模板
- 从ini文件或注册表中读取设置，最近使用的文件等
- 注册文档模板
- （MDI）创建Main frame window
- 处理命令行

初始化正确返回`TRUE`

关于多线程的[一点注释](https://docs.microsoft.com/zh-cn/cpp/mfc/initinstance-member-function)

## 特殊的CWinApp服务

- 注册文件关联
- GDI+
- 文件拖放
- 追踪最近使用的文件

### 文档模板和文档-视图创建过程

<https://docs.microsoft.com/zh-cn/cpp/mfc/document-templates-and-the-document-view-creation-process>

### 类体系

层次结构图参见 <https://docs.microsoft.com/zh-cn/cpp/mfc/hierarchy-chart>

![简明类层次结构图](/camo/note/windows/hierarchy-chart.jpg)

## Chapter 1x 基础代码

### 编译环境

1. 项目属性中调整“MFC的使用”
2. 链接器选项中调整“子系统”

### 预编译头与头文件

- 头文件 `afxwin.h` 定义了包括CWinApp在内的类
- 标准预编译头 `stdafx.h`

### CWinApp

有且只有一个的应用程序类，并需要一个全局对象实例。

1. virtual `BOOL InitInstance()`
    1. 创建主窗口
    2. 显示窗口，更新窗口

2. `Run()` 执行应用程序的消息循环

3. `Idle()`

4. `ExitInstance()`

### 消息映射

1. 在处理该消息的类中使用消息宏`DECLARE_MESSAGE_MAP`声明对消息映射的支持，并在该宏之前声明消息处理函数
    ```cpp
    protected:
        afx_msg void OnPaint();
        DECALARE_MESSAGE_MAP()
    ```
2. 使用`BEGIN_MESSAGE_MAP`和`END_MESSAGE_MAP`在类声明之后的地方定义该类支持的消息映射入口点。其中`BEGIN_MESSAGE_MAP`的第一个参数用于指定支持消息映射的用户派生类，第二个参数指定派生类的基类。
    ```cpp
    BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
        ON_WM_PAINT()
    END_MESSAGE_MAP()
    ```
3. 声明函数原型和定义消息处理函数
    ```cpp
    // 省略函数原型声明
    void CMainFrame::OnPaint()
    {
        CPaintDC dc(this);
        CRect    rc;
        GetClientRect(&rc);
        dc.DrawText(...);
    }
    ```

### 基础框架

参见Playgroud / Chapter 1 / 1.4.2

## Chapter 2 对话框

从基类CDialog派生

- **模式对话框**是当对话框弹出时，用户必须在对话框中做出相应的操作，在退出对话框之前，对话框所在的应用程序不能继续执行。 `.DoModal()`
- 相对应的概念是 **无模式对话框** `Create(IDD_...)`, `ShowWindow(SW_SHOWNORMAL)` 注意非模态对话框不会阻塞代码，从而作为局部变量的引用时会“一闪而过”；非模态对话框应该作为类的成员，并且在`OnInitDialog()`中被初始化

消息

- `WM_INITDIALOG` 对话框显示之前向父窗口发送的消息

方法

- `DoModal()` 显示（和终止）模式对话框，返回`IDOK`, `IDCANCEL`等值
- `GetWindowText()`, `GetWindowRect()`
- `OnOK()`, `OnCancel()`

通过重写`OnOK()`方法来解决对话框按下回车之后就退出对话框的问题。

### 通用对话框

从`CCommonDialog`继承的一系列预定义通用对话框

- CColorDialog
- CFileDialog
- CFindReplaceDialog
- CPageSetupDialog
- CFontDialog
- CPrintDialog

CFileDialog使用示例

```cpp
void CMyFileDialogDlg::OnBnClickedShowdlg()
{
    CString filter = TEXT("文本文件(*.txt)|*.txt|C++文件(*.h, *.cpp)|*.h;*.cpp|所有文件(*.*)|*.*|");  // 真的是Filter
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter);
    if (dlg.DoModal() == IDOK)
    {
        m_path = dlg.GetPathName();   // 完全限定路径
        UpdateData(FALSE);
    }
}
```

### 关于消息对话框

- Win32`MessageBox()` 参数与MFC中的MessageBox不同
- `AfxMessageBox()` 全程函数
- `MessageBox()` 只能用在控件、对话框、窗口等一些地方

### 关联对话框资源到MFC类

在资源设计视图中使用“添加类”来添加MFC类

## Chapter 2x 窗口

`CWnd`封装了Windows窗口对象，如无特殊需求，使用`CFrameWnd`更方便，因为省略了注册窗口类的步骤，`CFrameWnd`预先注册好了。`CWnd`需要额外的注册窗口的步骤。

```cpp
class MyWnd : public CFrameWnd
{
public:
    MyWnd()
    {
        Create(NULL, TEXT("New Window"));
    }
};
```

调用`CreateEx()`方法之前会先调用`PreCreateWindow(CREATESTRUCT)`，可在此方法中修改窗口给的外观；最后调用`CreateWindowEx()`完成窗口的创建。

`OnCreate()`是对`Create()`方法产生的`WM_CREATE`消息的响应，不创建窗口，而是负责在窗口显示之前修改窗口的外观和位置等等。

## Chapter 3 常用控件

用于与用户进行交互的基本单元

创建控件的方式有主要有两种

1. 在对话框模板中用编辑器指定控件
2. 调用MFC相应控件类的Create()函数来创建

消息

- ON_COMMAND 控件的通用消息，如果定义了ON_COMMAND消息的处理函数和其他消息的处理函数，那么先调用ON_COMMAND的处理函数再调用其他消息的处理函数

方法

- CWnd.`GetDlgItem(nId)` 通过控件id获取控件的类对象指针
    ```mfc
    CButton * pBtn = (CButton *) GetDlgItem(IDC_BUTTON1);
    ```
- `GetWindowsText(nId)`
- `EnableWindow(BOOL)` 是否启用窗口
- `Invalidate()` 使窗口无效，系统将重绘窗口

### 动态创建控件示例

现在类向导中为添加控件成员变量，并在`OnInitDialog()`中添加初始化代码

```cpp
// 很丑，外观与众不同
m_button.Create(TEXT("动态创建的按钮"), WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP, CRect(20, 20, 120, 40), this, 201);
// 设置字体之后好多了
m_button.SetFont(this->GetFont());
```

### DDX和DDV

- *Dynamic Data Exchange, DDX*
- *Dynamic Data Validate, DDV*

`UpdateData()` 先TRUE后FALSE即可取得数据后设置数据

- 使用`UpdateData(TRUE)`或`UpdateData()`时，数据由控件向绑定的成员变量（Data）输出
- 使用`UpdateData(FALSE)`时，数据由成员变量向绑定的控件输出
- 读作Update data from dialog

### 静态控件

静态控件包括：静态文本，分组框以及静态图片

#### 静态文本

1. 可以通过关联变量来设置静态文本，注意ID不能以`STATIC`结尾，否则无法添加变量
2. 可以通过`GetDlgItem(IDD)`

通过`SetWindowText()`来修改显示的Caption，通过`GetWindowText(CString&)`来获取Caption

甚至可以通过静态文本控件显示图片，通过`SetBitmap()`。

### 按钮

- 风格包括标准按键按钮和默认按钮（通过Default Button属性调整）；可以将多个按钮设置为默认按钮，但最终只有一个会成为默认按钮
- 单选按钮，分为一般按钮和自动按钮；自动类型保证同组的单选按钮至多只有一个可以被选中；在同一个组框中的单选按钮会自动成为关联的一组
- 复选按钮，三态按钮（Tri-state）

消息

- *BN_CLICKED*
- *BN_DOUBLE_CLICKED*

方法

- `SetCheck(nCheck)`, `GetCheck()` `nCheck`可以是0不选，1选中和2不确定（仅适用于三态按钮）
- 对于单选按钮组的设定和选取 `CheckRadioButton(nIdFirstButton, nIdLastButton, nIdCheckButton)`, `int GetCheckedRadioButton(nIdFirstButton, nIdLastButton)`
- `EnableWindow(FALSE)` 可以禁用窗口

### 编辑框和旋转按钮控件

#### 编辑框控件

编辑框可以多行

方法

- `SetPasswordChar(ch)` ch为0时取消设置密码字符
- `SetSel()`, `ReplaceSel()`, `GetSel()` 选择文本
- `SetMargins(nLeft, nRight)` 设置边距
- `Copy()`, `Paste()`, `Cut()`, `CanUndo()`, `Undo()`

#### 获取多行编辑框文本示例

可以使用DDX/DDV

可以结合`GetLineCount()`, `GetLineLength(m_Edit.LineIndex(1))`, `GetLine(nLine, sBuff, nCharCount)`

注意`GetLine()`不会自动添加结尾的空字符

#### 旋转按钮控件 Spinner

使用TAB次序将旋转按钮控件和编辑框控件编组

旋转按钮控件是一对箭头按钮

属性

- `Auto Buddy` 自动伙伴属性
- `Set Buddy Integer` 设置结伴证书

方法

- `SetRange(nLower, nUpper)` 改变最大值和最小值
- `SetBase(nBase)` 改变数字基数
- `SetPos(nPos)` 当前数值

### 列表框 CommoBox

有单选、多选、拓展多选以及非选四种类型。

方法

- `AddString(lpszItem)`, `InsertString(nIndex, lpszItem)` 添加列表项目，成功时返回索引，失败时返回`LB_ERR`
- `SetItemData(nIndex, dwItemData)`, `SetItemDataPtr(nIndex, pData)` 将列表项目与特定内容相关联
- `GetItemData()`, `GetItemDataPtr()`
- `DeleteString(nIndex)`, `ResetContent()` 删除字符串
- `FindString(nStartAfter, lpszItem)`, `FindStringExact(nIndexStart, lpszItem)` 开始位置若为-1则从头到尾搜寻，查找列表项目，失败返回`LB_ERR`
- `GetCurSel()`, `SetCurSel()` 设置单项选择列表框的选中选项，可以通过此函数来设置默认的值
- `GetText(nIndex, lpszBuffer)`, `GetText(nIndex, rString)`

多项选择列表框的需要响应`LBN_SELCHANGE`消息并利用`GetSelCount()`获取选中项目的数量, `GetSelItem(nCount, buffer)`获取选中项目的索引来处理。

#### 单选式下拉框 Commobox

在Data属性中使用分号分隔各个选项；Type“Drop List”属性可以使下拉框内容不能被用户修改；Sort“False”则不会自动排序

### 组合框

简单组合框、下拉式组合框和列表框

### 进度条、滚动条和滑动条

#### 进度条

方法

- `SetRange()`, `SetPos()`, `SetStep()`, `StepIt()`

#### 滚动条

方法

- `SetScrollRange(nMinPos, nMaxPos, bReDraw = TRUE)`, `SetScrollPos()`

消息

- `WM_HSCROLL`, `WM_VSCROLL`

#### 滑动条

- `SetRange()`, `SetPos()`
- `SetTic()`, `SetTicFreq()`, `ClearTic()` 刻度线相关设置
- `SetSelection(nMin, nMax)`

### 日期时间控件

- `SetTime()`, `GetTime()`

### 列表控件和树控件

#### 图像列表 ImageList

不能通过可视化编辑器创建；是在树控件中引用图片中所必须的。

#### 列表控件 List Control

大图标、小图标、列表视图和报表视图4中风格。

方法

- `SetImageList()` 设置关联的图像列表
- `InsertItem()`, `DeleteItem()`, `DeleteAllItems()`
- `FindItem()`
- `GetColumnCount()`, `InsertColumn()`

##### 报表模式

- 整行的选中状态 `SetExtendedStyle(.GetExtendedStyle() | LVS_EX_FULLLINESELECT)`
- 显示网格 `LVS_EX_GRIDLINES`

#### 树控件 TreeControl

属性

- HasLine, HasButton
- RootAtLine

方法

1. `SetImageList()` 设置图标；注意ImageList不要开辟在栈空间中否则函数创建函数结束之后其控件会释放导致图片无法加载
2. `HTreeItem InsertItem()` 设置节点
3. `SetSelectedItem(hTreeItem)` 设置默认选项; `GetSelectedItem()`
4. `GetItemText()`

事件

- TVN_SELECTCHANGED

#### 标签页 TabControl, TabSheet

基于对话框资源的深度定制

## Chapter 4 菜单、工具栏和状态栏

使用CMenu类的`CreateMenu()`, `CreatePopupMenu()`来创建菜单，使用`LoadMenu()`装入菜单资源，使用`AppendMenu()`, `InsertMenu()`来添加菜单项

### 右键菜单（快捷菜单）

1. 定义框架类的`OnContextMenu(CWnd * pWnd, CPoint point)`的函数

注释

1. `OnContextMenu()`响应的是鼠标右键按下后弹起的消息，因此如果定义`OnRButton`函数，并且有模态对话框出现，则此函数不会执行
2. `OnContextMenu()`中不需要使用`ScreenToClient()`转换坐标

## Chapter 5 框架窗口、文档和视图

框架窗口用于文档和视图的容器；文档是一个数据单元；视图是框架窗口的子窗口

### Section 1 框架窗口

应用程序只能有一个主框架窗口；对于多文档程序，文档窗口是主框架窗口的子窗口。

#### 窗口样式

以`WS_`开头定义的常量

### Section 2 文档和文档模板

文档模板用于建立资源、文档类、视图类和若存在的子框架窗口类之间的关联

```cpp
CSingleDocTemplate* pDocTemplate;
pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,                   // 资源类
    RUNTIME_CLASS(CMyDoc),           // 文档类
    RUNTIME_CLASS(CMainFrame),       // 主框架窗口类
    RUNTIME_CLASS(CMyView));         // 试图类
```

### 文档序列化 CArchieve类

### Section 3 视图

视图应用框架CView如`CEditView`, `CFormView`等

## Chapter 6 图形、文本和打印

绘制基于图形设备环境，任何从CWnd派生而来的对话框、控件和视图等都可以作为绘图设备环境。

MFC中的CDC类对绘图设备环境进行封装，提供画点、线、多边形、位图以及文本的操作。

一般绘图代码添加到`OnPaint()`和`OnDraw()`虚函数中。

### Section 1 图形

注意所有的Device Context函数必须在`OnPaint()`方法中调用，在其他函数中调用是无效的。

#### CDC Device Context 设备环境类

派生类具有实用功能

#### `OnDraw` vs `OnPaint`

两个方法不要同时存在，否则`OnPaint`会把`OnDraw`覆盖（名字长的覆盖名字短的（实际上是自定的OnPaint()方法没有调用OnDraw虚函数

- `OnPaint()`是CWnd类的成员，负责响应`WM_PAINT`消息
- `OnDraw()`是CView的成员函数，没有响应消息的功能

视图无效之后，发送`WM_ONPAINT`消息，由视图的`OnPaint()`方法创建CPaintDC对象来响应响应消息并调用视图的OnDraw成员函数（因为OnPaint最后要调用OnDraw，一般在OnDraw中进行绘制）

通常不需要编写OnPaint处理函数，当在CView视图类中添加了`OnPaint()`处理函数时，`OnPaint()`会覆盖掉`OnDraw()`

#### 坐标映射

通过坐标映射实现高DPI适应

### Section 2 文本

### Section 3 打印

## 常用工具类

### 一般辨识

- Visual Studio 类视图
- 以`Ex`是拓展函数
- 以`AFX`开头的是全局函数；一个例子是`MessageBox()`是CWnd的方法，而`AfxMessageBox()`

### 宏

- `HIBYTE()`, `LOBYTE()` 16位数值中的高位和低位
- `TEXT()` UNICODE字符支持
- `MAKEWORD()` 将两个16数值合成32位数值

TCHAR 自适应编码转换字符

wchar_t配套方法`wcslen()`

### 工具类

#### CString

有`CStringA`的变体

方法

- `CString(char *)` 由`char *`构造对象
- `Format()` 与printf()类似的格式化字符串的方法；由字符串转换成数值可以使用`atoi()`
- `GetBuffer()` 返回`char *`，此方法作为`std::string`与`CString`转换的桥梁

#### CPoint, CSize, CRect

#### CPaintDC

#### CFile

有`CStdioFile`的子类支持文件输出

创建文件的模式 `CFile::modeXXX`

使用`Write()`正确地输出`CString`的方法 `Write(str.GetBuffer(), sizeof(TCHAR) * str.GetLength());`

#### CStdioFile

本质上是对C的函数`fopen()`对应结构的封装，封装了`WriteString()`和`ReadString()`方法，注意两个版本的`ReadString()`对换行符的不同处理；

#### CImageList

1. 创建图片集合

```cpp
CImageList list;
list.Create(...);  // 创建（开辟空间）
list.Add(...);  // 添加具体的图像，可以是HICON
```

### 处理键盘输入

基于对话框的工程默认不能处理键盘输入

参考

- <https://blog.csdn.net/wwkaven/article/details/39935915>

## 参考资料

### API索引

<https://docs.microsoft.com/zh-cn/cpp/mfc/reference/mfc-classes>

### 手册

- [Microsft基础类：MFC和ATL](https://docs.microsoft.com/zh-cn/cpp/mfc/mfc-and-atl)
- [创建MFC应用程序的一般工作流程](https://docs.microsoft.com/zh-cn/cpp/mfc/sequence-of-operations-for-building-mfc-applications)

## 指南

- [黑马程序员MFC教程](https://www.bilibili.com/video/av20005978/)
