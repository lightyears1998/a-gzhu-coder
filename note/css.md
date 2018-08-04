## 基本格式

- `选择器 { 声明属性 : 声明值 }`
- 内联样式 `<tag style="pro1: val; pro2: val" />`

内嵌样式

```html
<head>
<style>
body {
    background-color: #CCFFFF;
    color: #000033;
}
</style>
</head>
```

外部连接模式

```html
<link rel="stylesheet" href="linked.css" type="text/css" />
```

### 选择器

类选择器

```css
.class {
    /* 单行/多行注释 */
}
```

id选择器

```css
#id {
    /* 省略内容 */
}
```

派生选择器

```css
main p {
    /* 省略内容 */
}
```

### 层叠

渲染方式优先级别

- 浏览器默认设置
- 外部样式
- 嵌入式样式
- 内联样式
- html属性

## 颜色

- 颜色名称 `red`
- 十六进制颜色码 `#FF0000`
- 简写十六进制颜色码 `#F00`
- rgb `rgb(255, 0, 0)`
- hsl `hsl(0%, 100%, 50%)`

## 盒

## 常用属性

字体

- font-size
- font-family

颜色

- color
- backgrond-color
