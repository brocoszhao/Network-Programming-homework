//// server.cpp : 
////
//#define _CRT_SECURE_NO_WARNINGS
//#include "winsock.h"
//#include "stdio.h"
//#pragma comment (lib,"wsock32.lib")
//#define MAX_SOCKETS	1024
//struct socket_list{
//	SOCKET MainSock;
//	int num;
//	SOCKET sock_array[MAX_SOCKETS];
//};
//void init_list(socket_list *list)
//{
//	int i;
//	list->MainSock = 0;
//	list->num = 0;
//	for(i = 0;i < MAX_SOCKETS;i ++){
//		list->sock_array[i] = 0;
//	}
//}
//void insert_list(SOCKET s,socket_list *list)
//{
//	int i;
//	for(i = 0;i < MAX_SOCKETS; i++){
//		if(list->sock_array[i] == 0){
//			list->sock_array[i] = s;
//			list->num += 1;
//			break;
//		}
//	}
//}
//void delete_list(SOCKET s,socket_list *list)
//{
//	int i;
//	for(i = 0;i < MAX_SOCKETS; i++){
//		if(list->sock_array[i] == s){
//			list->sock_array[i] = 0;
//			list->num -= 1;
//			break;
//		}
//	}
//}
//void make_fdlist(socket_list *list,fd_set *fd_list)
//{
//	int i;
//	FD_ZERO(fd_list);
//	FD_SET(list->MainSock,fd_list);
//	for(i = 0;i < MAX_SOCKETS;i++){
//		if(list->sock_array[i] > 0){
//			FD_SET(list->sock_array[i],fd_list);
//		}
//	}
//}
//int main(int argc, char* argv[])
//{
//	SOCKET s,sock;
//	struct sockaddr_in ser_addr,remote_addr;
//	int len,total_len,total_sendlen;
//	char *buf;
//	WSAData wsa;
//	int retval;
//	struct socket_list sock_list;
//	fd_set readfds,writefds,exceptfds;
//	int i;
//	unsigned long arg;
//	long pending_count = 0;
//	int BufLen;
//	int BufFlag;
//
//	WSAStartup(0x101,&wsa);
//
//	printf("请输入单片接收缓存大小(0表示自适应大小)：");
//	scanf("%d",&BufLen);
//	if(BufLen > 0){
//		buf = (char *)malloc(BufLen);
//		if(buf == NULL){
//			printf("内存不够\n");
//			return 0;
//		}
//		BufFlag = 1;
//	}else{
//		BufFlag = 0;
//		buf = NULL;
//	}
//
//	s = socket(AF_INET,SOCK_STREAM,0);
//	ser_addr.sin_family = AF_INET;
//	ser_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	ser_addr.sin_port = htons(12345);
//	bind(s,(sockaddr*)&ser_addr,sizeof(ser_addr));
//
//	listen(s,5);
//
//	init_list(&sock_list);
//	sock_list.MainSock = s;
//
//	total_len = 0;
//	total_sendlen = 0;
//
//	arg = 1;
//	ioctlsocket(sock_list.MainSock,FIONBIO,&arg);
//
//	while(1){
//		FD_ZERO(&readfds);
//		FD_ZERO(&writefds);
//		FD_ZERO(&exceptfds);
//		make_fdlist(&sock_list,&readfds);
//		//make_fdlist(&sock_list,&writefds);
//		//make_fdlist(&sock_list,&exceptfds);
//		retval = select(0,&readfds,&writefds,&exceptfds,NULL);
//		if(retval == SOCKET_ERROR){
//			retval = WSAGetLastError();
//			printf("select error %d\n",retval);
//			break;
//		}
//		if(FD_ISSET(sock_list.MainSock,&readfds)){
//			len = sizeof(remote_addr);
//			sock = accept(sock_list.MainSock,(sockaddr*)&remote_addr,&len);
//			if(sock == SOCKET_ERROR)
//				continue;
//			printf("accept a connection\n");
//			insert_list(sock,&sock_list);
//		}
//		for(i = 0;i < MAX_SOCKETS;i++){
//			if(sock_list.sock_array[i] == 0)
//				continue;
//			sock = sock_list.sock_array[i];
//			if(FD_ISSET(sock,&readfds)){
//				if(BufFlag == 0){
//					//自适应大小，根据待接收大小决定缓冲大小
//					ioctlsocket(sock,FIONREAD,(unsigned long *)&len);
//					if(len > 0){
//						if(buf != NULL){
//							free(buf);
//							buf = NULL;
//						}
//						buf = (char*)malloc(len);
//						if(buf == NULL){
//							printf("没有足够内存\n");
//							continue;
//						}
//						len = recv(sock,buf,len,0);
//					}
//				}else{
//					//使用固定大小缓存
//					len = recv(sock,buf,BufLen,0);
//				}
//				if(len == 0){
//					//必须将套接字从接收队列中取下来！否则不关闭就会不断有read事件。
//					
//					closesocket(sock);
//					printf("close a socket\n");
//					delete_list(sock,&sock_list);
//
//					printf("recv0发生过 %d 次无法及时发出的现象\n",pending_count);
//					
//					continue;
//				}else if(len == -1){
//					retval = WSAGetLastError();
//					if(retval == WSAEWOULDBLOCK){
//						continue;
//					}
//					closesocket(sock);
//					printf("close a socket\n");
//					delete_list(sock,&sock_list);
//
//					printf("recv-1发生过 %d 次无法及时发出的现象\n",pending_count);
//					continue;
//				}
//				//buf[len] = 0;
//				total_len += len;
//				printf("-->%d 字节\n",total_len);
//				retval = send(sock,buf,len,0);
//				if(retval == 0){
//					closesocket(sock);
//					printf("close a socket\n");
//					delete_list(sock,&sock_list);
//					printf("send0发生过 %d 次无法及时发出的现象\n",pending_count);
//					continue;
//				}else if(retval == -1){
//					retval = WSAGetLastError();
//					if(retval == WSAEWOULDBLOCK){
//						pending_count ++;
//						printf("send pending\n");
//						continue;
//					}
//					closesocket(sock);
//					printf("close a socket\n");
//					delete_list(sock,&sock_list);
//					printf("send-1发生过 %d 次无法及时发出的现象\n",pending_count);
//					continue;
//				}
//				total_sendlen += retval;
//				printf("<--%d 字节\n",total_sendlen);
//
//				if(buf != NULL && BufFlag == 0){
//					free(buf);
//					buf = NULL;
//				}
//			}
//			//if(FD_ISSET(sock,&writefds)){
//			//}
//			/*
//			if(FD_ISSET(sock,&exceptfds)){
//				closesocket(sock);
//				printf("close a socket\n");
//				delete_list(sock,&sock_list);
//				continue;
//			}
//			*/
//			
//		}
//	}
//	if(buf != NULL)
//		free(buf);
//	closesocket(sock_list.MainSock);
//	WSACleanup();
//	return 0;
//}
//

