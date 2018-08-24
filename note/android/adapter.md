# Adapter笔记

适配器，适配器控件与数据之间的桥梁

MVC：Model（数据源）， View（视图）， Control（适配器）

## 常见Adapter

### ArrayAdapter

处理只含有文字信息的情况，使用数组或`List<String>`形式的数据源

预定义资源 android.R.layout.Xxx

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

列表项较为复杂，或列表项含有不同类型的控件的情况，使用`List<Map>`形式的数据源

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

结合SQLite简化流程，使用Cursor作为数据源

### 自定义Adapter：继承BaseAdapter

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

    // getItem()和getItemId()可根据需要进行编写
}
```

## 与适配器关联的View

### Spinner

加载数据

1. 在xml文件中预先定义
2. 与ArrayAdapter关联

#### 在xml文件中定义

1. 在`res/values`中定义xml文件，结构`resourse -> string-array -> item`
2. 通过设定`entries`属性为`@array/spinner_item`来引用

#### 示例：绑定ArrayAdapter

设置适配器

```java
Spinner alphaSpinner = findViewById(R.id.spinner);
Spinner betaSpinner = findViewById(R.id.spinner2);

String[] data = {"one", "two", "three"};

final ArrayAdapter<CharSequence> alphaAdapter = ArrayAdapter.createFromResource(this, R.array.spinner, android.R.layout.simple_spinner_item);
alphaAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
ArrayAdapter<String> betaAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, data);

alphaSpinner.setAdapter(alphaAdapter);
betaSpinner.setAdapter(betaAdapter);
```

设置监听器

```java
alphaSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
    @Override
    public void onItemSelected(AdapterView<?> adapterView, View view, int position, long id) {
        // 通过适配器获取item
        String item = (String)alphaAdapter.getItem(position);
        Log.i("TAG", item);
        // 通过适配器控件获取item
        String str = (String)adapterView.getItemAtPosition(position);
        Log.i("TAG", str);
    }

    @Override
    public void onNothingSelected(AdapterView<?> adapterView) {

    }
});
```

### ListView

数据更新 `NotifyDataSetChanged()`

### 示例：绑定BaseAdapter

绑定

```java
// AnimalAdapter参见自定义Adapter一节
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

此外还有OnNothingSelectedListener

### 优化：BaseAdapter优化

复用ConvertView，并创建静态类ViewHolder以减少`findViewById()`的使用

1. 定义静态类ViewHolder
2. 检测convertView是否为空；若为空，将布局文件渲染成convertView，将ConvertView与ViewHolder关联，`setTag()`；若不为空，`getTag()`。
3. 设置ViewHolder。

```java
public class MyAdapter extends BaseAdapter {
    @Override
    public Object getItem(int position) {
        return list.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public int getCount() {
        return list.size();
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ViewHolder viewHolder;
        if (convertView == null)
        {
            convertView = LayoutInflater.from(MainActivity.this).inflate(R.layout.list_item, null);
            viewHolder = new ViewHolder();
            viewHolder.textView = convertView.findViewById(R.id.textView);
            viewHolder.imageView = convertView.findViewById(R.id.imageView);
            convertView.setTag(viewHolder);
        } else {
            viewHolder = (ViewHolder) convertView.getTag();
        }
        viewHolder.imageView.setImageResource((int)list.get(position).get("img"));
        viewHolder.textView.setText((String)list.get(position).get("text"));
        return convertView;
    }
}
```

### GridView

可以向两个方向滚动的控件，需要绑定BaseAdapter

用法与ListView类似

```java
public class MyAdapter extends BaseAdapter
{
    @Override
    public Object getItem(int position) {
        return list.get(position);
    }

    @Override
    public int getCount() {
        return list.size();
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ViewHolder viewHolder;
        if (convertView == null) {
            convertView = LayoutInflater.from(MainActivity.this).inflate(R.layout.grid_item, null);
            viewHolder = new ViewHolder();
            viewHolder.imageView = convertView.findViewById(R.id.imageView);
            convertView.setTag(viewHolder);
        } else {
            viewHolder = (ViewHolder)convertView.getTag();
        }
        viewHolder.imageView.setImageResource((int)list.get(position).get("img"));
        return convertView;
    }
}

static class ViewHolder {
    ImageView imageView;
}
```
