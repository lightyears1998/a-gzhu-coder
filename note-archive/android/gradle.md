# Gradle笔记

## 基本概念

- DSL Domain Specific Language
- JKS Java Keystore

构建生命周期

- 初始化 读取init.gradle, gradle.properties并设置在`__settings.gradle__`中列出的子项目
- 配置 解析构建脚本，并构建模型，包括DAG
- 运行

## 基础配置

- 仓库 `repositories {}`
- 依赖 `dependencies {}`

sdk版本

- applicationId 应用程序package名 应用程序商店中的唯一id
- minSdkVersion 最小Android版本
- targetSdkVersion 目标Android版本
- versionCode
- versionName 版本号

Project Structure窗口

升级到新版本的Gradle的两种方法

1. 添加wrapper任务到build.gradle并生成新的wrapper脚本
2. 修改gradle-wrapper.properties中的distibutionUrl

## 从命令行构建

`gradlew.bat` gradle wrapper

## 依赖配置

### 等价配置

`implementation group: 'org.apache.httpcomponents' , name: 'httpclient-android' , version: '4.3.5.1'` 等价于 `implementation 'org.apache.httpcomponents:httpclient-android:4.3.5.1'`

## 源

- 电子工业出版社 2017 《巧用Gradle构建Android应用 Gradle Receipe for Android》 Ken Kousen，李建 书是好书，但是翻译实在不敢恭维；这是因为基础知识不足不能深入理解书的主题
