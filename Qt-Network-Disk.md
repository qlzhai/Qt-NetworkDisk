# C++网盘系统

来自[哔哩哔哩](https://www.bilibili.com/video/BV1bR4y1774v/?spm_id_from=333.337.search-card.all.click)与[Gitee](https://gitee.com/goingme/qt-network-disk-project)上C++网盘项目的学习。

![image-20240409220237795](C:\Users\Qianlong\AppData\Roaming\Typora\typora-user-images\image-20240409220237795.png)

背景：随着时代的发展，业务数据量的剧增及移动办公需求，人们对内存的需求越来越强，传统的存储产品，在容量及携带型日益不能满足人工的工作需求，网盘在此背景下应运而生。网盘是能够提供文件同步，备份及共享等服务的网络云存储平台。可以随时随地的把照片、音乐、视频、文档等轻松地保存到网盘，无须担心文件丢失。通过网盘，用户可以多终端上传和下载、管理、分享文件，一切就变得轻而易举。

描述：随时随地上传下载、编辑和分享**文件**；搜索好友、加好友、**好友**聊天等

要点：

* 多线程。考虑多文件同时上传、信息输入和接受同时进行
* TCP Socket网络编程。用于客户端登录及互联网向服务端传输
* SQLite3数据库。信息在服务端的暂存
* 面向对象编程。通过设计不同的实体对象实现项目开发
* 采用C/S架构，数据库存储用户信息，磁盘存储用户文件（C/S、B/S架构可参考[C/S、B/S架构详解](https://blog.csdn.net/weixin_74021557/article/details/131378939#:~:text=CS架构（Client-Server Architecture）是一种分布式计算模型，其中客户端和服务器之间通过网络进行通信。,在这种架构中，客户端负责向服务器发送请求，并接收服务器返回的响应。 服务器则负责处理客户端的请求，并返回相应的结果。 CS架构通常用于构建大型的网络应用程序，如Web应用程序、电子邮件系统、数据库管理系统等。)）

本项目所使用的软件以及版本：

* sqlite3
* Qt6.6.0

## 设计

Qt网盘系统主要由Qt creator实现了客户端/服务器的设计，调用了tckSocket发送数据进行两端信息往来

使用了UI控件、socket网络编程、界面切换等一些基础的功能。服务器和多客户端之间通过QList链表存放对应的socket连接，负责与不同的客户端交互

UI控件通过connect连接信号槽和处理函数处理

数据库信息通过QSqlQuery的exec函数获取SQL查询结果并处理对应位置的value进行处理

界面切换：通过show和hide进行界面的切换、增加和关闭；也包括点击图书、好友等控件后执行界面处理的命令

## 一.数据库

### 基本操作

```sqlite
dir 查看当前目录下的文件
cd 进入文件夹
//打开数据库
sqlite3 cloud.db 

//创建数据库
D:\>sqlite3 ./cloud.db

//创建表
create table usrInfo(id integer primary key autoincrement,
...> name varchar(32) unique,
...> pwd varchar(32)
...> online integer default 0);
create table friend(id integer not null,
...> friendId integer not null,
...> primary key(id,friendId));

//查看数据库张的所有表
.tables

//向表中插入数据
insert into usrInfo(name,pwd) values('jack','jack'),('rose','rose'),('lucy','lucy');

//查询指定表
select * from usrInfo;

//更新表操作
update usrInfo set online=1 where name='%1' and pwd='%2';

//删除表中数据
delete from friend where id = 1 and friendId = 2;

//常用
update usrInfo set online=0 where name='jack';
```

![image-20240330111632604](C:\Users\Qianlong\AppData\Roaming\Typora\typora-user-images\image-20240330111632604.png)

## 二.客户端与服务器端的通信

### 1.加载配置文件

将服务器IP和PORT信息**填入配置文件**中；

将配置文件作为资源文件**添加到资源文件**中；

程序**运行时加载**配置文件中的数据。

### 2.tcp客户端连接服务器

### 3.服务器响应tcp客户端

## 三.弹性结构体

1.结构体中的最后一个成员设置为空的数组类型

2.采用malloc动态分配内存

3.设置内存中的所有数据为0

## 四.常见问题与现有bug

环境加入：在.pro文件加入   QT       += core gui network sql。其中network表示网络编程环境，sql表示数据库环境。

客户端结束之后，需要把客户端对应的socket删除掉，并把用户对应的登录状态修改为0.

对于私有成员变量，可以定义一个公有的接口来访问。

## bug：

### 0.客户端在线问题

有时候明明客户端已经关闭了，但是数据库中的用户仍然显示在线状态

如果服务器端关闭了，客户端如何处理？

如何服务器端关闭了，客户端的用户是否应该立即设置为不在线状态？



### 1.查看所有所有在线用户部分

//客户端接收到服务器端发送的查看所有用户回复信号
    case ENUM_MSG_TYPE_ALL_ONLINE_RESPOND:
        OpeWidget::getInstance().getFriend()->showALLOnlineUsr(pdu);
        break;
        //这里目前存在bug，也就是会重复显示，lineEdit中保留了上一次的结果



### 2.添加好友部分内容不完整

2.1自己添加自己为好友？ 已解决

2.2只有用户在线才能添加？



### 3.刷新好友列表部分

3.1显示好友是否在线

3.2将在线和非在线的好友分开存放

3.3再点击一次刷新好友不会覆盖，也就是会在原来的界面的下边接着显示，会重复

3.3B站上采用QStringList链表的形式存储好友用户姓名，可能会存在重复性问题。

​		改进：采用set集合存储



### 4.删除好友

4.1在删除好友前应该判断双方是否是好友

4.2删除成功后应该立即刷新好友列表



### 5.群聊

好友只有在线才能收到消息，不在线就收不到消息，即使好友上线了，也无法缓存之前不在线时候的消息，添加好友那一部分也是。



### 6.创建文件夹

创建文件夹成功之后应该自动更新窗口的文件信息



### 7.删除文件夹

删除成功之后应该立即刷新文件列表



### 8.重命名文件

重命名文件之后应该自动刷新文件列表



### 9.上传文件

上传文件的时候应该判断所上传的文件是否已经存在

是否能够同时上传？

上传成功之后应该立即刷新当前目录  已解决

目前 只能上传和下载txt文本格式的文件



### 10刷新文件夹

多次点击 刷新文件夹 命令会出现bug



### 11注销功能尚未完成



### 12多线程功能尚未实现