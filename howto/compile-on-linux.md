你可以使用你自己系统的编译器哦。

这里介绍GCC编译器的使用。许多Linux系统上都附带了GCC编译器。
如果你不确定系统上有没有安装编译器，在命令行工具中尝试一下下面的命令：

```bash
gcc --version
```

如果发现你的系统没有安装GCC编译器，可以尝试使用下面的方法安装一个：
```bash
yum install gcc
yun install gcc-c++

-- 或者

apt-get install gcc
apt-get install g++
```

编译文件，请使用：
```bash
gcc <C源文件> -o <欲生成可执行文件的文件名>
g++ <C++源文件> -o <欲生成可执行文件的文件名>

-- 例如：
-- gcc day1-ex1.c -o day1-ex1
-- 然后运行它：
-- ./day1-ex1
```
