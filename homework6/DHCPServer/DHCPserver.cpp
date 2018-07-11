#include"stdafx.h"
#include"DHCPOptionEnum.h"
#include"parser.h"
#include"Mystruct.h"
#include"maker.h"
#include<conio.h>     //控制台的一些函数调用
#include<winsock2.h>
#include<thread>      
#include<unordered_map>
#include<iphlpapi.h>     //获取网络信息的函数
#include<WS2tcpip.h>     //与ipv6相关的头文件
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "IPHLPAPI.lib")


//在用map存储的ip结构中找是否存在相同的ip，若果没有就加入并分配，如果有则返回这个IP的相应信息
int GetIpFromTable(int session) {
	if (gSessionList.find(session) == gSessionList.end()) { 
		for (int i = 0; i < 256; i++) {
			if (gIPList.find(session) == gIPList.end()) { 
				gSessionList[session] = i;
				gIPList[i] = session;
				return i;
			}
		}
	}
	else {
		return gSessionList[session];
	}
	return -1;
}

//创建一个线程来模拟客户端进行操作
void ClientListen(ULONG bindInterfaceAddress)
{
	WSADATA wsaData;
	SOCKET m_socket;
	SOCKADDR_IN reciver;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
		printf("Socket init failed\n");
		return;
	}
	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_socket == INVALID_SOCKET) {
		printf("Connection failed. Error no : %ld\n", WSAGetLastError());
		WSACleanup();
		return;
	}
	bool opt = true;
	int senferAddSize = sizeof(reciver);
	reciver.sin_family = AF_INET;
	reciver.sin_port = htons(68);
	reciver.sin_addr.s_addr = bindInterfaceAddress;

	bind(m_socket, (SOCKADDR*)&reciver, sizeof(reciver));
	/*if ((bind(m_socket, (SOCKADDR*)&reciver, sizeof(reciver))) == -1) {
		printf("Socket bind error. (%d)\n", WSAGetLastError());
	}*/


	Packet_Information pakInfo;
	char strbuf[1645];  //548*3+1
	int len, getbytes;
	while (1)
	{
		DHCP_PACKET dhcp;
		memset(&dhcp, 0, 548);
		getbytes = recvfrom(m_socket, (char*)&dhcp, 548, 0, (struct sockaddr*) &reciver, &senferAddSize);
		if (getbytes >0) {
			printf("[%s:%d] Connected.\n", inet_ntoa(reciver.sin_addr), htons(reciver.sin_port));
			// prettyDebug( dhcp);
			printf("OP:%d\n", dhcp.OP);
			printf("ciaddr:%d.%d.%d.%d\n", dhcp.ciaddr[0], dhcp.ciaddr[1], dhcp.ciaddr[2], dhcp.ciaddr[3]);
			printf("yiaddr:%d.%d.%d.%d\n", dhcp.yiaddr[0], dhcp.yiaddr[1], dhcp.yiaddr[2], dhcp.yiaddr[3]);
			printf("siaddr:%d.%d.%d.%d\n", dhcp.siaddr[0], dhcp.siaddr[1], dhcp.siaddr[2], dhcp.siaddr[3]);
			printf("giaddr:%d.%d.%d.%d\n", dhcp.giaddr[0], dhcp.giaddr[1], dhcp.giaddr[2], dhcp.giaddr[3]);
			memset(&pakInfo, 0, sizeof(pakInfo));
			OptionParser(dhcp.Options, &pakInfo);
			if (gDebug) {
				byteToHexStr((byte*)&dhcp, strbuf, getbytes);
				printf("[Chunk Debug]\n%s/%d\n", strbuf, getbytes);
			}

			printf("\n");
		}
	}
}

