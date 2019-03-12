# Thread线程笔记

UI线程模型（单一线程模型） 主线程负责所有用户界面的显示以及用户操作的响应事件，是应用程序从Android的UI工具包（Android.widget和Android.view）中所有组件的交互线程。不能在主线程之外访问UI工具包。因此主线程又称为UI线程。如果UI线程被阻塞了超过约5秒，应用程序就会被判定为“应用程序没有响应”ANR。

1. 不能阻塞主线程
2. 非UI线程不能访问UI工具包

```java
@Override
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);

    textView = findViewById(R.id.textView);

    // Fail: Only the original thread that created a view hierarchy can touch its views.
    new Thread() {
        @Override
        public void run() {
            int count = 0;
            while (count < 1000) {
                textView.setText("当前TextView的值是" + count);
                try {
                    Thread.sleep(100);
                } catch (Exception e) {
                    e.printStackTrace();
                }
                count++;
            }
        }
    }.start();
}
```

## 解决方案

1. 工作线程尝试访问UI线程，并委托UI线程更新UI
2. 工作线程与UI线程之间通信，让工作线程发送消息给UI线程，让UI线程根据消息更新UI
3. 使用AsyncTask

### 方案1：从工作线程访问UI线程

1. `Activity.runOnUiThread(Runnable)`
2. `View.post(Runnable)`
3. `View.postDelayed(Runnable, long)`

`View.post(Runnable)`

```java
new Thread() {
    @Override
    public void run() {
        count = 0;
        while (count < 1000) {
            textView.post(new Runnable() {
                @Override
                public void run() {
                    textView.setText("当前计数器：" + count);
                }
            });

            try {
                Thread.sleep(100);
            } catch (Exception e) {
                e.printStackTrace();
            }
            count++;
        }
    }
}.start();
```

### 方案3：使用AsyncTask

`AsyncTask<T param, T progress, T result>`

- param 发送给异步任务所需的参数类型
- progress 后台运算过程中进度的参数类型
- result 后台运算的结果类型

不需要的泛型参数可以标记为`Void`

任务通常经历的4个步骤：

1. `onPreExecute()` 执行异步任务之前，运行在UI线程中
2. `doInBackground(Params... )` 执行在后台的长时间操作；运行的结果通过此步骤返回，并被传递到最后一步。此步中可以使用`publishProgress(progress... )`发布进度
3. `onProgressUpdate(progress... )` 调用`publishProgress()`之后在UI线程中执行
4. `onPostExecute(result... )` 后台操作结束后在UI线程中执行

上述4步骤中的方法不能手动调用，故AsyncTask实例必须在UI线程中创建，`execute()`方法必须在UI线程中调用。

#### 示例：下载图片并展示进度

```java
@Override
public void onClick(View view) {
    if (view.getId() == R.id.button) {
        new MyAsyncTask().execute("https://qfstudio.net/i_bg_cool.jpg");
    }
}

public class MyAsyncTask extends AsyncTask<String, Integer, byte[]> {
    @Override
    protected void onPreExecute() {
        progress.setProgress(0);
    }

    @Override
    protected byte[] doInBackground(String... strings) {
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        try {
            URL url = new URL(strings[0]);
            HttpURLConnection con = (HttpURLConnection) url.openConnection();
            Log.i("Code", new Integer(con.getResponseCode()).toString());
            if (con.getResponseCode() == 200) {
                InputStream in = con.getInputStream();
                long length = con.getContentLength();
                int current = 0, temp;
                byte[] buff = new byte[1024];
                while ((temp = in.read(buff)) != -1) {
                    current += temp;
                    int progress = (int)(current/(double)length * 100);
                    publishProgress(progress);
                    out.write(buff, 0, temp);
                    out.flush();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return out.toByteArray();
    }

    @Override
    protected void onProgressUpdate(Integer... values) {
        progress.setProgress(values[0]);
    }

    @Override
    protected void onPostExecute(byte[] result) {
        if (result != null && result.length != 0) {
            Bitmap bm = BitmapFactory.decodeByteArray(result, 0, result.length);
            imageView.setImageBitmap(bm);
        } else {
            Toast.makeText(MainActivity.this, "网络连接出现了问题", Toast.LENGTH_LONG).show();
        }
    }
}
```

#### 示例：取消异步任务

调用`cancel(boolean)`来取消异步任务：调用此方法后`isCanceled()`返回true，并且异步任务结束后运行`onCancel(Object)`而不是`onPostExecute()`

应该在`doInBackground()`中检查`isCanceled()`的值。

```java
@Override
public void onClick(View view) {
    if (!onGoing) {
        task = new MyAsyncTask();
        task.execute("https://qfstudio.net/i_bg_cool.jpg");
        onGoing = true;
    } else {
        task.cancel(true);
        onGoing = false;
    }
}

public class MyAsyncTask extends AsyncTask<String, Integer, byte[]> {
    @Override
    protected void onPreExecute() {
        progress.setProgress(0);
    }

    @Override
    protected byte[] doInBackground(String... strings) {
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        try {
            URL url = new URL(strings[0]);
            HttpURLConnection con = (HttpURLConnection) url.openConnection();
            Log.i("Code", new Integer(con.getResponseCode()).toString());
            if (con.getResponseCode() == 200) {
                InputStream in = con.getInputStream();
                long length = con.getContentLength();
                int current = 0, temp;
                byte[] buff = new byte[1024];
                while ((temp = in.read(buff)) != -1) {
                    current += temp;
                    int progress = (int)(current/(double)length * 100);
                    publishProgress(progress);
                    out.write(buff, 0, temp);
                    out.flush();

                    if (isCancelled()) break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return out.toByteArray();
    }

    @Override
    protected void onProgressUpdate(Integer... values) {
        progress.setProgress(values[0]);
    }

    @Override
    protected void onCancelled() {
        Toast.makeText(MainActivity.this, "已取消", Toast.LENGTH_LONG).show();
    }

    @Override
    protected void onPostExecute(byte[] result) {
        if (result != null && result.length != 0) {
            Bitmap bm = BitmapFactory.decodeByteArray(result, 0, result.length);
            imageView.setImageBitmap(bm);
        } else {
            Toast.makeText(MainActivity.this, "网络连接出现了问题", Toast.LENGTH_LONG).show();
        }
    }
}
```
