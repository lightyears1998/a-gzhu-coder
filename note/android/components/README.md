# Components常用组件笔记

## AssetManager

路径不需要以"/"开头

## Toast

`Toast.makeText(context, "hint", Toast.LENGTH_LONG).show()`

自定义Toast

```java
View layout = getLayoutInflater().inflate(R.layout.dialog, null);
Toast toast = new Toast(this);
toast.setGravity(Gravity.BOTTOM, 0, 20);
toast.setDuration(Toast.LENGTH_LONG);
toast.setView(layout);
toast.show();
```

## Notification

状态栏通知

### NotificationManager and NotificationChannel

创建通知之前需要设置NotificationManager和Channel

```java
channel = new NotificationChannel(channelId, channelName, NotificationManager.IMPORTANCE_DEFAULT);
manager = (NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);
manager.createNotificationChannel(channel);
```

### 普通通知

```java
NotificationCompat.Builder builder = new NotificationCompat.Builder(this, channelId);
builder.setContentTitle("这是通知的标题")
        .setSmallIcon(R.drawable.ic_launcher_foreground)  // 必须设置小图标
        .setContentText("这是通知的内容")
        .setDefaults(Notification.DEFAULT_SOUND | Notification.DEFAULT_VIBRATE);

Intent intent = new Intent(this, NextActivity.class);
intent.putExtra("msg", "通知的内容");

// PendingIntent.FLAG_ONE_SHOT 一次性通知
PendingIntent pendingIntent = PendingIntent.getActivity(this, 1, intent, PendingIntent.FLAG_ONE_SHOT);
builder.setContentIntent(pendingIntent);
manager.notify(1, builder.build());
```

### 进度条通知

```java
new Thread() {
    @Override
    public void run() {
        int notificationId = 100;

        NotificationCompat.Builder builder = new NotificationCompat.Builder(MainActivity.this, channelId);
        builder.setSmallIcon(R.drawable.ic_launcher_foreground)
                .setContentTitle("正在滚动进度条");
        for (int i=0; i<=100; ++i) {
            builder.setProgress(100, i, false);
            manager.notify(notificationId, builder.build());
            try {
                Thread.sleep(200);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        builder.setContentTitle("滚动完成");
        manager.notify(notificationId, builder.build());
    }
}.start();
```

### 大视图通知

1. 设置builder
2. 设置style
3. 发送通知

```java
NotificationCompat.Builder builder = new NotificationCompat.Builder(this, channelId);
builder.setSmallIcon(R.drawable.ic_launcher_foreground);

switch ((int)Math.floor(Math.random()*3)) {
    case 0:
        NotificationCompat.InboxStyle inboxStyle = new NotificationCompat.InboxStyle();
        inboxStyle.setBigContentTitle("这是一条大型标题哦");
        inboxStyle.addLine("第一条通知");
        inboxStyle.addLine("第二条通知");
        inboxStyle.addLine("第三条通知");
        inboxStyle.setSummaryText("本次一共发送了3条通知");
        builder.setStyle(inboxStyle);
        break;
    case 1:
        NotificationCompat.BigTextStyle bigTextStyle = new NotificationCompat.BigTextStyle();
        bigTextStyle.setBigContentTitle("这是一条大标题");
        bigTextStyle.setSummaryText("下面是一条大标题");
        builder.setStyle(bigTextStyle);
        break;
    case 2:
        NotificationCompat.BigPictureStyle bigPictureStyle = new NotificationCompat.BigPictureStyle();
        bigPictureStyle.bigPicture(BitmapFactory.decodeResource(getResources(), R.drawable.ic_launcher_foreground));
        bigPictureStyle.setSummaryText("下面是一张很大的图片");
        builder.setStyle(bigPictureStyle);
        break;
}

manager.notify(4, builder.build());
```

### 自定义通知

参考RemoteView以及`setContent()`

```java

```

并不是所有的控件都可以在通知区域显示 比如switch就不行

通知区域的高度是有限的，不能无限占用

## Dialog

对话框

