# 重要的Windows API索引

- [API List](https://docs.microsoft.com/zh-cn/windows/desktop/api/index)
- [Playground](https://github.com/lightyears1998/quiet-space/tree/master/playground/w32)

## windows.h

还引入了

- `windef.h` 基本类型定义
- `winbase.h` 内核函数
- `wingdi.h` 图形设备接口函数
- `winuser.h` 用户接口函数，包括`MessageBox()`

```cpp

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MessageBox(NULL, TEXT("Message"), TEXT("Caption"), 0);
}

```

## [MessageBox](https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-messagebox)

`MessageBox(HWND hParent, LPCSTR lpText, LPCSTR lpCaption, UINT uType)` 

uType常量定义以`MB_`开头，记住常用的