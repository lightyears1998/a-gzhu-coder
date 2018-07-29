## 基本概念

Android应用运行在自己的安全沙箱内。（每个应用是操作系统的不同用户，每个应用在其自己的Linux进程内运行，每个进程具有自己的虚拟机） *最小权限原则*

基本组件

- *Activity* 具有用户界面的单一屏幕
- *Service* 服务后台长时间运行的操作，不提供用户界面
- *ContentProvider* 内容提供程序
- *BoardcastReceiver* 广播接收器
- *Intent* 消息传递者

文件组织

- *res/* 自动生成对应的Resource ID
- *assets/* AssetManager
- *raw/* 生成id的二进制流

资源组织

- *文字* strings.xml `getResources().getText(R.string.name);` `android:text:@string/hello_world`
- *图片* drawable/ `R.drawable.icon` `android:background:@drawable/icon`
- *颜色* colors.xml `getResources().getColor(R.color.red);`
- *布局* `R.layout.main`
- *边距* dimens.xml
- *控件* `findViewById(R.id.text_view);`
- *属性* `?attr/...`

![Activity生命周期](/camo/note/android_activity.png)]

AndroidManifest.xml
```xml
<manifest package="com.example.app">
    <application
        icon="@mipmap/ic_launcher_round"
        label="@string/app_name"
        theme="@style/AppTheme">
        <activity
            name=".MainActivity"
            label="@string/app_name"
            theme="@style/AppTheme">
            <intent-filter>
                <action name="android.intent.action.MAIN" />
                <category name="android.intent.category.LAUNCHER" />
            </intent-fileter>
        </activity>
    </application>
</manifest>
```

## 外观

### 原型设计

墨刀 mockplus

### 9-patch

## 常用组件

### Logcat

verbose, debug, info, warn, error

### Intent

```java
Intent intent = new Intent(this, AnotherActivity.class);
intent.putExtra("MSG_TAG", "EXTRA_MESSAGE");
startActivity(intent);
```

```java
Intenet intent = getIntent();
String Message = intent.getStringExtra("MSG_TAG");
```

## 常用布局

### LinearLayout

match_parent == fill_parent

布局自身

- layout_gravaty
- layout_width
- layout_height
- divider
- *showDivider* none, beginning, end, middle（每两个组件之间）
- dividerPadding

子元素的对齐方式

- *orientaion* horizontal(default), vertical
- *gravity* 

layout_width与layout_weight组合

- 对于在horizontal对齐的LinearLayout内的两个View，如果View的layout_width被设置为0dp，并设置了layout_weight属性，将按权重分配layout_width
- 如果容器内View被设置为match_parent，并设置了layout_weight属性，设有4份View，每份View的最终权重为(1-(份数-1)*(权重/权重之和))；如View权重1, 2, 3，则最终Layout_width为2, 1, 0
- wrap_content则视情况而定，居于前述两种情况之间

LinearLayout不能在同一水平线上布置一左一右的两个控件

属性

- `baselineAligned` 子View是否根据baseline对齐

### RelativeLayout



### DrawerLayout

布局根节点必须是DrawerLayout

主题NoActionBar化

```xml
<style name="AppTheme.NoActionBar" parent="AppTheme">
    <item name="windowActionBar">false</item>
    <item name="windowNoTitle">true</item>
</style>
```

自定义Toobar

`onCreate()`
```java
Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
setSupportActionBar(toolbar);
```

渲染菜单

`onCreateOptionMenu(Menu menu)`
```java
public boolean onCreateOptionsMenu(Menu menu) {
    getMenuInflater().inflate(R.menu.main, menu);
    return true;
}
```

Appbar与Drawer联动

```java
DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
        this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close
);
drawer.addDrawerListener(toggle);
toggle.syncState();
```
