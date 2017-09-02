build.bat 
旨在帮助你以简单的方式编译C/C++语言的源代码，
生成在Windows平台上可以运行的可执行代码。

build.bat 
通过简单的设置就能使用。

# 命令语法

`build.bat` 编译当前目录下所有的源代码

`build.bat <源代码文件>` 编译指定的源代码

# 编译器设置

build.bat 目前支持两种编译器：GCC和MSVC编译器。
可以根据惯用的编译器进行设置。

通过在COMPLIER变量中设置不同的值来指定编译器。
目前COMPLIER变量可用的值有“gcc”以及“cl”，分别对应GCC编译器和MSVC编译器。

## GCC设置

如果你的GCC编译器已在PATH环境变量中，则无需额外设置。

否则，你需要在GCC_PATH变量中指定编译器的路径。

可以设置GCC_EXTRA_ARGS变量，这会作为额外的命令行参数传递给GCC编译器。

## MSVC编译器

如果你已经设置了PATH环境变量、INCLUDE环境变量和LIB环境变量，则无需额外设置。

否则，你需要在CL_PATH、CL_INCLUDE、CL_LIB变量中指定路径。参见[变量设置提示](#cl_pathcl_includecl_lib设置提示)。

可以设置CL_EXTRA_ARGS变量，这会作为额外的命令行参数传递给MSVC编译器。

### CL_PATH、CL_INCLUDE、CL_LIB设置提示

如果你使用VS Studio，新建一个C/C++项目，然后打开项目属性窗口。转到“C/C++路径”即可查看电脑上MSVC编译器所需的路径。
CL_PATH、CL_INCLUDE、CL_LIB变量分别对应“Executable Diretories”、“Include Diretories”和“Library Direcotories”。

![](/camo/howto/make-use-of-build-batchfile.md/cl-config.png)
