![Activity生命周期](/camo/note/android_activity.png)

onCreate, onRestart, onStart, （可见时）onResume, （被其他Activity不完全遮挡）onPause, （不可见时）onStop, onDestroy

## Intent

六类信息：Component, Action, Category, Data, Extra and Flag

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

```java

```

## 带返回值启动Activity

