## 资源限定符

务必指定默认的资源限定符（特定密度的资源除外）

## 密度

dpi

dp单位基于MDPI，一个dp即一个MDPI屏幕上的一个像素

所有字体的尺寸指定为sp

## 支持的图片文件

### 支持栅格图片

- 大幅照片 有损压缩的jpeg
- 其他 png

### Android 5.0 对矢量图片的原生支持

### 9-patch

### XML Drawable

- Layer List
- State List 允许为不同状态指定不同的可绘制对象
- Level List 允许为不同的等级指定不同的可绘制对象
- TransitionDrawable 为两个可绘制对象指定淡入/淡出
- InsertDrawable 允许一个可绘制对象嵌入另一个可绘制对象
- ClipDrawable 常见于进度条 剪切或切掉单独的可绘制对象
- ScaleDrawable 允许缩放
- ShapeDrawable 用XML定义的矩形、椭圆或路径
- VectorDrawable 使用矢量数据绘制
    通过ViewportWidth和ViewportHeight指定虚拟画布尺寸，对实际数据路径中指定的位置赋予一定意义
- AnimatedVectorDrawable 矢量动画
- RippleDrawable 波纹效果

## 字符串

