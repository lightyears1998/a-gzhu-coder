System.out 在Logcat中的级别为Info，tag为System.out

`getResources().getAssets().open({"filename"});`

Color.RED

## 异步装载器Loader

通过系统的回调方法将数据异步装载到ListView、GridView等控件中。

1. 对Activity和Fragment均有效
2. 存在数据改变通知机制
3. 横竖屏切换时可以保证组件数据不丢失

## ContentProvider

- ContentProvider 允许程序访问另一个程序里的数据，并保证数据的安全性
- ContentResolver 访问另一个程序提供的数据

## BroadcastReceiver

获取手机各种实时状态

普通广播、有序广播

LocalBroacastManager

## Service

没有界面且能长时间运行于后台的应用组件

## 电话与短信

- SMSManager
- TelephoneManager

## 媒体

MeidaPlayer

## Sensor

SensorManager
