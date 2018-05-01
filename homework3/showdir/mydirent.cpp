#include <iostream>
#include "mydirent.h"
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;

int main()
{
	DIR *dir;
	struct dirent *ptr;

	std::vector<std::string> resVec;

	int num = 0, i = 0;
	//这里写成需要查看的文件目录
	if ((dir = opendir("E:\\Workstation")) == NULL) {
		std::cerr << "cannot open dir." << std::endl;
		return false;
	}

	while ((ptr = readdir(dir)) != NULL)
		resVec.push_back(std::string(ptr->d_name));     //char d_name[1];

	for (unsigned j = 0; j < resVec.size(); j++)
		std::cout << resVec.at(j) << std::endl;     //包含 ".." 上级目录

	//std::cout << resVec.size() << std::endl;

	closedir(dir);

	std::cout << "Press any key to continue.." << std::endl;
	getchar();

	return 0;
}