//#include<queue>
//#include<string>
//#include<iostream>
//using namespace std;
//queue<char> str;
//int main()
//{
//	//char *s = "1234";
//	//addqueue("1234");
//	//addqueue("123456");
//	//link point;
//	//point = front;
//	//while (point != NULL)
//	//{
//	//	for (int i = 0; i < 10; i++)
//	//	{
//	//		while ((point->a)[i] != '\0')
//	//		{
//	//			printf("%2d", (point->a)[i]);
//	//		}
//	//	}	
//	//	point = point->next;
//	//}
//	str.push('ab');
//	cout << str.front() << endl;
//	str.pop();
//	
//
//	system("pause");
//}

#include <iostream>
#include <list>
#include <string>
#include <cctype>
using namespace std;

//int main()
//{
//	list<string> mylist;
//	list<string>::iterator it;
//	mylist.push_back("one");
//	mylist.push_back("two");
//	mylist.push_back("Three");
//	
//	cout << "mylist contains:";
//	for (it = mylist.begin(); it != mylist.end(); ++it)
//		cout << " " << *it;
//	cout << endl;
//
//	mylist.pop_back();
//	for (it = mylist.begin(); it != mylist.end(); ++it)
//		cout << " " << *it;
//	cout << endl;
//
//	system("pause");
//	return 0;
//}

int main()
{
	char p[10];
	*(p + 10) = 'a';
	cout << *(p + 10) << endl;
	system("pause");
}
