# Network网络笔记

HTTP1.1 持久性连接 8个请求方法

- OPTIONS 返回服务器对特定资源支持的HTTP方法
- HEAD 请求GET的响应头
- GET 请求数据（单次可能不超过2kb）
- POST 请求数据
- PUT 向位置上传
- DELETE 请求服务器删除
- TRACE 回显服务器收到的请求，用于测试或诊断
- CONNECT 预留给能将连接该为管道方式的代理服务器

## 响应状态

1. 1xx 指示信息
2. 2xx 成功信息
3. 3xx 重定向信息
4. 4xx 客户端错误
5. 5xx 服务器端错误

## HttpClient

Apache提供的HttpClient，Android 6.0中[取消支持](https://developer.android.com/about/versions/marshmallow/android-6.0-changes?hl=zh-cn#behavior-apache-http-client)。

可以使用`HttpURLConnection`类替代，也可以添加依赖使用`implemetation group: 'org.apache.httpcomponents' , name: 'httpclient-android' , version: '4.3.5.1'`。

建议是使用`HttpURLConnection`替代

## 数据解析

### XML的解析

#### SAX：基于事件的XML解析器

解析xml文档时触发一系列回调函数

- `startDocument()`
- `startElement(String uri, String localName, String qName, Attributes attributes)`
- `characters(char[] ch, int start, int length)` start：解析到的字符数组开始的位置
- `endElement(String uri, String localName, String qName, Attributes attributes)`
- `endDocument()`

localName：不含有前缀的本地名称
qName：带有前缀的限定名称

使用步骤

1. 创建解析器工厂 `SAXParserFactory factory = SAXParserFactory.newInstance();`
2. 生产一个解析器对象 `SAXParser parser = factory.newSAXParser();`
3. 从解析器对象中的得到一个XML Reader实例 `XMLReader reader = paser.getXMLReader();`
4. 将自定义的handler注册到XML Reader中 `MyHandler handler = new MyHandler(); reader.setContentHandler(handler);`
5. 将XML文档转变成InputStream，解析正式开始 `parser.parser(is);`

#### Pull

Android内置的XML解析器 允许应用程序主动从解析器中获取事件

### Json的解析

Javasripet Object Notation

- 对象 `{key: value}`
- 数组 `[val1, val2, val3]`

键和值使用双引号包围

#### `org.json`

- JsonObject
- JsonStringer
- JsonArray

#### GSON

`toJson()`, `fromJson()`

#### `FastJson`

阿里巴巴出品
