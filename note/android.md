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

ShapeDrawable



## 外观

### 原型设计

墨刀 mockplus

### 9-patch

将图片放入Resource文件夹内，然后使用Create 9-patch png.

### 反编译

apktool

dex2jar

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

### TextView

属性

- gravity 空间内容对其方式

文本属性

- text 
- textColor
- textStyle
- textSize 以sp为单位
- background

阴影属性

阴影效果是运行时属性，不会在设计器中体现

- shawdowColor, shawdowRadius 阴影颜色与模糊程度
- shawdowDx, shawdowDy 水平偏移与竖直偏移

边框 自定义Shape左为Background

http://www.runoob.com/w3cnote/android-tutorial-edittext.html

drawableXxx

autolink

融合Html

部分可点击TextView：SpannableString

### EditText

属性

- hint
- textColorHint
- selectAllOnFocus
- inputType
- singleLine

### Button

```java
class MyActivity extends AppCompactActivity
    implements View.OnClickListener
{
    @Override
    public void OnCreated(Bundle savedInstanceState)
    {
        findViewById(R.id.button).setOnClickListener(this);
    }

    @Override
    public void OnClick(View view)
    {
        // Related opearations...
    }
}

```

自定义Button http://www.runoob.com/w3cnote/android-tutorial-button-imagebutton.html

### ImageView

属性

- src 内容，不会自动拉伸
- background 背景，根据View宽度自动拉伸

### RadioButton & CheckBox

RadioGroup `getChildCount()` `getChildAt()`

RadioButton / CheckBox `isChecked()`

### ToggleButton

属性

- checked
- textOn, textOff

### Switch

开关

### ProgressBar

```java
getMax();
getProgress();
getSecondaryProgress();  // 类似与视频缓冲进度
increasementProgressBy(int diff);
isIndeterminate();  // 是否处于不确定模式下
setIndeterminate(boolean bool)  // 设置不确定模式
```

### SeekBar

拖动条

### RatingBar

星级评分条

### ScrollView

`fullScroll()`

### Date and Time

TextClock, AnalogClock, Chronometer, DatePicker, TimePicker, CalendarView

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

- gravity / ignoreGravity
- 根据父容器定位 layout_alignParentXxx (Left | Right | Bottom | Top) layout_centerInParent (Horizontal | Vertical)
- 根据兄弟组件定位 layout_toXxxOf (Left | Right) layout_above(below) layout_alignXxx (Left | Right | Top | Bottom)
- layout_margin（外边距）
- layout_padding（内填充）

*梅花布局*

### TableLayout

属性

- collapseColumns 指定隐藏行
- shrinkColumns 指定可收缩行
- stretchColumns 制定可伸展行

单元格

- layout_column
- layout_span

### FrameLayout

属性

- foreground 前景色/前景图像
- foregroundGravity

### GridLayout

属性

- columnCount, rowCount

对于布局中的View

- layout_row, layout_column 设置行列 0-based
- layout_rowSpan, layout_columnSpan 设置跨行，设置跨列

### AbsoluteLayout

专业适配当前屏幕

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

## 源

http://www.runoob.com/w3cnote/android-tutorial-intro.html
