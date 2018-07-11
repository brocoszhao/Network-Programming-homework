#pragma once
#include<WS2tcpip.h> 
#include"DHCPOptionEnum.h"
#include"Mystruct.h"

int ByteOptionWriter(byte opt, byte * retOptionArray, int len, void * inputarray) {
	return 0;
}


int AnsiOptionWriter(byte opt, byte * retOptionArray, int len, void * inputarray) {
	retOptionArray[0] = opt;
	retOptionArray[1] = len;
	memcpy(retOptionArray + 2, inputarray, len);
	return len + 2;
}


int AddressOptionWriter(byte opt, byte * retOptionArray, int len, byte * inputarray) {
	retOptionArray[0] = opt;
	retOptionArray[1] = len;
	int ReplayOptionWalker = 2;
	for (int i = 0; i < len / 4; i++) {
		memcpy(retOptionArray + ReplayOptionWalker, &inputarray[i * 4], 4);
		ReplayOptionWalker += 4;
	}
	return ReplayOptionWalker;
}

int ChangeEndian(int var) {
	return (var & 0xFF) << 24 | (var & 0xFF00) << 8 | (var & 0xFF0000) >> 8 | (var & 0xFF000000) >> 24;
}


int OptionMaker(byte * ReplayOption, Packet_Information * packInfo) {
	int ReplayOptionWalker = 0;
	if (packInfo->OptionToReplay[DHCPMESSAGETYPE]) { // ×îƒžÏÈ»Ø
		switch (packInfo->DHCPMessageType) {
		case DHCPDISCOVER:
			ReplayOption[2] = DHCPOFFER;
			break;
		case DHCPOFFER: break;
		case DHCPREQUEST:
			ReplayOption[2] = DHCPACK;
			break;
		case DHCPDECLINE: break;
		case DHCPACK: break;
		case DHCPNAK: break;
		case DHCPRELEASE: break;
		case DHCPINFORM: break;
		}
		ReplayOption[0] = DHCPMESSAGETYPE;
		ReplayOption[1] = 1;
		ReplayOptionWalker += 3;
	}
	if (packInfo->OptionToReplay[SERVERIDENTIFIER]) {
		ReplayOptionWalker += AddressOptionWriter(SERVERIDENTIFIER, ReplayOption + ReplayOptionWalker, 4, gMyIP);
	}
	if (packInfo->OptionToReplay[IPADDRESSLEASETIME]) {
		ReplayOption[ReplayOptionWalker] = IPADDRESSLEASETIME;
		ReplayOption[ReplayOptionWalker + 1] = 4;
		int tmpTime = ChangeEndian(gLeaseTime);
		memcpy(ReplayOption + ReplayOptionWalker + 2, &tmpTime, 4);
		ReplayOptionWalker += 6;
	}
	if (packInfo->OptionToReplay[SUBNETMASK]) {
		ReplayOptionWalker += AddressOptionWriter(SUBNETMASK, ReplayOption + ReplayOptionWalker, 4, gSubMask);
	}
	if (packInfo->OptionToReplay[TIMEOFFSET]) {
	}
	if (packInfo->OptionToReplay[ROUTER]) {
		ReplayOptionWalker += AddressOptionWriter(ROUTER, ReplayOption + ReplayOptionWalker, 4, gRouter);
	}
	if (packInfo->OptionToReplay[TIMESERVER]) {
	}
	if (packInfo->OptionToReplay[NAMESERVER]) {
	}
	if (packInfo->OptionToReplay[DOMAINNAMESERVER]) {
		ReplayOptionWalker += AddressOptionWriter(DOMAINNAMESERVER, ReplayOption + ReplayOptionWalker, 4, gDomainNameServer);
	}
	if (packInfo->OptionToReplay[LOGSERVER]) {
	}
	if (packInfo->OptionToReplay[COOKIESERVER]) {
	}
	if (packInfo->OptionToReplay[LPRSERVER]) {
	}
	if (packInfo->OptionToReplay[IMPRESSSERVER]) {
	}
	if (packInfo->OptionToReplay[RESOURCELOCSERVER]) {
	}
	if (packInfo->OptionToReplay[HOSTNAME]) {
	}
	if (packInfo->OptionToReplay[BOOTFILESIZE]) {
	}
	if (packInfo->OptionToReplay[MERITDUMP]) {
	}
	if (packInfo->OptionToReplay[DOMAINNAME]) {
		ReplayOptionWalker += AnsiOptionWriter(DOMAINNAME, ReplayOption + ReplayOptionWalker, sizeof(gDomainName), gDomainName);
	}
	if (packInfo->OptionToReplay[SWAPSERVER]) {
	}
	if (packInfo->OptionToReplay[ROOTPATH]) {
	}
	if (packInfo->OptionToReplay[EXTENSIONSPATH]) {
	}
	if (packInfo->OptionToReplay[IPFORWARDING]) {
	}
	if (packInfo->OptionToReplay[NONLOCALSOURCEROUTING]) {
	}
	if (packInfo->OptionToReplay[POLICYFILTER]) {
	}
	if (packInfo->OptionToReplay[MAXIMUMDATAGRAMREASSEMBLYSIZE]) {
	}
	if (packInfo->OptionToReplay[DEFAULTIPTIMETOLIVE]) {
	}
	if (packInfo->OptionToReplay[PATHMTUAGINGTIMEOUT]) {
	}
	if (packInfo->OptionToReplay[PATHMTUPLATEAUTABLE]) {
	}
	if (packInfo->OptionToReplay[INTERFACEMTU]) {
	}
	if (packInfo->OptionToReplay[ALLSUBNETSARELOCAL]) {
	}
	if (packInfo->OptionToReplay[BROADCASTADDRESS]) {
	}
	if (packInfo->OptionToReplay[PERFORMMASKDISCOVERY]) {
	}
	if (packInfo->OptionToReplay[MASKSUPPLIER]) {
	}
	if (packInfo->OptionToReplay[PERFORMROUTERDISCOVERY]) {
	}
	if (packInfo->OptionToReplay[ROUTERSOLICITATIONADDRESS]) {
	}
	if (packInfo->OptionToReplay[STATICROUTE]) {
	}
	if (packInfo->OptionToReplay[TRAILERENCAPSULATION]) {
	}
	if (packInfo->OptionToReplay[ARPCACHETIMEOUT]) {
	}
	if (packInfo->OptionToReplay[ETHERNETENCAPSULATION]) {
	}
	if (packInfo->OptionToReplay[TCPDEFAULTTTL]) {
	}
	if (packInfo->OptionToReplay[TCPKEEPALIVEINTERVAL]) {
	}
	if (packInfo->OptionToReplay[TCPKEEPALIVEGARBAGE]) {
	}
	if (packInfo->OptionToReplay[NETWORKINFORMATIONSERVICEDOMAIN]) {
	}
	if (packInfo->OptionToReplay[NETWORKINFORMATIONSERVERS]) {
	}
	if (packInfo->OptionToReplay[NETWORKTIMEPROTOCOLSERVERS]) {
	}
	if (packInfo->OptionToReplay[VENDORSPECIFICINFORMATION]) {
	}
	if (packInfo->OptionToReplay[NETBIOSOVERTCPIPNAMESERVER]) {
	}
	if (packInfo->OptionToReplay[NETBIOSOVERTCPIPDATAGRAMDISTRIBUTIONSERVER]) {
	}
	if (packInfo->OptionToReplay[NETBIOSOVERTCPIPNODETYPE]) {
	}
	if (packInfo->OptionToReplay[NETBIOSOVERTCPIPSCOPE]) {
	}
	if (packInfo->OptionToReplay[XWINDOWSYSTEMFONTSERVER]) {
	}
	if (packInfo->OptionToReplay[XWINDOWSYSTEMDISPLAYMANAGER]) {
	}
	if (packInfo->OptionToReplay[REQUESTEDIPADDRESS]) {
	}
	if (packInfo->OptionToReplay[OPTIONOVERLOAD]) {
	}

	if (packInfo->OptionToReplay[PARAMETERREQUESTLIST]) {
	}
	if (packInfo->OptionToReplay[MESSAGE]) {
	}
	if (packInfo->OptionToReplay[MAXIMUMDHCPMESSAGESIZE]) {
	}
	if (packInfo->OptionToReplay[RENEWALTIMEVALUE_T1]) {
	}
	if (packInfo->OptionToReplay[REBINDINGTIMEVALUE_T2]) {
	}
	if (packInfo->OptionToReplay[VENDORCLASSIDENTIFIER]) {
	}
	if (packInfo->OptionToReplay[CLIENTIDENTIFIER]) {
	}
	if (packInfo->OptionToReplay[NETWORKINFORMATIONSERVICEPLUSDOMAIN]) {
	}
	if (packInfo->OptionToReplay[NETWORKINFORMATIONSERVICEPLUSSERVERS]) {
	}
	if (packInfo->OptionToReplay[TFTPSERVERNAME]) {
	}
	if (packInfo->OptionToReplay[BOOTFILENAME]) {
	}
	if (packInfo->OptionToReplay[MOBILEIPHOMEAGENT]) {
	}
	if (packInfo->OptionToReplay[SMTPSERVER]) {
	}
	if (packInfo->OptionToReplay[POP3SERVER]) {
	}
	if (packInfo->OptionToReplay[NNTPSERVER]) {
	}
	if (packInfo->OptionToReplay[DEFAULTWWWSERVER]) {
	}
	if (packInfo->OptionToReplay[DEFAULTFINGERSERVER]) {
	}
	if (packInfo->OptionToReplay[DEFAULTIRCSERVER]) {
	}
	if (packInfo->OptionToReplay[STREETTALKSERVER]) {
	}
	if (packInfo->OptionToReplay[STDASERVER]) {
	}
	return ReplayOptionWalker;
}