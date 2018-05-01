#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

typedef struct _dirdesc {
    int     dd_fd;      /** file descriptor associated with directory */
    long    dd_loc;     /** offset in current buffer */
    long    dd_size;    /** amount of data returned by getdirentries */
    char    *dd_buf;    /** data buffer */
    int     dd_len;     /** size of data buffer */
    long    dd_seek;    /** magic cookie returned by getdirentries */
} DIR;

# define __dirfd(dp)    ((dp)->dd_fd)

DIR *opendir (const char *);
struct dirent *readdir (DIR *);
void rewinddir (DIR *);
int closedir (DIR *);

#include <sys/types.h>

struct dirent
{
     long d_ino;              /* inode number*/
     off_t d_off;             /* offset to this dirent*/
     unsigned short d_reclen; /* length of this d_name*/
     unsigned char d_type;    /* the type of d_name*/
     char d_name[1];          /* file name (null-terminated)*/
};

#include <windows.h>
#include <stdio.h>

static HANDLE hFind;

DIR *opendir(const char *name)
{
	DIR *dir;
	WIN32_FIND_DATA FindData;
	char namebuf[512];

	sprintf_s(namebuf, "%s\\*.*", name);

	hFind = FindFirstFile(namebuf, &FindData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("FindFirstFile failed (%d)\n", GetLastError());
		return 0;
	}

	dir = (DIR *)malloc(sizeof(DIR));
	if (!dir)
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
	if (!d)
	{
		return 0;
	}

	bf = FindNextFile(hFind, &FileData);
	//fail or end  
	if (!bf)
	{
		return 0;
	}

	for (i = 0; i < 256; i++)
	{
		dirent.d_name[i] = FileData.cFileName[i];
		if (FileData.cFileName[i] == '\0') break;
	}
	dirent.d_reclen = i;
	dirent.d_reclen = FileData.nFileSizeLow;

	//check there is file or directory  
	if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
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
	if (!d) return -1;
	hFind = 0;
	free(d);
	return 0;
}

#endif