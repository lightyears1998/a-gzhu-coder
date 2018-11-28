# Win32 API参考

- [API完整索引](https://docs.microsoft.com/zh-cn/windows/desktop/api/index)
- [新手入门](https://docs.microsoft.com/en-us/windows/desktop/learnwin32/learn-to-program-for-windows)

## Chapter 1 [数据类型](https://docs.microsoft.com/zh-cn/windows/desktop/LearnWin32/windows-coding-conventions)

### 匈牙利命名法

`m_`, `g_`, `l_` 成员、全局和局部函数

- 'n' / 'i' = INT
- 'l' = LONG
- 'u' = UNSIGNED
- 'ch' = CHAR
- 'b' = BOOL
- 'f' = FLOAT
- 'd' = DOUBLE
- 'w' = WORD(2 bytes) / UNSIGNED SHORT
- 'dw' = DWORD(4 bytes) / UNSIGNED LONG
- 'p' = pointer
- 'lp' = long pointer
- 'lpsz' = long pointer to string that is zero-terminated / LPSTR

此外还有

- `fn` 函数
- `wparam`, `lparam` word or long as parameter
- `cb` count bytes

### HANDLE句柄

- *INVALID_HANDLE_VALUE*
- `GetStdHandle()` `STD_INPUT_HANDLE`, `STD_OUTPUT_HANDLE`

### WINAPI

__stdcall参数的传递顺序，从右到左压入堆栈，并且在函数返回前清空堆栈

**HWND**形似指针，但不是指针

## Chapter 2 基本概念

### 窗口Window

- 占据一定的屏幕空间
- 在给定时间内可见或不可见
- 具有绘制自己的方法
- 能够处理来自用户或操作系统的输入

### 应用程序入口WinMain

签名如下

```cpp
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow);
```

wWinMain

```cpp
int WINAPI wWimMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);
```

如果无法生成，检查链接器的系统设定中的“子系统”项目。

若出现未加载符号的提示，在调试选项中选择加载符号即可。

- *hInstance* 指向实例的指针，操作系统用此区分加载到内存中的应用程序
- *hPrevInstance* 无意义，总是0；源自16位Windows操作系统
- *pCmdLine* 命令行参数
- *nCmdShow* 最小化、最大化或正常显示

操作系统不会使用WinMain的返回值

### 窗口类WNDCLASS

每个窗口都需要与一个窗口类相关联；窗口类并非C++中的“类”，而是操作系统使用的一种数据结构

可以将窗口类的多数字段留空以保持默认选项，但必须填写3个字段

1. `lpfnWndProc` 窗口过程函数
2. `hInstance` 应用程序实例句柄
3. `lpszClassName` 窗口类的名称，在线程中保持唯一即可；注意不要与预定义的控件类等的名称冲突

然后使用`RegisterClass(&wc)`注册窗口。

调用`CreateWindowEx(...)`来创建窗口；此函数在`CreateWindow()`的基础提供更多拓展。

创建完毕后使用`ShowWindow(hwnd, nCmdShow)`来显示窗口。

其他属性

1. cbClsExtra, cbWndExtra 为类或窗口分配的额外内存
2. hbrBackground
3. hCursor
4. hIcon

### 窗口消息Window Message

以`WM_`开头的宏定义是窗口消息

通过`GetMessage(&msg, NULL, 0, 0)`来获取消息队列中的消息，如果消息队列中没有消息，此函数会被阻塞。

获取到消息后，通过`TranslateMessage(&msg)`来翻译键盘消息，并通过`DispatchMessage(&msg)`来调用窗口过程函数。

通过`PostQuitMessage(0)`来发送`WM_QUIT`消息，使应用程序退出消息循环。

关于 **Post Message** 以及 **Sent Message**

```quote
The terminology for this distinction can be confusing:

- Posting a message means the message goes on the message queue, and is dispatched through the message loop (GetMessage and DispatchMessage).
- Sending a message means the message skips the queue, and the operating system calls the window procedure directly.
```

### 窗口过程Window Procedure

使用默认的窗口过程函数`return DefWindowProc(hwnd, uMsg, wParam, lParam);`

### 绘制窗口

`WM_PAINT`消息通知窗口更新区域

使用`BeginPaint(hwnd, &ps)`填充PAINTSTRUCT并获得hdc句柄，使用`EndPaint()`结束绘制

### 关闭窗口

接受到`WM_CLOSE`消息后可以选择提示用户是否真的关闭窗口，如果窗口过程返回0，操作系统不会关闭窗口

使用`DestroyWindow()`来关闭窗口

`WM_DESTROY`在窗口被销毁之后，其他析构开始（如，子窗口的销毁）之前调用，此时通常选择`PostQuitMessage()`来退出消息循环

### 应用程序状态

`WM_NCCREATE`以及`WM_CREATE`在窗口创建之前调用，可用于初始化UI。

具体参考　<https://docs.microsoft.com/en-us/windows/desktop/learnwin32/managing-application-state->

## Chapter 3 创建窗口的基本过程

1. 设计窗口 WNDCLASS
2. 注册窗口 `RegisterClass()`
3. 创建窗口 `CreateWindow()`
4. 显示和更新窗口
5. 取出消息 翻译消息 分发消息
6. 销毁窗口

## Chpater X 重要API

### windows.h

同时引入了

- `windef.h` 基本类型定义
- `winbase.h` 内核函数
- `wingdi.h` 图形设备接口函数
- `winuser.h` 用户接口函数，包括`MessageBox()`

### winuser.h

#### LoadIcon

`LoadIcon(HINSTANCE hInstance, LPCSTR lpIconName)`

- *hInstance* 加载标准图标时必须为`NULl`
- *lpIconName* 图标名称

### LoadCursor

`LoadCurcosr(HINSTANCE hInstance, LPSTR lpCursorName)`

- *hInstance* 加载标准Cursor时需要为空
- *lpCursorName* Cursor名称

### GetMessage

从当前Thread线程的消息队列中获取一个消息

```cpp
while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);  // 翻译某些键盘消息
    DispatchMessage(&msg);   // 发送至窗口过程
}
return msg.wParam;
```

### `GetSystemMetrics()`

获取系统设定相关数值

### [MessageBox](https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-messagebox)

`MessageBox(HWND hParent, LPCSTR lpText, LPCSTR lpCaption, UINT uType)`

uType常量定义以`MB_`开头，常用`MB_OK`

### wingid.h

#### GetStockObject

`GetStockObject` 返回一个储藏的GDI对象
