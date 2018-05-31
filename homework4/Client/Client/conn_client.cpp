// 连接客户.cpp : 与服务器建立连接后，向服务器发送一个字符串，收到服务器应答后，关闭连接。
//
#include <winsock.h>
#pragma comment(lib,"wsock32.lib")
int main(int argc, char* argv[])
{

	WSAData wsa;
	SOCKET s;
	const char *buf = "I am a client";
	char recvbuf[128];
	sockaddr_in local;
	sockaddr_in server;

	WSAStartup(0x101,&wsa);

	s = socket( AF_INET  , SOCK_STREAM  , 0  );

	local.sin_family = AF_INET;
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_port = htons( 0x3412  );
	
	bind( s,(sockaddr*)&local,sizeof(local));

	server.sin_family = AF_INET;
	server.sin_addr.S_un.S_addr = htonl( INADDR_ANY);
	server.sin_port = htons( 0x1234  );
	
	connect( s ,  ( sockaddr*)&server ,sizeof(server));
	
	send( s ,buf,6,0);
	recv( s ,recvbuf,sizeof(recvbuf),0);

	closesocket(  s );
	system("pause");
	WSACleanup();
	return 0;
}

