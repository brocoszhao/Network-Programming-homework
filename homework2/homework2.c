#include<stdio.h>
#include<windows.h>
#include<winsock.h>
#include<time.h>
#define PORT 3000
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")


DWORD WINAPI senddata(LPVOID lpParameter);
DWORD WINAPI recvdata(LPVOID lpParameter);
int wherey();
void gotoxy(int x, int y);

int main() {
	printf("客户端启动完成！(TCP)\n");
	SOCKET s, newsock;
	sockaddr_in local, object;
	WSAData wsa;
	char object_ip[20];
	int object_port = PORT;
	int flag = 0;
	int err_flag;
	WSAStartup(0x101, &wsa);

	s = socket(AF_INET, SOCK_STREAM, 0);
	local.sin_family = AF_INET;
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_port = htons(PORT);
	err_flag = bind(s, (sockaddr*)&local, sizeof(local));
	if (err_flag < 0) 
		printf("绑定错误！错误代码：%d\n", WSAGetLastError());

	printf("是否要发起聊天？[1/0]");
	scanf("%d", &flag);

	if (flag == 1) {
		printf("请输入目标IP地址:");
		scanf("%s", object_ip);
		object.sin_family = AF_INET;
		object.sin_addr.S_un.S_addr = inet_addr(object_ip);
		object.sin_port = htons(PORT);
		err_flag = connect(s, (sockaddr*)&object, sizeof(object));
		if (err_flag < 0) 
			printf("连接错误！错误代码：%d\n", WSAGetLastError());
		printf("连接建立成功！(输入'exit'退出)\n");
		HANDLE thread_send = CreateThread(NULL, 0, senddata, &s, 0, NULL);
		HANDLE thread_recv = CreateThread(NULL, 0, recvdata, &s, 0, NULL);
		WaitForSingleObject(thread_send, INFINITE);
		WaitForSingleObject(thread_recv, INFINITE);
		CloseHandle(thread_send);
		CloseHandle(thread_recv);
	}
	else {
		listen(s, 0);
		printf("进入监听模式!\n");
		int len = sizeof(object);
		newsock = accept(s, (sockaddr*)&object, &len);
		if (newsock < 0)
			printf("连接错误！错误代码：%d\n", WSAGetLastError());
		printf("连接建立成功！(输入'exit'退出)\n");
		HANDLE thread_send = CreateThread(NULL, 0, senddata, &newsock, 0, NULL);
		HANDLE thread_recv = CreateThread(NULL, 0, recvdata, &newsock, 0, NULL);
		WaitForSingleObject(thread_send, INFINITE);
		WaitForSingleObject(thread_recv, INFINITE);
		CloseHandle(thread_send);
		CloseHandle(thread_recv);
		closesocket(newsock);
	}
	closesocket(s);
	WSACleanup();
	printf("结束！");
	return 0;
}

DWORD WINAPI senddata(LPVOID lpParameter) {
	printf("发送数据线程启动！\n");
	SOCKET *s = (SOCKET*)lpParameter;
	char ex[] = "exit";
	int i, y, err_flag, x=1, flag = 0;
	time_t now;
	struct tm *tm_now;
	while (1) 
	{
		time(&now);
		tm_now = localtime(&now);

		char sendbuf[128] = { 0 };
		scanf("%s", sendbuf);
		y = wherey() - 1;
		send(*s, sendbuf, strlen(sendbuf), 0);
		gotoxy(x, y);
		printf("%d-%d-%d %d:%d:%d 发送数据：\n%s\n\n", tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday, tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec,sendbuf);
		for (i = 0; i < strlen(ex); i++) 
		{
			if (sendbuf[i] == ex[i])
			{
				if (i == strlen(ex) - 1)
					flag = 1;
			}
			else
				break;
		}
		if (flag == 1)
			break;
	}
	//closesocket(*s);
	return 0;
}

DWORD WINAPI recvdata(LPVOID lpParameter) {
	printf("接收数据线程启动！\n");
	SOCKET *s = (SOCKET*)lpParameter;
	char ex[] = "exit";
	int i, x = 1, flag = 0;
	time_t now;
	struct tm *tm_now;
	while (1) 
	{
		time(&now);
		tm_now = localtime(&now);

		char recvbuf[128] = { 0 };
		recv(*s, recvbuf, sizeof(recvbuf), 0);
		printf("%d-%d-%d %d:%d:%d 收到数据：\n%s\n\n", tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday, tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec, recvbuf);
		for (i = 0; i < strlen(ex); i++)
		{
			if (recvbuf[i] == ex[i])
			{
				if (i == strlen(ex) - 1)
					flag = 1;
			}
			else
				break;
		}
		if (flag == 1)
			break;
	}
	//closesocket(*s);
	return 0;
}

int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO pBuffer;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
	return (pBuffer.dwCursorPosition.Y + 1);
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}