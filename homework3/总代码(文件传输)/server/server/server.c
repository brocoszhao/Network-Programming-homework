#include "winsock.h"
#include "stdio.h"
#include <math.h>
#include <time.h>
#include <string.h>
#include "dirent2.h"
#include <stdlib.h>
#pragma comment (lib,"wsock32.lib")
#define PORT 3000


struct socket_list {
	SOCKET MainSock;
	int num;
	SOCKET sock_array[64];
};

char *get_dir()
{
	DIR *dir;
	struct dirent *file;
	int found = 0;
	char buf[128] = "";
	dir = opendir("D:\\root");   //����ĳ���Ҫ��ʾ�ļ�Ŀ¼���ļ�λ��    
	if (dir)
	{
		while ((file = readdir(dir)) != NULL)
		{
			//printf("%s\n", file->d_name); 
			strcat_s(buf, sizeof(buf), file->d_name);   //�ļ�ȫ���浽buf��
			strcat_s(buf, sizeof(buf), "\t");  //������Ըı������ʽ���ļ��Ǽ����ո�������ǻ��з����
		}
	}
	return buf;
}

int string_match(char a[], char b[]) {
	int a_length = strlen(a);
	int b_length = strlen(b);
	if (a_length < b_length) {
		//��ƥ��
		return 0;
	}
	for (int i = 0; i < b_length; i++) {
		if (a[i] != b[i]) {
			return 0;
		}
	}
	return 1;
}

struct qdata {
	int qrslt;
	char qlst_char[80] = { 0 };
};

struct qdata get_qdata() {
	srand(time(NULL));
	int N = rand() % 11 + 10;//���鳤��
	unsigned int qlst[20] = { 0 };
	unsigned char qlst_char[80] = { 0 };
	for (int i = 0; i < N; i++) {
		qlst[i] = rand();
		printf("%d\t", qlst[i]);
		for (int j = i * 4; j < i * 4 + 4; j++) {
			qlst_char[j] = char ((qlst[i]) >> (4 * i + 3 - j) * 8);
		}
	}
	unsigned int sum = 0;
	for (int i = 0; i < N; i++) {
		sum += qlst[i];
	}
	int qrslt = sum ^ 12345;
	struct qdata qrydata;
	qrydata.qrslt = qrslt;
	for (int i = 0; i < 80; i++) {
		qrydata.qlst_char[i] = qlst_char[i];
	}
	return qrydata;
}



