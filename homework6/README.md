# 项目6自由设计
## 介绍
基于《Qt及Qt Quick开发实战精解》的局域网聊天软件设计为基础开发的一款即时IM软件。

## 计划安排
首先实现基本聊天功能  
之后仿照同级目录下的Chat与QQ做一个Demo出来  
后续可能涉及:
- [X] 注册登录功能
- [X] 导入导出数据库
- [ ] 登录界面优化
- [ ] 多线程
- [ ] 界面优化
- [ ] 功能优化


## 目前完成
![Snipaste_2018-04-11_21-17-25.png](https://upload-images.jianshu.io/upload_images/7154520-50ab7f018809731a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![Snipaste_2018-04-11_21-17-42.png](https://upload-images.jianshu.io/upload_images/7154520-dc03013143e9442c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

单独的数据库登录注册功能已经完成，但是暂时还聊天室进行交互的功能。想法是注册账号或者只有已知的账户和密码才能进入聊天室。这样的话聊天室的程序可能就需要写在Qdialog中了；之前写过在QDialog中加入图表，结果是显示不出来的。如果聊天室仍然如此，可能需要变更方案。

！[](https://img.shields.io/badge/{QtChat}-{building}-{orange}.svg)
