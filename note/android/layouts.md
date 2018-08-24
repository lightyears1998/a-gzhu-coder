# Layouts笔记

## 常用布局

### LinearLayout

match_parent == fill_parent

布局自身

- layout_gravaty
- layout_width
- layout_height
- divider
- *showDivider* none, beginning, end, middle（每两个组件之间）
- dividerPadding

子元素的对齐方式

- *orientaion* horizontal(default), vertical
- *gravity*

layout_width与layout_weight组合

- 对于在horizontal对齐的LinearLayout内的两个View，如果View的layout_width被设置为0dp，并设置了layout_weight属性，将按权重分配layout_width
- 如果容器内View被设置为match_parent，并设置了layout_weight属性，设有4份View，每份View的最终权重为(1-(份数-1)*(权重/权重之和))；如View权重1, 2, 3，则最终Layout_width为2, 1, 0
- wrap_content则视情况而定，居于前述两种情况之间

LinearLayout不能在同一水平线上布置一左一右的两个控件

给予已指定weight的子View设置0dp的高度，可以优化测量

属性

- `baselineAligned` 子View是否根据baseline对齐

### RelativeLayout

- gravity / ignoreGravity
- 根据父容器定位 layout_alignParentXxx (Left | Right | Bottom | Top) layout_centerInParent (Horizontal | Vertical)
- 根据兄弟组件定位 layout_toXxxOf (Left | Right) layout_above(below) layout_alignXxx (Left | Right | Top | Bottom)
- layout_margin（外边距）
- layout_padding（内填充）

另外，*梅花布局*

### TableLayout

属性

- collapseColumns 指定隐藏行
- shrinkColumns 指定可收缩行
- stretchColumns 制定可伸展行

单元格

- layout_column
- layout_span

### FrameLayout

属性

- foreground 前景色/前景图像
- foregroundGravity

### GridLayout

属性

- columnCount, rowCount

对于布局中的View

- layout_row, layout_column 设置行列 0-based
- layout_rowSpan, layout_columnSpan 设置跨行，设置跨列

### AbsoluteLayout

专业适配当前屏幕

### DrawerLayout

布局根节点必须是DrawerLayout

主题NoActionBar化

```xml
<style name="AppTheme.NoActionBar" parent="AppTheme">
    <item name="windowActionBar">false</item>
    <item name="windowNoTitle">true</item>
</style>
```

自定义Toobar

`onCreate()`

```java
Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
setSupportActionBar(toolbar);
```

渲染菜单

`onCreateOptionMenu(Menu menu)`

```java
public boolean onCreateOptionsMenu(Menu menu) {
    getMenuInflater().inflate(R.menu.main, menu);
    return true;
}
```

Appbar与Drawer联动

```java
DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
        this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close
);
drawer.addDrawerListener(toggle);
toggle.syncState();
```

### ViewPager

容器类 经常与Fragment一起使用

需要PageAdapter 存在FragmentPageAdapter以及FragmentStatePageAdapter