# homework3:简单的文件服务器
## 基本要求
1.具有用户登录认证功能  
2.用户登录后能够查看服务器文件目录，选择上传或下载文件(客户端与服务器之间传输文件)  
3.设计差错控制协议，是文件传输功能能够在模拟的差错环境下正确传输  

## 进阶要求
1.支持多用户同时在线  
2.客户机在一次文件传输过程中，在不关闭连接情况下继续提出新上传或下载的命令，开始新的传输  
3.支持用户管理，用户密码修改，有全用户的共享目录、各用户的独享目录。  

## 扩展要求
1.客户端具有图形化界面  
2.服务器能在运行过程中获得新的设置，如添加用户、修改指定用户密码。  

## 项目完成程度
-[X] 在linux端成功实现了基本要求。由于文件传输所以考的为TCP协议，所以不需要考虑差错控制。
-[X] 能够显示文件目录(小组中自己负责的部分)，从linux中关于ls的dirent.h，运用了在win下的dirent.h接口实现；此外还利用Windows的api:findfirtfile、findnextfile等进行了多种实现方案。
