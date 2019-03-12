# Linux笔记

## Chapter 1 概述

### 发行版

- *Arch*
- *CentOS*

### 硬件基础

组件和设备都是文件

- 芯片组 北快南慢
- 硬盘 IDE(Master/Slave): `/dev/hda` SATA/USB/SCSI: `/dev/sda` 扇区柱面 磁盘第一扇区（主引导分区446bytes + 分区表64bytes）
- 当前鼠标 `/dev/mouse` 当前CDROM `/dev/cdrom`

集群计算机系统（Cluster）

### 硬件设置

#### 磁盘分区

##### MBR(Master Boot Record)

- 分区最小单位：柱面
- 默认分区表支持4组分区信息：主分区、拓展分区（硬盘限制） `/dev/sda1` ~ `/dev/sda4`
- 拓展分区用于记录额外的分区信息，不能格式化以记录数据，额外分区称为“逻辑分区”，唯一（操作系统限制）
- 逻辑分区自`/dev/sda5`始，无论默认分区表4组分区是否全部存在
- Primary, Extended, Logical

### 启动流程

1. **BIOS** 读取CMOS参数，分析储存设备
2. **MBR** 446bytes内含Boot loader
3. **Boot loader**
4. **Kernel**

### 目录树

挂载：结合目录树与磁盘内容

常见挂载点：

- `/`
- `/usr`
- `/home`
- `/var`

### 软件基础

- 个人文件夹 `/home/usrname`
- man文档 `/usr/share/doc/` info文档 `/usr/share/info/`

#### Run-level

1. LEVEL0 关机
2. LEVEL3 命令行模式 tty1 ~ tty6
3. LEVEL5 含有图形界面模式 tty7
4. LEVEL6 重启

`init [number]` 切换模式

#### 图形管理员 Window Manager

- 重启X Windows `Ctrl + Alt + Backspace`
- 切换Terminal `Ctrl + Alt + [F1~F7]`

#### Commamnd

`command [-options] parameter1 parameter2...`

- 命令区分大小写
- 可以使用反斜杠转义[Enter]，使命令跨行生效
- `Ctrl + D` End of Input

系统命令

- `sync` 将数据写入磁盘
- `reboot`, `halt`, `poweroff`

常见命令

- `man` Manual
- `cal [[month] year]`
- `date`
- `bc`

#### Manual

- `man -f command` `whatis command` 列出command的手册
- `man -k keyword` `man -K keyword-in-text` `apropos command` 根据关键字列出command的手册
- `man [1-9] command`
- 使用`man man`查看9类数字说明符对应的含义
- `/string` `?string` 向下、向上查询字符串
- `n, N` 下一个 /上一个查询目标

#### Info

- `info info`
- `h` 帮助系统
- `N P` 前后导航
- `U` 向上

#### Terminal

- `$` normal user
- `#` Root user；`#`比`$`更接近0

#### 编辑器

`vi`, `nano`, `vim`

## Chapter 2 启动

### 忘记密码？单用户维护模式

1. 编辑GRUB引导，在`kernel`部分添加`single`参数
2. 取得root权限登陆系统，使用`passwd`命令修改密码

### 欢迎界面

- tty `/etc/issue` `man issue` `man getty`
- `etc/motd`

## Chapter 3 用户与用户组
