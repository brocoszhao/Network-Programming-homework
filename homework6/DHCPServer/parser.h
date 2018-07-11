#pragma once
#include"stdafx.h"
#include"DHCPOptionEnum.h"
#include"Mystruct.h"
#include<conio.h>     //控制台的一些函数调用
#include<winsock2.h>
#include<thread>      
#include<unordered_map>
#include<iphlpapi.h>     //获取网络信息的函数
#include<WS2tcpip.h>     //与ipv6相关的头文件

void byteToHexStr(byte * in, char * out, int size) {
	int current = 0;
	out[0] = 0;
	while (current < size) {
		sprintf(out, "%s%02X ", out, in[current++]);
	}
}

void ParserByteTypeOption(byte opt, byte * OptionArray, int len, const char * name, byte * retarray) {
	memcpy(retarray, OptionArray, len);
	char * tmp = new char[len * 3 + 1];
	byteToHexStr(OptionArray, tmp, len);
	printf(" *%s(%d) : %s\n", name, opt, tmp);
	delete tmp;
}

void ParserAnsiTypeOption(byte opt, byte * OptionArray, int len, const char * name, void * retarray) {
	memcpy(retarray, OptionArray, len);
	((char *)retarray)[len] = 0;
	printf(" *%s(%d) : %s\n", name, opt, retarray);
}

void ParserByteTypeOption(byte opt, byte * OptionArray, int len, const char * name, byte * retarray) {
	memcpy(retarray, OptionArray, len);
	char * tmp = new char[len * 3 + 1];
	byteToHexStr(OptionArray, tmp, len);
	printf(" *%s(%d) : %s\n", name, opt, tmp);
	delete tmp;
}

void ParserAddressTypeOption(byte opt, byte * OptionArray, int len, const char * name, byte * retarray) {
	memcpy(retarray, OptionArray, len);
	for (int i = 0; i < len / 4; i++) {
		printf(" *%s(%d) : %d.%d.%d.%d\n", name, opt, OptionArray[i * 4], OptionArray[i * 4 + 1], OptionArray[i * 4 + 2], OptionArray[i * 4 + 3]);
	}
}

void ParserIntTypeOption(byte opt, byte * OptionArray, int len, const char * name, void * retarray) {
	for (int i = 0; i < len; i++) {
		((byte *)retarray)[len - i - 1] = OptionArray[i];
	}
	switch (len) {
	case 4:
		printf(" *%s(%d) : %d\n", name, opt, ((UINT *)retarray)[0]); break;
	case 2:printf(" *%s(%d) : %d\n", name, opt, ((USHORT *)retarray)[0]); break;
	case 1:printf(" *%s(%d) : %d\n", name, opt, ((byte *)retarray)[0]); break;
	default: break;
	}
}

