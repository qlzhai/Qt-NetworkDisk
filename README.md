# QT网盘项目

来自[b站项目](https://www.bilibili.com/video/BV1bR4y1774v/?spm_id_from=333.999.0.0)的C++网盘项目学习

![网盘1](图片/网盘1-1678981548229.png)

## 介绍
QT用C++实现的网盘开发，包括了建立客户端、服务器、TCP数据收发、SQL等实现

## 软件架构
客户端实现了ui界面（登录、好友、文件）的设计，服务器实现了与SQL数据库的交互，相互之间使用了统一的数据协议收发并针对文件延时接收保证数据接收时的正确性。

### GUI及功能演示

#### 服务器

**运行**TcpServer项目，打开服务器：

<img src="图片/image-20230731102348561.png" alt="image-20230731102348561" style="zoom:50%;" />



用户信息查询命令（数据库文件位于TcpServer目录）：

```sqlite
sqlite3 cloud.db             
.table
select * from usrInfo;     
select * from friend;                                                                 
```

<img src="图片/image-20230731105420586.png" alt="image-20230731105420586" style="zoom: 67%;" />



用户文件管理（用户文件位于book目录下）：

![image-20240411114534511](E:\Qt_network_disk\图片\文件管理.png)

#### 客户端

**运行**一个TcpClient项目，打开一个客户端：

<img src="图片/image-20230731110332011.png" alt="image-20230731110332011" style="zoom:67%;" />

账户在db文件中，如jack-jack、rose-rose等，也可选择注销或创建用户：

<img src="图片/image-20230731110720131.png" alt="image-20230731110720131" style="zoom:67%;" />



Rose登录后界面，刷新好友后可看到jack在线（已登录）：

<img src="图片/image-20230731182213707.png" alt="image-20230731182213707" style="zoom:50%;" />



选择jack，私聊，jack客户端出会跳出对应消息：

<img src="图片/image-20230731182432493.png" alt="image-20230731182432493" style="zoom: 33%;" />



选择图书，进入后刷新图书，可看到用户的文件，可以进行任意操作：

<img src="图片/image-20230731182740997.png" alt="image-20230731182740997" style="zoom: 50%;" />

### 源码概述

项目主要使用统一的自定义PDU数据传输协议在tcpclient和tcpserver之间进行数据传输、界面跳转。

* protocol为自定义的数据传输协议，在需要客户端和服务器之间保持一致性

* 服务器端定义了与数据库和客户端独立的连接，依照客户端的信号对本地的文件及数据库进行管理和信息反馈

* 客户端定义了不同的ui界面：tcpclient客户端登录界面、online在线好友界面、privatechat私聊界面及book.cpp中直接编写的文件界面

* 下图包含了客户端中显示图书时，对应的图标；config文件则基本了本地ip地址和端口。

![image-20230731184223355](图片/image-20230731184223355.png)



## 安装教程

1.  安装QT软件和SQL3
2.  可使用C++修改实现的程序

## 使用说明

1.  TcpClient为设计的客户端程序
2.  TcpServer为设计的服务器程序
3.  运行服务器，运行客户端登录账户可实现本地不同客户端之间的交互，账户信息和好友关系存在sever文件中的cloud.db文件下
4.  程序未完全打包，直接打开可能有问题

## 常见问题

1. 无法打开多个客户端，构建和运行->在Stop applications before building中选择“None”
2. 关闭客户端后部分用户登录异常，初步可使用sql重置在线信息
3. 用户信息出错？检查cloud.db中的数据库
4. 登录用时？秒级以内，文件传输则与大小相关

## 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


## 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
