# 关于

这里有从新生群里收集到的题目，还有我自己写的解答。
希望这些东西对你学习C/C++有所帮助 ^_^

# 文件结构

仓库中的文件编码为UTF-8，换行符为Windows风格（CRLF）。

| 文件或目录 | 提示 |
| ------ | ------ |
| *.c | C语言源文件 |
| *.cpp | C++源文件 | 
| pre-school/ | 学姐（学长）在新生群布置的题目和尝试解答 |
| snippets/ | 帽子（学长）和仙女（学姐）给出的练习小题目 |
| */index.md | 题目索引 |
| */bin/ | 已经编译好的Windows可执行文件 |

| 辅助标记 | 提示 |
| ------ | ------ |
| -brhole | Brain Hole <br/> 脑洞请忽略…… |
| -clargsreq | Command-Line Arguments Required <br/> 需要命令行参数 |


# 使用帮助

## 集成开发环境

### Dev C++

这个仓库中的文件都是UTF-8编码的文件。
Dev C++默认以系统编码打开文件，而Windows简体中文版的默认系统编码为gb2312。
如果用Dev C++直接打开文件，代码中的中文字符不能正确显示。
可以将文件的编码从UTF-8转换为gb2312。
方法是使用记事本打开文件，按Alt+F+A显示“另存为”窗口，选择以“ANSI”编码保存。

## 命令行工具

### Linux系统上的GCC

使用你自己系统的编译器哦。这里介绍GCC编译器的使用。
如果你不确定系统上有没有安装编译器，在命令行工具中尝试一下下面的命令

```
gcc --version
```

如果发现你的系统没有安装GCC编译器，可以尝试使用下面的方法安装
```
yum install gcc
yun install gcc-c++

-- 或者

apt-get install gcc
apt-get install g++
```

编译文件，请使用
```
gcc <C源文件> -o <欲生成可执行文件的文件名>
g++ <C++源文件> -o <欲生成可执行文件的文件名>

-- 例如：
-- gcc day1-ex1.c -o day1-ex1
-- 然后运行它：
-- day1-ex1
```

# 可能有用外部链接

* **[CPP Reference][link_cppreference]** C/C++标准参考
* **[QF Blog: C Begginer Menu][link_blog]** 我和我的两个好朋友一起写的关于C语言入门的博客，还没有完善，希望能有所帮助 : )

# 许可

你可以自由地使用这个代码库中的代码学习，
如果你的使用方式涉及版权，请参考下面的信息：

题目来自学姐（学长），文件中附有题目的来源信息。
题目的版权属于出题者。
如果你认为此处的文件侵犯了你的权利，
请给我issue，我会立即处理。☆⌒(*＾-゜)v THX!!

我的解答和其他归属于我的文件属于公有领域。

# 最后

Hope you enjoy it! (ง •̀_•́)ง

[link_cppreference]: http://en.cppreference.com/w/
[link_blog]: https://blog.qfstudio.net/index.php/c-and-cpp-menu/
