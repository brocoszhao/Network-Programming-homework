#include"stdafx.h"
#include"DHCPOptionEnum.h"
#include"parser.h"
#include"Mystruct.h"
#include"maker.h"
#include<conio.h>     //����̨��һЩ��������
#include<winsock2.h>
#include<thread>      
#include<unordered_map>
#include<iphlpapi.h>     //��ȡ������Ϣ�ĺ���
#include<WS2tcpip.h>     //��ipv6��ص�ͷ�ļ�
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "IPHLPAPI.lib")


//����map�洢��ip�ṹ�����Ƿ������ͬ��ip������û�оͼ��벢���䣬������򷵻����IP����Ӧ��Ϣ
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

//����һ���߳���ģ��ͻ��˽��в���
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

int _tmain()   //��uniccode�����main(),Ԥ�������main()
{
	ULONG outBufLen = 0;   //unsigned long
	GetAdaptersInfo(NULL, &outBufLen);   //������������Ϣ,��һ��ʹ���Ȼ�ȡ��С(NULL�϶����������Է��ؿռ��С)
	//����PIP_ADAPTER_INFO�ṹ��ָ��
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
		printf("ѡ��һ������󶨵������豸:");
		byte num = _getch() - '0';
		printf("ѡ��һ������󶨵������豸:");
		AdapterWalker = gPIpAdapterInfo;   //����ֻ��Ϊ������豸��Ϣ���������³�ʼ��
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
	//�����׽ӿڵ�ѡ����Ҫ���þ�Ҫ���ڶ���ѡ����ΪSOL_SOCKET��SO_BROADCAST��optvalΪ1�����Ϊ0��ֹ���͹㲥����
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


	//�����˴����߳�ģ��ͻ��˷��������ݱ��ģ�����pares
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


			//parse��ɺ����߳̿�ʼ����PDU�����ͱ��ģ����а�����IP��ַ�������Ϣ���߿�������
			// Ĭ�ϵ�Server Option
			pakInfo.OptionToReplay[DHCPMESSAGETYPE] = true;
			pakInfo.OptionToReplay[SERVERIDENTIFIER] = true;
			pakInfo.OptionToReplay[IPADDRESSLEASETIME] = true;
			pakInfo.OptionToReplay[DOMAINNAME] = true;
			pakInfo.OptionToReplay[SUBNETMASK] = true;
			pakInfo.OptionToReplay[ROUTER] = true;
			pakInfo.OptionToReplay[DOMAINNAMESERVER] = true;

			ReplayOptionWalker += OptionMaker(ReplayOption + ReplayOptionWalker, &pakInfo);
			ReplayOption[ReplayOptionWalker++] = 0xFF;

			//����PDU
			dhcp.OP = 2;
			memset(dhcp.ciaddr, 0, 4); // ��Ϊ0
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