// client.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include <windows.h>
#include <winsock.h>
#include <stdio.h>
//#include <stdlib.h>
#define SERVER_PORT 0x1234
#pragma comment (lib, "wsock32.lib")
#define MAX_BUFFER 1000000

void my_printf(const char * p)
{
	printf("%s\n",p);
}
void my_scanf(char * buf,int buf_size)
{
	scanf("%s",buf);
}

int main(int argc, char* argv[])
{
	SOCKET s;
	struct sockaddr_in ser_addr;
	int len;
	char scanbuf[80];
	WSAData wsa;
	char * sendbuf;
	int total;
	int templen;
	int totalsend;
	int retval;
	int buf_flag;
	int recv_size;
	bool bStop;

	WSAStartup(0x101,&wsa);


	s = socket(AF_INET,SOCK_STREAM,0);
	ser_addr.sin_family = AF_INET;

	my_printf("������IP��ַ");
	my_scanf(scanbuf,sizeof(scanbuf));
	my_printf(scanbuf);
	ser_addr.sin_addr.S_un.S_addr = inet_addr(scanbuf);

	my_printf("������˿ں�");
	my_scanf(scanbuf,sizeof(scanbuf));
	my_printf(scanbuf);
	ser_addr.sin_port = htons(atoi(scanbuf));
	my_printf(scanbuf);

	len = sizeof(ser_addr);
	if(connect(s,(sockaddr *)&ser_addr,len) != 0){
		my_printf("can`t connet to server!");
		return 0;
	}
	my_printf("connect to server !");
	bStop = false;

	while(!bStop){
		my_printf("�����뷢�͵��ֽ���");
		my_scanf(scanbuf,sizeof(scanbuf));
		if(!strcmp("exit",scanbuf)){
			//����exit�󣬾ͽ���ͨ��
			break;
		}
		len = atoi(scanbuf);
		my_printf(scanbuf);
		total = 0;
		totalsend = len;
		if(len > MAX_BUFFER){
			len = MAX_BUFFER;
		}

		while(total < totalsend){
			if(totalsend - total > MAX_BUFFER){
				len = MAX_BUFFER;
			}else{
				len = totalsend - total;
			}
			sendbuf = (char *)malloc(len);
			if(sendbuf == NULL){
				my_printf("û���㹻����");
				closesocket(s);
				return 0;
			}
			//sectotal = 0;
			templen = 0;
			while(templen < len){
				retval = send(s,sendbuf+templen,len-templen,0);
				while(retval < 0){
					retval = send(s,sendbuf+templen,len-templen,0);
				}
				if(retval == 0){
					my_printf("���ͳ���");
					closesocket(s);
					return 0;
				}
				templen += retval;
			}
			free(sendbuf);
			
			total += templen;
		}
		sprintf(scanbuf,"�ɹ����� %d �ֽ�",total);
		my_printf(scanbuf);

		total = 0;
		sendbuf = (char* )malloc(MAX_BUFFER);
		if(sendbuf == NULL){
			my_printf("�ڴ治��");
			//���þֲ��ռ����������ݣ�������
			sendbuf = scanbuf;
			buf_flag = 1;
			recv_size = sizeof(scanbuf);
		}else{
			buf_flag = 0;
			recv_size = MAX_BUFFER;
		}
		templen = recv(s,sendbuf,recv_size,0);
		if(templen <= 0){
			my_printf("��������ֹ����");
			bStop = 1;
			if(buf_flag == 0)
				free(sendbuf);
			break;
		}
		total += templen;
		while(total < totalsend ){
			templen = recv(s,sendbuf,recv_size,0);
			if(templen <= 0){
				my_printf("��������ֹ����");
				if(buf_flag == 0)
					free(sendbuf);
				bStop = 1;
				break;
			}
			total += templen;
			
		}
		sprintf(scanbuf,"�ɹ����� %d �ֽ�",total);
		my_printf(scanbuf);
		if(buf_flag == 0)
			free(sendbuf);
	}
	closesocket(s);
	return 0;
}
