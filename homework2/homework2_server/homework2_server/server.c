#include <WinSock2.h>
#include<stdio.h>

#define SERVER_PORT 10000
#define QUEUE 20
#define BUFSIZE 4096

int main() {
	int ret;
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	ret = WSAStartup(sockVersion, &wsaData);
	if (ret != 0) 
	{
		printf("Couldn't Find a Useable Winsock.dll!\n");
		exit(-1);
	}

	SOCKET msock;
	msock = socket(AF_INET, SOCK_STREAM, 0);
	if(msock==INVALID_SOCKET)
	{ 
		printf("Create Socket Failed!\n");
		exit(-1);
	}

	struct sockaddr_in servaddr;
	ZeroMemory(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERVER_PORT);

	int ret2;
	ret2 = bind(msock, (struct sockaddr*)&servaddr, sizeof(struct sockaddr_in));
	if (ret2 < 0)
	{
		printf("Server Bind Port:%d Failed!\n", SERVER_PORT);
		exit(-1);
	}

	int ret3;
	ret3 = listen(msock, QUEUE);
	if (ret3 < 0)
	{
		printf("Listen Failed!\n");
		exir(-1);
	}

	SOCKET ssock;
	struct sockaddr_in clientaddr;
	int len = sizeof(clientaddr);
	ZeroMemory(&clientaddr, sizeof(clientaddr));
	ssock = accept(msock, (struct sockaddr*)&clientaddr, &len);
	if (ssock == INVALID_SOCKET) {
		printf("Accept Failed!\n");
		exit(-1);
	}

	char buf[BUFSIZE];
	ZeroMemory(buf, sizeof(buf));
	int num;
	num = recv(ssock, buf, sizeof(buf), 0);
	if (num < 0)
	{
		printf("Receive Data Failed!\n");
		exit(-1);
	}

	char *buffer = "HELLO!";
	num = 0;
	num = send(ssock, buffer, strlen(buffer), 0);
	if (num != strlen(buffer))
	{
		printf("Send Data Failed!\n");
		exit(-1);
	}

	closesocket(ssock);

	closesocket(msock);
	WSCleanup();
}



