#include <dirent.h>
#include "dirent2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 65535



int main(void)
{
	DIR *dir;
	struct dirent *ptr;
	char *flow[MAX_LEN];
	int num = 0, i = 0;

	if ((dir = opendir("e:\\")) == NULL)
	{
		perror("Open dir error...");
		system("pause");
		exit(1);
	}
	// readdir() return next enter point of directory dir
	while ((ptr = readdir(dir)) != NULL)
	{
		flow[num] = (char*)malloc(sizeof(char));
		int len = strlen(ptr->d_name);
		strcpy_s(flow[num],len, ptr->d_name);
		num++;
	}

	for (i = 0; i < num; i++)
	{
		printf("%s\n", flow[i]);
	}

	closedir(dir);
}