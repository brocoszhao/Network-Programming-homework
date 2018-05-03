#include "winsock.h"
#include <stdio.h>
#include <string.h>
#pragma comment (lib,"wsock32.lib")
#define PORT 3000
int string_match(char a[], char b[]) {
	int a_length = strlen(a);
	int b_length = strlen(b);
	if (a_length < b_length) {
		//不匹配
		return 0;
	}
	for (int i = 0; i < b_length; i++) {
		if (a[i] != b[i]) {
			return 0;
		}
	}
	return 1;
}

int main() {
	SOCKET s;
	sockaddr_in local_addr, remote_addr;
	char recvbuf[128] = { 0 };
	char sendbuf[128] = { 0 };
	char typebuf[128] = { 0 };
	char remote_ip[12] = { 0 };
	char uploadpath[128] = { 0 };
	char downloadpath[128] = { 0 };
	char name[128] = { 0 };
	int recvlen, i, j, linxt, id = 0;
	FILE *fid;
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
	printf("Please input the ip address of server:");
	scanf("%s",remote_ip);

	remote_addr.sin_family = AF_INET;
	remote_addr.sin_addr.S_un.S_addr = inet_addr(remote_ip);
	remote_addr.sin_port = htons(PORT);

	connect(s, (sockaddr*)&remote_addr, sizeof(remote_addr));
	//质询
	recvlen = recv(s, recvbuf, 128, 0);
	if (recvlen == -1) {
		printf("Error! error code:%d", WSAGetLastError());
		return 0;
	}
	recvbuf[recvlen] = 0;
	unsigned int qlst[20] = { 0 };
	for (i = 0; i < 20; i++) {
		for (j = i * 4; j < i * 4 + 4; j++) {
			qlst[i] += unsigned int((recvbuf[j]) << (4 * i + 3 - j) * 8);
		}
		printf("%d\t", qlst[i]);
	}
	unsigned int sum = 0;
	for (i = 0; i < 20; i++) {
		sum += qlst[i];
	}
	unsigned int qrslt = sum ^ 12345;
	unsigned char qrslt_char[4];
	for (i = 0; i < 4; i++) {
		qrslt_char[i] = unsigned char(qrslt >> (3 - i) * 8);
	}
	send(s, (char*)qrslt_char, 4, 0);
	recvlen = recv(s, recvbuf, 128, 0);
	if (recvlen == -1) {
		printf("Error code:%d", WSAGetLastError());
		return 0;
	}
	recvbuf[recvlen] = 0;
	if (/*!strcmp(recvbuf,"q1")*/1){
		printf("Connection completed\n");
		while (1) {
			printf(">");
			scanf("%s", sendbuf);
			send(s, sendbuf, strlen(sendbuf), 0);
			if (string_match(sendbuf, "ls")) {
				//查看目录
				recvlen = recv(s, recvbuf, sizeof(recvbuf), 0);
				recvbuf[recvlen] = '\0';
				printf("%s\n", recvbuf);
			}
			else if (string_match(sendbuf, "upload")) {
				//用户要上传
				printf("%s", uploadpath);
				strcpy(uploadpath, &sendbuf[7]);
				fid = fopen(uploadpath, "a+b");
				while (!feof(fid)) {
					fgets(sendbuf, sizeof(sendbuf), fid);
					send(s, sendbuf, strlen(sendbuf), 0);
				}
				fclose(fid);
				send(s, "end", 3, 0);
			}
			else if (string_match(sendbuf, "download")) {
				//用户要下载
				for (i = 0; i < strlen(sendbuf); i++) {
					if (sendbuf[i] == 92)
						id = i;
				}
				//printf("%d", id);
				if (id == 0) {
					//未写下载存储路径
					strcpy(downloadpath, "C:\\Users\\忠涛\\Desktop\\");
					strcpy(name, &sendbuf[9]);//获得下载的文件名
				}
				else {
					//写了下载存储路径
					strcpy(downloadpath, &sendbuf[9]);
					downloadpath[id - 8] = '\0';
					strcpy(name, &sendbuf[id + 1]);//获得下载的文件名
				}
				strcat(downloadpath, name);//获得下载文件URL
				printf("%s", downloadpath);

				fid = fopen(downloadpath, "a+b");
				recvlen = recv(s, recvbuf, sizeof(recvbuf), 0);
				recvbuf[recvlen] = '\0';
				fprintf(fid, "%s", recvbuf);//写入新文件
				printf("11111111\t%s", recvbuf);
				while (!string_match(recvbuf, "end")) {
					printf("1232132323");
					recvlen = recv(s, recvbuf, sizeof(recvbuf), 0);
					recvbuf[recvlen] = '\0';
					fprintf(fid, "%s", recvbuf);
				}
				fclose(fid);//关闭文件
			}
		}
	}
	else {
		printf("Connection failed\n");
	}
	return 0;
}