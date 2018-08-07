## 常用组件

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

### AssetManager

路径不需要以"/"开头

### Toast

`Toast.makeText(context, "hint", Toast.LENGTH_LONG).show()` 

### Notification

状态栏通知

### AlertDialog

对话框

### ProgressDialog

### DatePickerDialog

### TimePickerDialog

### PopupWindow

IO blocked

### Menu

- OptionMenu
- ContextMenu
- SubMenu
- PopupMenu

### TextView

属性

- gravity 空间内容对其方式

文本属性

- text 
- textColor
- textStyle
- textSize 以sp为单位
- background


autoLink
- all, none
- phone, web, email, map

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

支持HTML标签 <b>, <i>, <u>

`getText().toString()`

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

### ImageButton

通过src属性链接到文件

### ImageView

属性

- src 内容，不会自动拉伸
- background 背景，根据View宽度自动拉伸

### RadioButton & CheckBox

RadioGroup `getChildCount()` `getChildAt()`

RadioButton / CheckBox `isChecked()`

注意到RadioButton的Listener与CheckBox的Listener处于不同的包中

```java
// android.widget.RadioGroup.OnCheckedChangeListener
// 注意方法签名中的checkedId是R类分配的id

public void onCheckedChanged(RadioGroup group, int checkedId) {
	switch (checkedId) {
		case R.id.radioButton:
			textView.setText("One");
			break;
		case R.id.radioButton2:
			textView.setText("Two");
			break;
		case R.id.radioButton3:
			textView.setText("Three");
			break;
	}
}
```

```java
// android.widget.CompoundButton.OnCheckedChangeListener

```

### ToggleButton

属性

- checked
- textOn, textOff 按下按钮，断开按钮时显示的文本

`check()`是否被选中

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

#### DatePicker

属性
- startYear, endYear
- 

### ArrayAdapter

android.R.layout.Xxx

- simple_list_item_1 单独一行
- simple_list_item_2 两行
- simple_list_item_checked
- simple_list_item_multiple_choice
- simple_list_item_single_choice

静态创建

```xml
<!-- res/values/arrays.xml -->
<resources>
<string-array name="myarray">
    <item>Hello<item>
    <item>,<item>
    <item>world<item>
</string-array>
</rsources>
```

```xml
<listView entries="@array/myarray" />
```

动态创建

`ArrayAdapter<?>(context, 模板layout, data);`

`ArrayAdapter.createFromResource(context, R.array.myarry, 模板layout);`

```java

// 从String数组创建
String[] strs = {"This", "is", "my", "sentence"};
ArrayApater<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_expandable_list_item_1, strs);
ListView view = findViewById(R.id.listView);
view.setAdapter(adapter);

// 以CharSequence形式从文件创建
ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.myarry, android.R.layout.simple_expandable_list_item_1);

```

### SimpleAdapter

创建ListItem中每个Item的布局

```xml
<!-- res/layout/list_item -->
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    android:orientation="horizontal" android:layout_width="match_parent"
    android:layout_height="match_parent">

    <!-- 头图 -->
    <ImageView
        android:id="@+id/avatar"
        android:layout_width="64dp"
        android:layout_height="64dp"
        android:paddingLeft="8dp"
        android:baselineAlignBottom="true"
        />

    <LinearLayout
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:orientation="vertical">
        
        <!-- 标题 -->
        <TextView
            android:id="@+id/caption"
            android:paddingLeft="8dp"
            android:textSize="20sp"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content" />

        <!-- 箴言 -->
        <TextView
            android:id="@+id/says"
            android:paddingLeft="8dp"
            android:textSize="12sp"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content" />

    </LinearLayout>

</LinearLayout>
```

使用适配器

```java

public class SettingsActivity extends AppCompatActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        int[] avatarIds = {R.drawable.ic_backup_black_24dp, R.drawable.ic_explore_black_24dp, R.drawable.ic_timer_black_24dp};
        String[] captions = {"One", "Two", "Three"};
        String[] says = {
                "I would like to say",
                "Once I have the power of Intel i7 CPU",
                "I would like to run Android Studio"
        };

        List<Map<String, Object>> list = new ArrayList<Map<String, Object>>();
        for (int i = 0; i < captions.length; ++i)
        {
            Map<String, Object> item = new HashMap<String, Object>();
            item.put("avatar", avatarIds[i]);
            item.put("caption", captions[i]);
            item.put("says", says[i]);
            list.add(item);
        }

        SimpleAdapter adapter = new SimpleAdapter(
                getApplicationContext(), list, R.layout.list_item,
                new String[]{"avatar", "caption", "says"}, new int[]{R.id.avatar, R.id.caption, R.id.says}
                );
        ListView view = findViewById(R.id.listView);
        view.setAdapter(adapter);
    }
}

```

### SimpleCursorAdapter

结合SQLite简化流程

### BaseAdapter

```java

public class AnimalAdapter extends BaseAdapter {
    private LinkedList<Animal> data;
    private Context context;

    public AnimalAdapter(LinkedList<Animal> data, Context context) {
        this.data = date;
        this.context = context;
    }

    @Override
    public int getCount() {
        return date.size();
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        convertView = LayoutInflater.from(context).inflate(R.layout.item_list_animal, parent, false);
        // 视图中各项资源操作
        return convertView;
    }
}


```


### ListView绑定BaseAdapter

绑定

```java

setAdapter(new AnimalAdapter(linkedlist, this));

```


监听单击事件

```java
class MyActivity implements AdapterView.OnItemClickListener {
    @Override
    public void onItemClick(AdapterView<?> parent, View view, int positon, long id)
    {
        Toast.makeText(this, "You click" + position, Toast.LENGTH_SHORT).show();
    }
}

```

### BaseAdapter优化

1. 复用ConvertView
2. 创建静态类ViewHolder以减少`findViewById()`的使用

复用BaseAdapter

1. 使用泛型

#### 参考

1. http://www.imooc.com/learn/372
2. http://www.runoob.com/w3cnote/android-tutorial-customer-baseadapter.html

### ListView数据更新

`NotifyDataSetChanged()`

### GridView

网格视图

### Spinner

列表视图

### AutoCompleteTextView

自动完成文本域，提示用户自动完成的强大功能

创建和绑定适配器

```java
private ArrayAdapter<String> buildAdapter() {
	String data[] = {
			"Beijing", "Shanghai", "Guangzhou", "China", "Tianjin"
	};
	ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_dropdown_item_1line, data);
	return adater;
}

AutoCompleteTextView autoCompleteTextView = findViewById(R.id.autoCompleteTextView);
autoCompleteTextView.setAdapter(buildAdapter());
```

### ExpandableListView

可折叠列表

### ViewFlipper

翻转视图 用于制作用户第一次登陆的引导页面等
