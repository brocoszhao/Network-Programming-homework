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
	char buf[MAX_LEN] = "";
	dir = opendir("E:\\Workstation");   //这里改成需要显示文件目录的文件位置    
	if (dir) 
	{ 
		while ((file = readdir(dir)) != NULL)
		{
			//printf("%s\n", file->d_name); 
			if ((strcmp(file->d_name, ".") == 0) || (strcmp(file->d_name, "..") == 0))
				continue;
			strcat_s(buf, sizeof(buf), file->d_name);   //文件全部存到buf中
			strcat_s(buf, sizeof(buf), "  ");  //这里可以改变输出格式，文件是几个空格相隔还是换行符相隔
		}
	}                              
	printf("%s ", buf); 

	//return buf;       //返回的是一个包含了所有文件的字符串类型
	system("pause");
	return 0;
}