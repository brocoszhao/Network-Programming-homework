#include<stdio.h>
#include<windows.h>
#include<winsock.h>
#define PORT 3000
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")


DWORD WINAPI senddata(LPVOID lpParameter);
DWORD WINAPI recvdata(LPVOID lpParameter);

int main() {
	printf("客户端启动完成！\n");
	SOCKET s, newsock;
	SOCKET sock_array[64] = { 0 };
	sockaddr_in local, object;
	WSAData wsa;
	char object_ip[20];
	int object_port = PORT;

	int flag = 0;
	WSAStartup(0x101, &wsa);

	s = socket(AF_INET, SOCK_STREAM, 0);
	local.sin_family = AF_INET;
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_port = htons(PORT);
	bind(s, (sockaddr*)&local, sizeof(local));

	printf("是否要发起聊天？[1/0]");
	scanf("%d", &flag);

	if (flag == 1) {
		printf("请输入目标IP地址:");
		scanf("%s", object_ip);
		object.sin_family = AF_INET;
		object.sin_addr.S_un.S_addr = inet_addr(object_ip);
		object.sin_port = htons(PORT);
		connect(s, (sockaddr*)&object, sizeof(object));
		printf("连接建立成功！\n");
		HANDLE thread_send = CreateThread(NULL, 0, senddata, &s, 0, NULL);
		HANDLE thread_recv = CreateThread(NULL, 0, recvdata, &s, 0, NULL);
		while (1);
		CloseHandle(thread_send);
		CloseHandle(thread_recv);
	}
	else {
		listen(s, 0);
		printf("进入监听模式!\n");
		int len = sizeof(object);
		newsock = accept(s, (sockaddr*)&object, &len);
		printf("连接建立成功！\n");
		HANDLE thread_send = CreateThread(NULL, 0, senddata, &newsock, 0, NULL);
		HANDLE thread_recv = CreateThread(NULL, 0, recvdata, &newsock, 0, NULL);
		while (1);
		CloseHandle(thread_send);
		CloseHandle(thread_recv);
		closesocket(newsock);
	}
	closesocket(s);
	WSACleanup();
	return 0;
}
DWORD WINAPI senddata(LPVOID lpParameter) {
	printf("发送数据线程启动！\n");
	SOCKET *s = (SOCKET*)lpParameter;
	
	int i;
	while (1) {
		char sendbuf[128] = { 0 };
		scanf("%s", sendbuf);
		send(*s, sendbuf, strlen(sendbuf), 0);
		if (*sendbuf == 'exit')
			break;
		for (i = 0; i < strlen(sendbuf); i++)
			sendbuf[i] = { 0 };
	}
	//closesocket(*s);
	return 0;
}

DWORD WINAPI recvdata(LPVOID lpParameter) {
	printf("接收数据线程启动！\n");
	SOCKET *s = (SOCKET*)lpParameter;
	int i, len;
	while (1) {
		char recvbuf[128] = { 0 };
		len = recv(*s, recvbuf, sizeof(recvbuf), 0);
		printf("%s", recvbuf);
		if (*recvbuf == 'exit')
			break;
		for (i = 0; i < strlen(recvbuf); i++)
			recvbuf[i] = { 0 };
	}
	//closesocket(*s);
	return 0;
}


/*
#include<stdio.h>
#include<windows.h>
int main() {
char a[128] = { 0 };
printf("%s\n", a);
scanf("%s", a);
for (int i = 0; i < strlen(a); i++)
a[i] = { 0 };
printf("%d\n", strlen(a));
printf("%s", a);
return 0;
}
*/