void init_list(socket_list *list)
{
	int i;
	list->MainSock = 0;
	list->num = 0;
	for (i = 0; i < 64; i++) {
		list->sock_array[i] = 0;
	}
}
void insert_list(SOCKET s, socket_list *list)
{
	int i;
	for (i = 0; i < 64; i++) {
		if (list->sock_array[i] == 0) {
			list->sock_array[i] = s;
			list->num += 1;
			break;
		}
	}
}
void delete_list(SOCKET s, socket_list *list)
{
	int i;
	for (i = 0; i < 64; i++) {
		if (list->sock_array[i] == s) {
			list->sock_array[i] = 0;
			list->num -= 1;
			break;
		}
	}
}
void make_fdlist(socket_list *list, fd_set *fd_list)
{
	int i;
	FD_SET(list->MainSock, fd_list);
	for (i = 0; i < 64; i++) {
		if (list->sock_array[i] > 0) {
			FD_SET(list->sock_array[i], fd_list);
		}
	}
}
int main() {
	SOCKET s, newsock, sock;
	sockaddr_in local_addr, remote_addr;
	char recvbuf[128] = { 0 };
	char sendbuf[128] = { 0 };
	char path[128] = { 0 };
	char name[128] = { 0 };
	strcpy(path,"D:\\root\\");
	struct socket_list sock_list;
	init_list(&sock_list);
	fd_set readfds, writefds, exceptfds;
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_ZERO(&exceptfds);
	int flag, len, N, i, j, qrslt_client, recvlen, linxt, id = 0;
	FILE *fid;
	char linxt_char;
	struct qdata qrydata;
	WSAData wsa;
	WSAStartup(0x101, &wsa);
	
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == SOCKET_ERROR)
		return 0;
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local_addr.sin_port = htons(PORT);
	bind(s, (sockaddr*)&local_addr, sizeof(local_addr));

	printf("Initialization completed\n");
	printf("Enter the listen mode\n");

	listen(s, 5);
	sock_list.MainSock = s;
	while (1) {
		make_fdlist(&sock_list, &readfds);
		flag = select(0, &readfds, &writefds, &exceptfds, NULL);
		if (flag == SOCKET_ERROR) {
			printf("Error! error code:%d", WSAGetLastError());
			break;
		}
		if (FD_ISSET(sock_list.MainSock, &readfds)) {
			len = sizeof(remote_addr);
			newsock = accept(sock_list.MainSock, (sockaddr*)&remote_addr, &len);
			if (newsock == SOCKET_ERROR)
				continue;
			//��ѯ��
			qrydata = get_qdata();//������ѯ����
			send(newsock, (char*)qrydata.qlst_char, sizeof(qrydata.qlst_char), 0);
			recv(newsock, recvbuf, 128, 0);
			qrslt_client = 0;
			for (i = 0; i < 4; i++) {
				qrslt_client += (unsigned int)recvbuf[i] << (3 - i) * 8;
			}
			if (qrslt_client != qrydata.qrslt) {
				printf("accept a connection\n");
				send(newsock, "q1", 6, 0);
				insert_list(newsock, &sock_list);
			}
			else {
				printf("connection is rejected\n");
				send(newsock, "q2", 6, 0);
			}
		}
		for (i = 0; i < 64; i++) {
			if (sock_list.sock_array[i] == 0)
				continue;
			sock = sock_list.sock_array[i];
			if (FD_ISSET(sock, &readfds)) {
				recvlen = recv(sock, recvbuf, 128, 0);
				if (recvlen == 0) {
					closesocket(sock);
					printf("close a socket\n");
					delete_list(sock, &sock_list);
					continue;
				}
				else if (recvlen == -1) {
					recvlen = WSAGetLastError();
					if (recvlen == WSAEWOULDBLOCK)
						continue;
					closesocket(sock);
					printf("close a socket\n");
					delete_list(sock, &sock_list);
					continue;
				}
				recvbuf[recvlen] = '\0';
				if (string_match(recvbuf, "ls")) {
					//�û�Ҫ�鿴Ŀ¼
					strcpy(sendbuf, get_dir());
					send(sock, sendbuf, strlen(sendbuf), 0);
				}
				else if (string_match(recvbuf, "upload")) {
					//�û�Ҫ�ϴ�
					for (i = 0; i < strlen(recvbuf); i++) {
						if (recvbuf[i] == 92)
							id = i;
					}
					strcpy(name, &recvbuf[id + 1]);//����ϴ��ļ���
					strcat(path, name);//����ϴ��ļ�·��
					
					fid = fopen(path, "a+b");//�������ļ�
					recvlen = recv(sock, recvbuf, sizeof(recvbuf), 0);
					recvbuf[recvlen] = '\0';
					fprintf(fid, "%s", recvbuf);//д�����ļ�
					while (!string_match(recvbuf, "end")) {
						recvlen = recv(sock, recvbuf, sizeof(recvbuf), 0);
						recvbuf[recvlen] = '\0';
						fprintf(fid, "%s", recvbuf);
					}
					fclose(fid);//�ر��ļ�		
					printf(strcat(name, " has been uploaded by user!"));
				}
				else if (string_match(recvbuf, "download")) {
					//�û�Ҫ����
					strcpy(path, "D:\\root\\");
					for (i = 0; i < strlen(recvbuf); i++) {
						if (recvbuf[i] == 92)
							id = i;
					}
					if(id == 0)
						strcpy(name, &recvbuf[9]);//��������ļ���
					else
						strcpy(name, &recvbuf[id + 1]);//��������ļ���
					strcat(path, name);//��������ļ�·��
					fid = fopen(path, "a+b");
					while (!feof(fid)) {
						fgets(sendbuf, sizeof(sendbuf), fid);
						printf("%s", sendbuf);
						send(sock, sendbuf, strlen(sendbuf), 0);
					}
					fclose(fid);
					send(sock, "end", 3, 0);
				}
			}
		}
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_ZERO(&exceptfds);
	}
}






