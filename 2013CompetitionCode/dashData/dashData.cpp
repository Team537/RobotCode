#include "WPILib.h"
#include "dashData.h"
#include "sysLib.h"
#include <inetLib.h>
#include <sockLib.h>

dashData::dashData(const char* caddr) :
	m_ipAddress(inet_addr((char*) caddr))
{
	m_addr = strdup(caddr);
	dashFd = -1;
	currTime.Start();
}

int
dashData::dashLink()
{
	int sockAddrSize;
	struct sockaddr_in serverAddr;
	int dashSocket;

	if (-1 != dashFd)
		close(dashFd);

	// create socket
	if ((dashSocket = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR)
	{
		perror("Camera:dash: socket");
		return 0;
	}

	sockAddrSize = sizeof(struct sockaddr_in);
	bzero((char*) &serverAddr, sockAddrSize);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_len = (u_char) sockAddrSize;
	serverAddr.sin_port = htons(1140);
	serverAddr.sin_addr.s_addr = m_ipAddress;

	// connect to server
	//printf("DashLink: connect to dashboard\n");
	if (connect(dashSocket, (struct sockaddr*) &serverAddr, sockAddrSize) == ERROR)
	{
		perror("Camera:dash: connect");
		close(dashSocket);
	}
	//printf("DashLink: connect to dashboard, sock %d\n", dashSocket);
	dashFd = dashSocket;
	return dashSocket;
}

// Offset: Usage
//     0: Packet type
//     1: offset / BLKSZ
//     2: sequence
//     3: upper byte size of this packet
//     4: lower byte size of this packet
//     5: packet number


#define CMDSZ 6
#define BLKSZ 4096
#define BUFSZ (BLKSZ + CMDSZ)
int
sendPacket(int fd, char pktType, char* data, int sz)
{
	static int seq = 0;
	int rc = 0, off = 0, ssz = BUFSZ, cnt;
	char buf[BUFSZ];

	cnt = (sz / BLKSZ) + (sz % BLKSZ ? 1 : 0);          // number of blocks
	if (sz < BLKSZ)
		ssz = sz + CMDSZ;

	while (0 < sz)
	{
		buf[0] = pktType;
		buf[1] = off / BLKSZ;
		buf[2] = seq;
		buf[3] = ((ssz - CMDSZ) >> 8) & 0xff;
		buf[4] = (ssz - CMDSZ) & 0xff;
		buf[5] = cnt;

		memcpy(buf + CMDSZ, data + off, ssz - CMDSZ);
		if (0 > (rc = send(fd, buf, ssz, 0)))
			break;
		sz -= (rc - CMDSZ);
		off += (rc - CMDSZ);
		if (sz < BLKSZ)
			ssz = sz + CMDSZ;
	}
	if (0 > rc)
		perror("sendInfo: send");
	seq = (seq + 1) % 256;
	return rc;
}

void
dashData::sendFloat(int ttype, float value)
{
	char sb[8];
	char* p;
	float ts = currTime.Get();

	p = (char*) &ts;
	sb[0] = *(p + 0);
	sb[1] = *(p + 1);
	sb[2] = *(p + 2);
	sb[3] = *(p + 3);
	p = (char*) &value;
	sb[4] = *(p + 0);
	sb[5] = *(p + 1);
	sb[6] = *(p + 2);
	sb[7] = *(p + 3);
	if (-1 == dashFd)
		dashLink();
	sendPacket(dashFd, ttype, sb, 8);
}

void dashData::sendInt(int ttype, int value)
{
	char sb[8];
	char* p;
	float ts = currTime.Get();

	p = (char*) &ts;
	sb[0] = *(p + 0);
	sb[1] = *(p + 1);
	sb[2] = *(p + 2);
	sb[3] = *(p + 3);
	p = (char*) &value;
	sb[4] = *(p + 0);
	sb[5] = *(p + 1);
	sb[6] = *(p + 2);
	sb[7] = *(p + 3);
	if (-1 == dashFd)
		dashLink();
	sendPacket(dashFd, ttype, sb, 8);
}


void
dashData::sendString(char* sb)
{
	sendPacket(dashFd, 1, sb, strlen(sb));
}

