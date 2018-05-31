// 服务器连接.cpp : 建立连接，收到客户机发送来的字符串后，回送一个ACK字符串给客户机。
//
#include <winsock.h>
#pragma comment(lib,"wsock32.lib")
int main(int argc, char* argv[])
{
	int len;
	char buf[128];
	WSAData wsa;
	SOCKET s, newsock;
	sockaddr_in ser_addr;
	sockaddr_in remote_addr;
	WSAStartup(0x101,&wsa);

	s = socket(AF_INET,SOCK_STREAM,0);
	
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(0x1234);
	
	bind( s , (sockaddr*)&ser_addr ,sizeof(ser_addr));

	//进入监听状态，此处缺一个函数调用
	listen(s, 5);
	
	while(1){
		len = sizeof(remote_addr);

		newsock = accept(  s,  (sockaddr*)&remote_addr   ,&len);
		
		recv( newsock ,buf,sizeof(buf),0);
		send( newsock ,"ACK",3,0);
		closesocket(newsock);
	}
	closesocket(s);
	WSACleanup();
	return 0;
}

