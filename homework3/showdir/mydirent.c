#include <stdio.h>     
#include <windows.h>  
#include <stdlib.h>
#include <string.h>
#include "mydirent.h"
  
static HANDLE hFind;  
#define MAX_LEN 65535

int main()
{
	// use as readdir() in Linux
	DIR *dir;
	struct dirent *ptr;

	char *flow[65536];
	int num = 0, i = 0;

	if ((dir = opendir("E:\\Workstation")) == NULL) {
		perror("cannot open the dir");
		system("pause");
		return 0;
	}

	while ((ptr = readdir(dir)) != NULL) {
		flow[num] = (char *)malloc(sizeof(char));
		int len = strlen(ptr->d_name);
		strcpy_s(flow[num], len,ptr->d_name);             //char d_name[1];
		num++;
	}

	// output test
	for (i = 0; i < num; ++i) {
		//if (strcmp(flow[i], "..") == 0 || strcmp(flow[i], ".") == 0)
		//	std::cout << "find last directory." << std::endl;
		//else
		//	std::cout << std::string(flow[i]) << std::endl;
		printf("%s\n", flow[i]);
	}
	
	closedir(dir);
	system("pause");
	return 0;
}


