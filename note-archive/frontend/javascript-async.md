# JavaScript异步编程

## 事件模型

JavaScript是一种动态的单线程语言。

JavaScript处理器在线程空闲之前永远不会运行。JavaScript代码永远不会被中断，因为事件在代码结束运行前不会被触发。

如果队列中至少有一个事件适合于触发，则环境随机挑选一个触发。

```js
for (var i = 1; i <= 3; ++i) {
  setTimeout(function () {
    console.log(i);
  }, 0);
}

// 4; 4; 4
```

```js
for (var i = 1; i <= 3; ++i) {
  setTimeout(function () {
    console.log(i);
  }, 0);
}

// 1; 2; 3;
```

## 异步函数

- IO函数 `XMLHttpRequest`对象
- 计时函数 `setTimeout`, `setInterval`
  浏览器端 `requestAnimationFrame` 允许以60+帧每秒速率运行动画，且避免在后台选项卡中运行动画
  Nodejs `process.nextTick` 尽可能快地触发

**垫片技术（Shim）** 如果浏览器支持`requestAnimationFrame`则使用，否则退而求其次使用`setTimeout`

### 异步函数测试

异步函数永远可以通过以下测试

```js
var functionHasReturned = false;
asyncFunction(function () {
  console.assert(functionHasReturned);
});
functionHasReturned = true;

```

### 间或异步函数

函数有些时候是异步的，但其他时候却不然。

### 缓存型异步函数

### 用回调储存取缔异步递归

避免使用“异步递归”

## 异步操作的模式

1. 回调函数

   ```js
   function (callback) {
       callback();
   }
   ```

2. 事件监听

3. 发布/订阅模式（观察者模式）

## 异步操作的流程控制

https://wangdoc.com/javascript/async/general.html#%E5%BC%82%E6%AD%A5%E6%93%8D%E4%BD%9C%E7%9A%84%E6%B5%81%E7%A8%8B%E6%8E%A7%E5%88%B6

### 串行执行

### 并行执行

### 并行与串行的结合

## 定时器

1. 单次执行 `var timerId = setTimeout(func|code, delay);`

2. 无限次数执行 `var timerId = setInterval(func|code, delay);`

3. `claerTiemout(id)`, `clearInterval(id)`