# MFC常用类和工具

- 代码文档化（XML注释） <https://docs.microsoft.com/zh-cn/cpp/ide/recommended-tags-for-documentation-comments-visual-cpp?view=vs-2017>

MFC六大核心机制

1. MFC初始化
2. 运行时类型识别RTTI
3. 动态创建
4. 串行化
5. 消息映射和命令传递

## 参考资料

- [鸡啄米MFC教程](http://www.jizhuomi.com/catalog.asp?tags=MFC)

## 常用类

### CWinApp

可以修改应用程序的名字

### CArchive

串行化神器。

使用示例

```cpp
CFile file;
file.Open(L"data.bin", CFile::modeCreate | CFile::modeReadWrite);
CArchive ar1(&file, CArchive::store);

ar1.WriteObject(&s1);
ar1.WriteObject(&s2);
ar1.WriteObject(&manager);
ar1.Close();

/* ====== */

file.SeekToBegin();
CArchive ar2(&file, CArchive::load);
Student * s = (Student*)ar2.ReadObject(RUNTIME_CLASS(Student));
Management * man = (Management*)ar2.ReadObject(RUNTIME_CLASS(Management));

```
