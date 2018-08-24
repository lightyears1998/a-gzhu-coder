# Files文件IO笔记

## Assets

AssetsManager `getAssets()`

- `list()`
- `oepn()`

## SharedPreferences

`data/data/package_name/shared_prefs`

储存键值对，不支持自定义类型的储存；实质是封装了xml储存

### 基本使用

1. 获取SharedPreferences对象，使用`get`系列方法

    1. 使用`Context.getSharedPreferences(String name, int mode)` 文件名，模式
    2. 使用`Activity.getPreferences(int mode)` 自动使用Activity的类名作为文件名
    3. 使用`PreferenceManager的getDefaultSharedPreferences(Context context)` 使用当前应用程序的包名作为前缀创建文件

2. 使用`edit()`获取editor对象
3. 使用`put`系列方法
4. `commit()`

### 首选项功能

封装了方便的首选项功能

## 内部储存

`data/data/package_name/files/`

应用程序私有数据，卸载应用后会被删除

空间有限且资源宝贵

### 读写

FileOutputStream和FileInputStream对象 `openFileInput(String filename)`, `openFileOutput(String filename, int mode)`

- `getFilesDir()` 获取内部文件的绝对路径
- `getCacheDir()` 获取内部缓存的绝对路径
- `getDir()` 在内部储存空间中创建或打开目录
- `deleteFiles()` 删除文件
- `fileList()` 返回当前应用存放的所有私有文件名称

## 外部储存

全局可用的储存空间，通常是SD Card

需要申请权限

### 检查外部储存挂载

`Environment.getExternalStorageState()`

`Environment.MEDIA_MOUNTED`

### 获取路径

主要有两种路径

- `/mnt/sdcard`
- `/storage/sdcard0`

`Environment.getExternalStorageDirectory().getAbsolutePath()`

### 获取空间大小

通过文件系统统计类`StatFs`获取

### 目录结构

公有目录`Environment.getExternalStoragePublicDirectory(String type)`

- Music
- Podcasts
- Ringtones
- Alarms
- Notifications
- Pictures
- Movies
- Download

私有目录 `/mnd/sdcard/Android/data/package_name`

可以使用自定义目录

### 访问私有目录文件

`getExternalFilesDir()`

只要知道路径，就可以通过常规的IO流读写文件

## SQLite

`data/data/package_name/databases/`

SQLite通过文件保存数据，文件名即数据库名

SQLite支持无类型数据

### 操作步骤

1. 创建SQLiteDatabase对象 `openDatabase(path, factory, flags)` factory为null则使用默认的工厂
2. 执行语句

    - void `execSQL(String sql)`, `execSQL(String sql, Object[] bindArgs)` 非select语句
    - Cursor `rawQuery` select语句等
    - `beginTransaction()`, `endTransaction()`

3. 操作返回的数据Cursor

- `move`系列方法
- `get`系列方法
- `getType()` 返回字段的数据类型
- `close()`

#### SimpleCursorAdapter

将Cursor中的数据与控件进行简易匹配的适配器，继承于CursorAdapter

#### 事务

- `inTransaction()`, `setTransactionSuccessful()`

### 数据库的创建和更新：SQLiteOpenHelper

- `onCreate()`, `onUpgrade()` 版本
- `getReadableDatabase()`, `getWriteableDatabase()` 创建数据库对象
