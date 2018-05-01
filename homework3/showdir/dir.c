//#include <dirent.h>
#include "dirent2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 65535


int main(void)
{
	DIR *dir;    
	struct dirent *file;    
	int found = 0;       
	dir = opendir("E:\\Workstation\\Python");   //这里改成需要显示文件目录的文件位置    
	if (dir) 
	{ 
		while ((file = readdir(dir)) != NULL) 
		    printf("%s\n", file->d_name); 
	} 
	system("pause");
	return 0;
}