void OptionParser(byte * optionarray, Packet_Information * packInfo) {
	bool end = false;
	while (optionarray[0] && !end) {
		short len = optionarray[1];
		switch (optionarray[0]) {
		case 0:
			len = -1; // 只去除該padding
			break;
		case SUBNETMASK:
			ParserAddressTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Subnet Mask", packInfo->Unsupport);
			break;
		case TIMEOFFSET:
			ParserAddressTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Time Offset", packInfo->Unsupport);
			break;
		case ROUTER:
			ParserAddressTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Router", packInfo->Unsupport);
			break;
		case TIMESERVER:
			ParserAddressTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Time Server", packInfo->Unsupport);
			break;
		case NAMESERVER:
			ParserAddressTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Name Server", packInfo->Unsupport);
			break;
		case DOMAINNAMESERVER:
			ParserAddressTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Domain Name Server", packInfo->Unsupport);
			break;
		case LOGSERVER:
			ParserAddressTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Log Server", packInfo->Unsupport);
			break;
		case COOKIESERVER:
			ParserAddressTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Cookie Server", packInfo->Unsupport);
			break;
		case LPRSERVER:
			ParserAddressTypeOption(optionarray[0], optionarray + 2, optionarray[1], "LPR Server", packInfo->Unsupport);
			break;
		case IMPRESSSERVER:
			ParserAddressTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Impress Server", packInfo->Unsupport);
			break;
		case RESOURCELOCSERVER:
			ParserAddressTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Resource Location Server", packInfo->Unsupport);
			break;
		case HOSTNAME:
			ParserAnsiTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Host Name", packInfo->HostName);
			break;
		case BOOTFILESIZE:
			ParserIntTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Boot File Size", &packInfo->BootFileSize);
			break;
		case MERITDUMP:
			ParserAnsiTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Merit Dump File", packInfo->MeritDumpFile);
			break;
		case DOMAINNAME:
			ParserAnsiTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Domain Name", (char *)packInfo->Unsupport);
			break;
		case SWAPSERVER:
			ParserAddressTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Swap Server", packInfo->Unsupport);
			break;
		case ROOTPATH:
			ParserAnsiTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Root Path", packInfo->Unsupport);
			break;
		case EXTENSIONSPATH:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Extensions Path", packInfo->Unsupport);
			break;
		case IPFORWARDING:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "IP Forwarding", packInfo->Unsupport);
			break;
		case NONLOCALSOURCEROUTING:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Non-Local Source Routing", packInfo->Unsupport);
			break;
		case POLICYFILTER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Policy Filter", packInfo->Unsupport);
			break;
		case MAXIMUMDATAGRAMREASSEMBLYSIZE:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Maximum Datagram Reassembly Size", packInfo->Unsupport);
			break;
		case DEFAULTIPTIMETOLIVE:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Default IP Time-to-live", packInfo->Unsupport);
			break;
		case PATHMTUAGINGTIMEOUT:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Path MTU Aging Timeout", packInfo->Unsupport);
			break;
		case PATHMTUPLATEAUTABLE:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Path MTU Plateau Table", packInfo->Unsupport);
			break;
		case INTERFACEMTU:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Interface MTU", packInfo->Unsupport);
			break;
		case ALLSUBNETSARELOCAL:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "All Subnets are Local", packInfo->Unsupport);
			break;
		case BROADCASTADDRESS:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Broadcast Address", packInfo->Unsupport);
			break;
		case PERFORMMASKDISCOVERY:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Perform Mask Discovery", packInfo->Unsupport);
			break;
		case MASKSUPPLIER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Mask Supplier", packInfo->Unsupport);
			break;
		case PERFORMROUTERDISCOVERY:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Perform Router Discovery", packInfo->Unsupport);
			break;
		case ROUTERSOLICITATIONADDRESS:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Router Solicitation Address", packInfo->Unsupport);
			break;
		case STATICROUTE:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Static Route", packInfo->Unsupport);
			break;
		case TRAILERENCAPSULATION:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Trailer Encapsulation", packInfo->Unsupport);
			break;
		case ARPCACHETIMEOUT:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "ARP Cache Timeout", packInfo->Unsupport);
			break;
		case ETHERNETENCAPSULATION:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Ethernet Encapsulation", packInfo->Unsupport);
			break;
		case TCPDEFAULTTTL:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "TCP Default TTL", packInfo->Unsupport);
			break;
		case TCPKEEPALIVEINTERVAL:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "TCP Keepalive Interval", packInfo->Unsupport);
			break;
		case TCPKEEPALIVEGARBAGE:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "TCP Keepalive Garbage", packInfo->Unsupport);
			break;
		case NETWORKINFORMATIONSERVICEDOMAIN:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Network Information Service Domain", packInfo->Unsupport);
			break;
		case NETWORKINFORMATIONSERVERS:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Network Information Servers", packInfo->Unsupport);
			break;
		case NETWORKTIMEPROTOCOLSERVERS:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Network Time Protocol Servers", packInfo->Unsupport);
			break;
		case VENDORSPECIFICINFORMATION:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Vendor Specific Information", packInfo->Unsupport);
			break;
		case NETBIOSOVERTCPIPNAMESERVER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "NetBIOS over TCP/IP Name Server", packInfo->Unsupport);
			break;
		case NETBIOSOVERTCPIPDATAGRAMDISTRIBUTIONSERVER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "NetBIOS over TCP/IP Datagram Distribution Server", packInfo->Unsupport);
			break;
		case NETBIOSOVERTCPIPNODETYPE:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "NetBIOS over TCP/IP Node Type", packInfo->Unsupport);
			break;
		case NETBIOSOVERTCPIPSCOPE:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "NetBIOS over TCP/IP Scope", packInfo->Unsupport);
			break;
		case XWINDOWSYSTEMFONTSERVER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "X Window System Font Server", packInfo->Unsupport);
			break;
		case XWINDOWSYSTEMDISPLAYMANAGER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "X Window System Display Manager", packInfo->Unsupport);
			break;
		case REQUESTEDIPADDRESS:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Requested IP Address", packInfo->Unsupport);
			break;
		case IPADDRESSLEASETIME:
			ParserIntTypeOption(optionarray[0], optionarray + 2, optionarray[1], "IP Address Lease Time", (void *)&packInfo->IPLeaseTime);
			break;
		case OPTIONOVERLOAD:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Option Overload", packInfo->Unsupport);
			break;
		case DHCPMESSAGETYPE:
			ParserIntTypeOption(optionarray[0], optionarray + 2, optionarray[1], "DHCP Message Type", &packInfo->DHCPMessageType);
			break;
		case SERVERIDENTIFIER:
			ParserAddressTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Server Identifier", packInfo->ServerIdentifier);
			break;
		case PARAMETERREQUESTLIST:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case MESSAGE:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case MAXIMUMDHCPMESSAGESIZE:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case RENEWALTIMEVALUE_T1:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case REBINDINGTIMEVALUE_T2:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case VENDORCLASSIDENTIFIER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case CLIENTIDENTIFIER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Client-identifier", packInfo->ClientIdentifier);
			break;
		case NETWORKINFORMATIONSERVICEPLUSDOMAIN:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case NETWORKINFORMATIONSERVICEPLUSSERVERS:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case TFTPSERVERNAME:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case BOOTFILENAME:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case MOBILEIPHOMEAGENT:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case SMTPSERVER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case POP3SERVER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case NNTPSERVER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case DEFAULTWWWSERVER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case DEFAULTFINGERSERVER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case DEFAULTIRCSERVER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case STREETTALKSERVER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case STDASERVER:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "UnSupportOption", packInfo->Unsupport);
			break;
		case END_OPTION:
			end = true;
			break;
		default:
			ParserByteTypeOption(optionarray[0], optionarray + 2, optionarray[1], "Unknow Option", packInfo->Unsupport);
			break;
		}
		optionarray += len + 2; // 下一個option
	}
}