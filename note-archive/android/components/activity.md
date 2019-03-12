# Activity笔记

## 生命周期

onCreate, onRestart, onStart, （可见时）onResume, （被其他Activity不完全遮挡，执行后可以被销毁）onPause, （不可见时）onStop, onDestroy

- Resumed 在用户最前端
- Paused 可见但失去用户焦点
- Stopped 不可见
- Destroyed 销毁

重写生命周期方法时，在重载函数结束前显式调用父类方法。

## Intent

Intent中携带的六类信息：Component, Action, Category, Data, Extra and Flag

```java
Intent intent = new Intent(this, NextActivity.class);
startActivity(intent);
```

```java
Intent intent = new Intent(this, NextActivity.class);
intent.putExtra("Key", "Value");
intent.putExtra("iKey", 100);

intent = getIntent();
String value = intent.getStringExtra("Key");
int iValue = intent.getIntExtra("iKey");
```

### Component属性

如果指定了ComponentName，其他属性将被忽略

### Action属性

- ACTION_CALL
- ACTION_MAIN
- ACTION_BATTERY_LOW
- ACTION_SRENN_ON

### Category属性

- CATEGORY_HOME
- CATEGORY_LAUNCHER
- CATEGORY_GADGET 可以作为其他Activity的一部分插入

### Data属性

可以与Action配合使用

`setData()` 可以指定待操作的Uri

### Extra

携带的额外信息

### Flag

- FLAG_ACTIVITY_NEW_TASK 作为一个新task初始化activity
- FLAG_ACTIVITY_NO_HISTORY 不放入返回栈中
- FLAG_FROM_BACKGROUND 通知系统此操作来自于后台操作，并非用户的直接选择

### IntentFilter

标识一个Activiy可以处理的Intent

## Bundle

Bundle可以捆绑在Intent中，提供额外的数据

```java
Bundle bundle = new Bundle();
bundle.putString("Key", "Value");
intent.putExtras(bundle);
```

```java
Bundle = intent.getExtras();
bundle.getString("Key");
```

## 带返回值启动Activity

- 在源中请求 `startActivityForResult(Intent intent, int requestCode)`
- 回传数据 `setResult(int resultCode, Intent data)`
- 在源中处理回传信息 `onActivityResult(int requestCode, int resultCode, Intent data)`

在源中请求

```java
Intent intent = new Intent(this, NextActivity.class);
startActivityForResult(intent, 1);
```

回传数据

```java
Intent intent = new Intent();
intent.putExtra("result", ((EditText)findViewById(R.id.editText)).getText().toString().trim());
setResult(Activity.RESULT_OK, intent);
finish();
```

在源中处理回传信息

```java
@Override
protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
    super.onActivityResult(requestCode, resultCode, data);

    if (requestCode == 1 && resultCode == Activity.RESULT_OK) {
        Toast.makeText(this, data.getStringExtra("result"), Toast.LENGTH_LONG).show();
    }
}
```

## Task 与 Back Stack

Task由执行某一个共同任务时与用户交互产生的多个Activity组成的集合；Back Stack根据Activity后进先出的顺序压栈和弹栈。
