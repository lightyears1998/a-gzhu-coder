# JQuery笔记

## 基础语法

```js
$(seletor).action();
```

## 选择器

- `$(document)`
- `$("#id")`
- `$("tag")`
- `$(".class")`

高级语法

- `$("tag.class")`
- `$("[href]")` 选择所有带href属性的元素
- `$("li:odd")` 选择奇数位置的li元素

## 文档对象 `$(document)`

### 在文档就绪之后执行代码

两种等价方式

```js
$(document).ready(function() {
    // ...
});
```

```js
$(function() {
    // ...
});
```

注意如不使用使用匿名函数，则应提供函数类型的参数，注意不是在参数位置调用函数。

## 事件

- `.click()`  元素被点击时产生的事件

## Ajax

### Get

`$.get(url, callback);`

示例

```js
$.get(url, function(data, status) {
    concole.log(data + status);
});
```

### Post

`$.post(url, data, callback);`
