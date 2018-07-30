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

### ShapeDrawable

### 反编译

apktool

dex2jar

### Logcat

verbose, debug, info, warn, error