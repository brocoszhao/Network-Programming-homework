// nblksrv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winsock.h"
#include "stdio.h"
#pragma comment (lib,"wsock32.lib")

#define SERVER_PORT 0x1234

int main(int argc, char* argv[])
{
	SOCKET sock,newsock;
	struct sockaddr_in server;
	int len;
	long retval;
	char buf[128];
	WSAData wsa;
	unsigned long arg;

	WSAStartup(0x101,&wsa);

	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == INVALID_SOCKET){
		return 0;
	}

	server.sin_addr.S_un.S_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	if(bind(sock,(struct sockaddr*)&server,sizeof(server)) < 0){
		retval = WSAGetLastError();
		printf("Binding error\n");
		return 0;
	}

	listen(sock,5);

	arg = 1;
	ioctlsocket(sock,FIONBIO,&arg);

	while(1){
		len = sizeof(server);
		do{
			if((newsock = accept(sock,(sockaddr*)&server,&len)) == INVALID_SOCKET){
				retval = WSAGetLastError();
				if(retval == WSAEWOULDBLOCK)
					continue;
				else
					break;
			}
		}while(newsock == INVALID_SOCKET);
		printf("accept connection\n");
	
		arg = 1;
		ioctlsocket(newsock,FIONBIO,&arg);

		do{
			retval = recv(newsock,buf,sizeof(buf),0);
			if(retval == SOCKET_ERROR ){
				retval = WSAGetLastError();
				if(retval == WSAEWOULDBLOCK)
					continue;
				break;
			}
			else if(retval == 0){
				retval = WSAGetLastError();
				break;
			}
			buf[retval] = 0;
			printf("->%s\n",buf);
			// send a ack back
			retval = send(newsock,"ACK by server",13,0);
			if(retval == SOCKET_ERROR){
				retval = WSAGetLastError();
				break;
			}
		}while(1);
		
		closesocket(newsock);
		printf("close socket\n");
	}

	closesocket(sock);
	WSACleanup();
	free(buf);
	return 0;
} 