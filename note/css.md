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


### 颜色

- 颜色名称 `red`
- 十六进制颜色码 `#FF0000`
- 简写十六进制颜色码 `#F00`
- rgb `rgb(255, 0, 0)`
- hsl `hsl(0%, 100%, 50%)`

## 常用属性

- color
- backgrond-color
