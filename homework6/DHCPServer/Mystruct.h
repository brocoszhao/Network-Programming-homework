#pragma once
#include<WS2tcpip.h>     //与ipv6相关的头文件

//设置全局变量
int gDebug = 0;
byte gMyIP[4] = { 192,168,56,101 };
byte gRouter[4] = { 192,168,1,254 };
byte gSubMask[4] = { 255,255,255,0 };
byte gRouter[4] = { 192,168,1,254 };
byte gDomainName[] = "www.baidu.com";
byte gDomainNameServer[4] = { 8,8,8,8 };
int gLeaseTime = 7200;
unordered_map<int, int> gIPList;
unordered_map<int, int> gSessionList;


//548个字节
struct DHCP_PACKET {
	byte OP;
	byte HTYPE;
	byte HLEN;
	byte HOPS;
	UINT32 TRANSACTION_ID;
	UINT16 SECONDS;
	UINT16 FLAGS;
	byte ciaddr[4];
	byte yiaddr[4];
	byte siaddr[4];
	byte giaddr[4];
	byte chaddr[16];
	byte sname[64];
	byte file[128];
	UINT32 magicCode;
	byte Options[308];
};

struct Packet_Information {
	char HostName[256];
	USHORT BootFileSize;
	char MeritDumpFile[256];
	byte DHCPMessageType;
	int IPLeaseTime;          // client
	byte ServerIdentifier[4]; // client
	byte ClientIdentifier[4];
	byte ParameterRequestList[256];
	byte VendorClassIdentifier[256];
	byte RequestedIPAddress[4];
	byte Unsupport[256];
	bool OptionToReplay[256];
};