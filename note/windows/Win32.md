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

WinMain

```cpp
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MessageBox(NULL, TEXT("Message"), TEXT("Caption"), 0);
}
```

如果无法生成，检查链接器的系统设定中的“子系统”项目。

若出现未加载符号的提示，在调试选项中选择加载符号即可。

注册窗口

1. 填充`WNDCLASS`结构体
2. 注册窗口 `RegisterClass()`
3. 创建并显示窗口 `CreateWindow()`, `ShowWindow()`, `UpdateWindow()`
4. 进入消息循环，发送特定消息与窗口过程

```cpp

```

窗口过程函数

```cpp

```

### 用户交互函数

## [MessageBox](https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-messagebox)

`MessageBox(HWND hParent, LPCSTR lpText, LPCSTR lpCaption, UINT uType)`

uType常量定义以`MB_`开头，常用`MB_OK`

## 示例

1. 注册窗口，处理消息循环 <https://github.com/lightyears1998/quiet-space/blob/master/playground/mfc/ch1/ch1ex2WindowsAndMessage/%E6%BA%90.cpp>
