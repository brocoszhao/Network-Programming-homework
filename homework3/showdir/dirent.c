#include <stdio.h>     
#include <windows.h>  
#include <stdlib.h>
#include <string.h>
#include "dirent.h"
  
static HANDLE hFind;  
#define MAX_LEN 65535
  
DIR *opendir(const char *name)  
{  
    DIR *dir;  
    WIN32_FIND_DATA FindData;  
    char namebuf[512];  
  
	printf("there is a bug£¡£¡£¡£¡");
    printf(namebuf, "%s\\*.*",name);  
  
    hFind = FindFirstFile(namebuf, &FindData );   
    if(hFind == INVALID_HANDLE_VALUE)   
    {  
        printf("FindFirstFile failed (%d)\n", GetLastError());  
        return 0;  
    }   
  
    dir = (DIR *)malloc(sizeof(DIR));  
    if(!dir)  
    {  
        printf("DIR memory allocate fail\n");  
        return 0;  
    } 

    memset(dir, 0, sizeof(DIR));  
    dir->dd_fd = 0;   // simulate return  
  
    return dir;  
}  

struct dirent *readdir(DIR *d)  
{  
    int i; 
    static struct dirent dirent;  
    BOOL bf;  
    WIN32_FIND_DATA FileData;  
    if(!d)  
    {  
        return 0;  
    }  
  
    bf = FindNextFile(hFind,&FileData);  
    //fail or end  
    if(!bf)  
    {  
        return 0;  
    }

    for(i = 0; i < 256; i++)  
    {  
        dirent.d_name[i] = FileData.cFileName[i];  
        if(FileData.cFileName[i] == '\0') break;  
    }  
    dirent.d_reclen = i;  
    dirent.d_reclen = FileData.nFileSizeLow;  
  
    //check there is file or directory  
    if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  
    {  
        dirent.d_type = 2;  
    }  
    else  
    {  
        dirent.d_type = 1;  
    }  
      
  
    return (&dirent);  
}  
  
int closedir(DIR *d)  
{  
    if(!d) return -1;  
    hFind=0;  
    free(d);  
    return 0;  
} 


//int main()
//{
//	DIR *dir;
//	struct dirent *ptr;
//	char *flow[MAX_LEN];
//	int num = 0, i = 0;
//
//	if ((dir = opendir("./data")) == NULL)
//	{
//		printf("³öÏÖÁË´íÎó£¡");
//		perror("cannot open the dir");
//		system("pause");
//		exit(1);
//	}
//
//	while ((ptr = readdir(dir)) != NULL)
//	{
//		flow[num] = (char*)malloc(sizeof(char));
//		strcpy(flow[num], ptr->d_name);
//		num++;
//	}
//
//	for (int i = 0; i < num; i++)
//	{
//		printf("%s\n", flow[i]);
//	}
//
//	closedir(dir);
//
//	system("pause");
//}

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent* mydirent;
	if (argc != 2)
	{
		printf("usage:directory_name");
		system("pause");
		return -1;
	}
	if ((dir = opendir(argv[1])) != NULL)
	{
		while ((mydirent = readdir(dir)) != NULL)
		{
			printf("%s \n", mydirent->d_name);
			system("pause");
		}
	}
	else {
		printf("cannot open %s", argv[1]);
		system("pause");
		return -1;
	}
	closedir(dir);
	system("pause");
	return 0;
}
