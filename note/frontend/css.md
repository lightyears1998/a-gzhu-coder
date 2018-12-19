# Cascading Style Sheet笔记

- [Mozilla CSS参考](https://developer.mozilla.org/en-US/docs/Web/CSS)

颜色选择工具

1. [Colors on the Web](http://www.colorsontheweb.com/Color-Tools/Color-Wizard) 众多颜色工具
2. [Paletton.com](http://paletton.com) 在色环上选择并且提供颜色使用示例
3. [Adobe Color CC](https://color.adobe.com) 强大的色环工具，并且提供从图像中自动提取色彩的工具

## 基本概念

- `选择器 { 声明属性 : 声明值 }`
- 内联样式 `<tag style="pro1: val; pro2: val" />`
- `/* 注释 */`

### “层叠”次序

渲染方式优先级别

- 浏览器默认设置
- 外部样式
- 嵌入式样式
- 内联样式
- html属性

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

## 颜色

- 颜色名称 `red`
- 十六进制颜色码 `#FF0000`
- 简写十六进制颜色码 `#F00`
- rgb `rgb(255, 0, 0)`
- hsl `hsl(0%, 100%, 50%)`

## 图像

- 图像互换格式 GIF 256色 透明 动画 无损 交错
- 联合照片专家小组 JEPG 数百万色 无透明 无动画 有损 渐进式
- 可移植网络图形格式 PNG 数百外色 透明 无动画 无损 交错
- webp

## 盒 border

- border-width
- border-style
- border-color

margin, boarder, padding

- margin
- boarder
- padding

浮动

- float: left | right 元素浮动到容器的左侧|右侧
- clear: left | right | both 清除浮动
- overflow

## 常用属性

字体

- font-size
- font-family

颜色

- color
- backgrond-color

图像

- background-image
- background-repeat
- background-position
- background-attachment
- background-clip 背景图像的绘制区域
- background-origin 背景图像的位置
- background-size

圆角和阴影

- border-radius
- box-shadow
- opacity 透明度

渐变

- background-image: linear-gradient(to bottom, #FFFFFF, #00FF00);

## Grid

### 创建布局

1. `grid-template-columns: 20% 20% 20% 20% 20%;`

    还可以使用百分比以外的数值来标定宽度，例如：`px`, `em`和Grid特有的单位`fr`（按比例分配格点时使用，每个`fr`为一份）

    使用fr作为单位时，fr的宽度将在最后计算，`grid-template-columns: 50px 1fr 1fr 1fr 50px;`。

2. `grid-template: <row> / <column>`是上述代码的简写

### 指定行与列

使用负数来标定行或列时，`-1`是指逆序第一条网格线。

1. `grid-column-start`, `grid-column-end`结合使用时，渲染结果是`[两者中较小值, 较大值)`（即夹在初始格线与停止格线之间的部分）
2. `span`可用于在给出了`start`或`end`时，指定格子拓展的长度
3. `grid-column: <start> / <end>;`是上述语法的简写

类似的还有`grid-row`的使用。

1. `grid-area: <row-start> / <column-start> / <row-end> / <column-end>;`是上述语法的简写

未指定`grid-column-start`等位置元素时，元素按源代码中出现的顺序占据一个格点，使用`order: <number>`来改变默认排序，类似于`z-index`。

### 辅助计算

1. `repeat(5, 20%)`展开为`20% 20% 20% 20% 20%`

这个参数顺序挺满足英语简单部分前置的风格的。
