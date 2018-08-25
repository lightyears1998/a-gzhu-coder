# Win32 API参考

- [API List](https://docs.microsoft.com/zh-cn/windows/desktop/api/index)
- [Playground](https://github.com/lightyears1998/quiet-space/tree/master/playground/w32)

## [数据类型](https://docs.microsoft.com/zh-cn/windows/desktop/LearnWin32/windows-coding-conventions)

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

### HANDLE

- *INVALID_HANDLE_VALUE*
- `GetStdHandle()` `STD_INPUT_HANDLE`, `STD_OUTPUT_HANDLE`

## 头文件与工具函数

### windows.h

同时引入了

- `windef.h` 基本类型定义
- `winbase.h` 内核函数
- `wingdi.h` 图形设备接口函数
- `winuser.h` 用户接口函数，包括`MessageBox()`

#### 应用程序入口

WinMain

```cpp
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow);
```

wWinMain

```cpp
int WINAPI wWimMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);
```

如果无法生成，检查链接器的系统设定中的“子系统”项目。

若出现未加载符号的提示，在调试选项中选择加载符号即可。

#### WNDCLASS与注册窗口

WNDCLASS

1. 每一个WNDCLASS都有一个相关联的窗口过程

```cpp
typedef struct tagWNDCLASS {
  UINT      style;
  WNDPROC   lpfnWndProc;
  int       cbClsExtra;        // 分配给窗口类结构之后的额外字节数
  int       cbWndExtra;        // 分配给窗口类实例之后的额外字节数
  HINSTANCE hInstance;         // 窗口过程所对应的实例句柄
  HICON     hIcon;
  HCURSOR   hCursor;
  HBRUSH    hbrBackground;
  LPCTSTR   lpszMenuName;
  LPCTSTR   lpszClassName;
} WNDCLASS, *PWNDCLASS;

// 10成员
```

注册窗口的过程

1. 填充`WNDCLASS`结构体
2. 注册窗口 `RegisterClass()`
3. 创建并显示窗口 `CreateWindow()`, `ShowWindow()`, `UpdateWindow()`
4. 进入消息循环，发送特定消息与窗口过程

```cpp
WNDCLASS wndclass;
wndclass.style = CS_HREDRAW | CS_VREDRAW;
wndclass.lpfnWndProc = WndProc;
wndclass.cbClsExtra = 0;
wndclass.cbWndExtra = 0;
wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
wndclass.lpszMenuName = NULL;
wndclass.hInstance = hInstance;
wndclass.lpszClassName = TEXT("HelloWindow");

if (!RegisterClass(&wndclass)) {
    MessageBox(NULL, TEXT("红牌警告：窗口注册失败啦"), TEXT("注册失败"), 0);
    return 0;
}

HWND hwnd = CreateWindow(
    TEXT("HelloWindow"),
    TEXT("我的窗口"),
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    480,
    320,
    NULL,                    // 父窗口句柄
    NULL,                    // 窗口菜单句柄
    hInstance,               // 应用程序实例句柄
    NULL                     // 创建窗口的参数
);

ShowWindow(hwnd, nCmdShow);
UpdateWindow(hwnd);

MSG msg;
while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}
return msg.wParam;
```

窗口过程函数

```cpp
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;
    switch (message)
    {
    case WM_CREATE: return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rc);
        DrawText(hdc, TEXT("Hello Windows!"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
```

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

### [MessageBox](https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-messagebox)

`MessageBox(HWND hParent, LPCSTR lpText, LPCSTR lpCaption, UINT uType)`

uType常量定义以`MB_`开头，常用`MB_OK`

### wingid.h

#### GetStockObject

`GetStockObject` 返回一个储藏的GDI对象

## 示例

1. 注册窗口，处理消息循环 <https://github.com/lightyears1998/quiet-space/blob/master/playground/mfc/ch1/ch1ex2WindowsAndMessage/%E6%BA%90.cpp>
