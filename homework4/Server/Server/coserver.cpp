// coserver.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "winsock.h"
#include "stdio.h"
#pragma comment(lib,"wsock32.lib")
#define SERVER_PORT 0x1234
int main(int argc, char* argv[])
{
	WSAData wsa;
	SOCKET s,ns;
	sockaddr_in local,remote;
	int len;
	char recvbuf[4];
	int retval;
	int r;

	WSAStartup(0x101,&wsa);
	
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s == SOCKET_ERROR)
		r = WSAGetLastError();

	local.sin_family = AF_INET;
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_port = htons(SERVER_PORT);

	retval = bind(s,(sockaddr*)&local,sizeof(local));
	if(retval != 0)
		r = WSAGetLastError();

	retval = listen(s,7);
	if(retval != 0)
		r = WSAGetLastError();

	while(1){
		len = sizeof(remote);
		ns = accept(s,(sockaddr*)&remote,&len);
		if(ns == SOCKET_ERROR)
			r = WSAGetLastError();

		retval = recv(ns,recvbuf,2,0);
		if(retval == SOCKET_ERROR)
			r = WSAGetLastError();
		
		retval = send(ns,"ACK",3,0);
		if(retval == SOCKET_ERROR)
			r = WSAGetLastError();

		closesocket(ns);
		//retval = closesocket(ns);
		//if(retval != 0)
			//r = WSAGetLastError();
	}

	WSACleanup();
	return 0;
}