int _tmain()   //有uniccode编码的main(),预编译后还是main()
{
	ULONG outBufLen = 0;   //unsigned long
	GetAdaptersInfo(NULL, &outBufLen);   //获得网络相关信息,第一次使用先获取大小(NULL肯定不够，所以返回空间大小)
	//创建PIP_ADAPTER_INFO结构体指针
	PIP_ADAPTER_INFO gPIpAdapterInfo = (PIP_ADAPTER_INFO)malloc(outBufLen);
	GetAdaptersInfo(gPIpAdapterInfo, &outBufLen);
	PIP_ADAPTER_INFO AdapterWalker = gPIpAdapterInfo;

	printf("DHCP Server BY YunLambert 2018-7-12");

	for (int i = 1; AdapterWalker; i++)
	{
		printf("(%d) %s %s\n", i, AdapterWalker->AdapterName, AdapterWalker->Description);
		printf(" *MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", AdapterWalker->Address[0], AdapterWalker->Address[1], AdapterWalker->Address[2],
			AdapterWalker->Address[3], AdapterWalker->Address[4], AdapterWalker->Address[5]);
		IP_ADDR_STRING *pIpAddrString = &(AdapterWalker->IpAddressList);

		do {
			printf("  IP: %s\n  Subnet Mask: %s\n  Gateway: %s\n",
				pIpAddrString->IpAddress.String, pIpAddrString->IpMask.String, AdapterWalker->GatewayList.IpAddress.String);
			pIpAddrString = pIpAddrString->Next;
		} while (pIpAddrString);
		AdapterWalker = AdapterWalker->Next;
	}

	ULONG bindInterfaceAddress = 0;
	do {
		printf("选择一个你想绑定的网络设备:");
		byte num = _getch() - '0';
		printf("选择一个你想绑定的网络设备:");
		AdapterWalker = gPIpAdapterInfo;   //上面只是为了输出设备信息，现在重新初始化
		for (int i = 1; AdapterWalker && (!bindInterfaceAddress); i++)
		{
			if (num == i)
			{
				bindInterfaceAddress=inet_addr(AdapterWalker->IpAddressList.IpAddress.String);
			}
			AdapterWalker = AdapterWalker->Next;
		}
	} while (!bindInterfaceAddress);

	memcpy(gMyIP, &bindInterfaceAddress, 4);
	memcpy(gRouter, &bindInterfaceAddress, 4);

	WSADATA wsaData;
	SOCKET m_socket;
	SOCKADDR_IN broadcast,reciver;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
		printf("Socket init failed.\n");
		return WSAGetLastError();
	}

	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_socket == INVALID_SOCKET) {
		printf("Connect error : %ld\n", WSAGetLastError());
		WSACleanup();
		return WSAGetLastError();
	}

	bool optval = true;
	//设置套接口的选项，如果要设置就要将第二个选项设为SOL_SOCKET，SO_BROADCAST，optval为1允许或为0禁止发送广播数据
	if (setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(bool)) == -1)
		printf("Can't broadcast.");

	broadcast.sin_family = AF_INET;
	broadcast.sin_port = htons(68);
	inet_pton(AF_INET, "255.255.255.255", &broadcast.sin_addr);

	int senferAddSize = sizeof(reciver);
	reciver.sin_family = AF_INET;
	reciver.sin_port = htons(67);
	reciver.sin_addr.s_addr = bindInterfaceAddress; // htonl(INADDR_ANY);
	bind(m_socket, (SOCKADDR*)&reciver, sizeof(reciver));

	printf("waiting\n");

	thread mThread(ClientListen, bindInterfaceAddress);


	//接收了从新线程模拟客户端发来的数据报文，进行pares
	Packet_Information pakInfo;
	byte ReplayOption[308];
	char strbuf[1645];
	int getbytes, id;
	char *tmp;
	while (1)
	{
		DHCP_PACKET dhcp;
		memset(&dhcp, 0, 548);
		getbytes = recvfrom(m_socket, (char*)&dhcp, 548, 0, (struct sockaddr*)&reciver, &senferAddSize);
		if (getbytes >= 0)
		{
			printf("[%s/%d] Connected.\n", inet_ntoa(reciver.sin_addr), htons(reciver.sin_port));
			byte* optionarray = dhcp.Options;
			memset(ReplayOption, 0, 308);
			bool end = false;
			int ReplayOptionWalker = 0;
			memset(&pakInfo, 0, sizeof(pakInfo));
			printf("OP:%d\n", dhcp.OP);
			printf("ciaddr:%d.%d.%d.%d\n", dhcp.ciaddr[0], dhcp.ciaddr[1], dhcp.ciaddr[2], dhcp.ciaddr[3]);
			printf("yiaddr:%d.%d.%d.%d\n", dhcp.yiaddr[0], dhcp.yiaddr[1], dhcp.yiaddr[2], dhcp.yiaddr[3]);
			printf("siaddr:%d.%d.%d.%d\n", dhcp.siaddr[0], dhcp.siaddr[1], dhcp.siaddr[2], dhcp.siaddr[3]);
			printf("giaddr:%d.%d.%d.%d\n", dhcp.giaddr[0], dhcp.giaddr[1], dhcp.giaddr[2], dhcp.giaddr[3]);

			OptionParser(dhcp.Options, &pakInfo);
			for (int i = 0; pakInfo.ParameterRequestList[i]; i++) {
				pakInfo.OptionToReplay[pakInfo.ParameterRequestList[i]] = true;
			}


			//parse完成后，主线程开始制作PDU并发送报文，其中包含了IP地址等相关信息或者控制命令
			// 默认的Server Option
			pakInfo.OptionToReplay[DHCPMESSAGETYPE] = true;
			pakInfo.OptionToReplay[SERVERIDENTIFIER] = true;
			pakInfo.OptionToReplay[IPADDRESSLEASETIME] = true;
			pakInfo.OptionToReplay[DOMAINNAME] = true;
			pakInfo.OptionToReplay[SUBNETMASK] = true;
			pakInfo.OptionToReplay[ROUTER] = true;
			pakInfo.OptionToReplay[DOMAINNAMESERVER] = true;

			ReplayOptionWalker += OptionMaker(ReplayOption + ReplayOptionWalker, &pakInfo);
			ReplayOption[ReplayOptionWalker++] = 0xFF;

			//制作PDU
			dhcp.OP = 2;
			memset(dhcp.ciaddr, 0, 4); // 设为0
			memcpy(dhcp.yiaddr, gMyIP, 3);
			dhcp.yiaddr[3] = GetIpFromTable(dhcp.TRANSACTION_ID);
			dhcp.FLAGS = 0;
			dhcp.SECONDS = 0;
			memcpy(dhcp.Options, ReplayOption, ReplayOptionWalker);

			if (sendto(m_socket, (char*)&dhcp, 548, 0, (SOCKADDR*)&broadcast, sizeof(SOCKADDR)) <0) {
				printf(" *Error to Send:%d\n", GetLastError());
			}

			if (gDebug) {
				byteToHexStr((byte*)&dhcp, strbuf, getbytes);
				printf("[Debug]\n%s/%d\n", strbuf, getbytes);
			}
			printf("\n");
		}
	}
	free(gPIpAdapterInfo);
	system("pause");
	WSACleanup();
	return 0;
}