1. 创建builder对象，并设置对话框参数
2. 设置所显示的内容
3. 为对话框中的空间绑定监听器
4. 使用builder生成Dialog对象
5. 调用builder的show方法显示对话框

### AlertDialog

```java
AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
builder.setTitle("这是一场开发者测试");
builder.setMessage("我是新手开发者Jack");
builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
    @Override
    public void onClick(DialogInterface dialog, int which) {
        Log.i("TAG", "用户点击了确认按钮");
    }
});

builder.show();
AlertDialog alertDialog = builder.create();
alertDialog.show();

```

### ProgressDialog

### DatePickerDialog

1. 创建DatePickerDialog.OnDateSetListener
2. 创建DatePickerDialog
3. show()

```java
Calendar calendar = Calendar.getInstance();
int year = calendar.get(Calendar.YEAR);
int month = calendar.get(Calendar.MONTH);
int day = calendar.get(Calendar.DAY_OF_MONTH);

DatePickerDialog.OnDateSetListener onDateSetListener = new DatePickerDialog.OnDateSetListener() {
    @Override
    public void onDateSet(DatePicker view, int year, int month, int dayOfMonth) {
        textView.setText("" + year + " " + month + " " + dayOfMonth);
    }
};

DatePickerDialog dialog = new DatePickerDialog(this, onDateSetListener, 2018, 8, 8);
dialog.show();
```

### TimePickerDialog

### 自定义Dialog

1. `setView()`
2. `inflate()`

```java
LayoutInflater inflater = LayoutInflater.from(this);
final View dialogView = inflater.inflate(R.layout.dialog, null);
AlertDialog.Builder builder = new AlertDialog.Builder(this);
builder.setTitle("自定义对话框控件");
builder.setView(dialogView);

builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
    @Override
    public void onClick(DialogInterface dialog, int which) {
        AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
        builder.setTitle(((TextView)dialogView.findViewById(R.id.editText1)).getText());
        builder.setMessage(((TextView)dialogView.findViewById(R.id.editText2)).getText());
        builder.show();
    }
});

builder.show();
```

### Dialog生命周期管理

为Dialog对象分配一个唯一id，当使用`showDialog(int id)`显示对话框时，Activity检查持有该id的Dialog对象是否存在，如果存在则直接显示

- 重写`onCreateDialog(int id)`
- 可以操作`onPrepareDialog(int id, Dialog dialog)`

## PopupWindow

IO blocked

## Menu

- OptionMenu
- ContextMenu
- SubMenu
- PopupMenu

## TextView

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

<http://www.runoob.com/w3cnote/android-tutorial-edittext.html>

drawableXxx

autolink

融合Html

部分可点击TextView：SpannableString

## EditText

属性

- hint
- textColorHint
- selectAllOnFocus
- inputType
- singleLine

支持HTML标签 `<b>`, `<i>`, `<u>`

`getText().toString()`

## Button

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

也可以在xml中定义点击处理事件

## ImageButton

通过src属性链接到文件

## ImageView

属性

- src 内容，不会自动拉伸
- background 背景，根据View宽度自动拉伸

## RadioButton & CheckBox

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

## ToggleButton

属性

- checked
- textOn, textOff 按下按钮，断开按钮时显示的文本

`check()`是否被选中

## Switch

开关

## ProgressBar

```java
getMax();
getProgress();
getSecondaryProgress();  // 类似与视频缓冲进度
increasementProgressBy(int diff);
isIndeterminate();  // 是否处于不确定模式下
setIndeterminate(boolean bool)  // 设置不确定模式
```

## SeekBar

拖动条

## RatingBar

星级评分条

## ScrollView

`fullScroll()`

## Date and Time

TextClock, AnalogClock, Chronometer, DatePicker, TimePicker, CalendarView

### DatePicker

属性

- startYear, endYear 均是包含区间

月份设置 0~11

`datePicker.init(year, month, day, listener)`

### TimePicker

`setIs24HourView()`

`OnTimeChangedListener`

## AutoCompleteTextView

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

## ExpandableListView

可折叠列表

## ViewFlipper

翻转视图 用于制作用户第一次登陆的引导页面等
