#include "WPILib.h"
#include "vizData.h"
#include "sysLib.h"
#include <inetLib.h>
#include <sockLib.h>

vizData::vizData(const char* caddr) :
	m_ipAddress(inet_addr((char*) caddr)), 
	task("viztask", (FUNCPTR) s_recv)
{
	m_addr = strdup(caddr);
	vizFd = -1;
	currTime.Start();
	height = center = 0;
	task.Start((INT32) this);
}

void vizData::s_recv(vizData *ptr)
{
	ptr->recv();
}

void vizData::recv()
{
	vizLink();
	while (1) {
		getPacket();                 // sets center
	}
}

int vizData::vizLink()
{
	int sockAddrSize;
	struct sockaddr_in serverAddr;
	int vizSocket;

	if (-1 != vizFd)
		close(vizFd);

	// create socket
	if ((vizSocket = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR)
	{
		//perror("Camera:Viz: socket");
		return 0;
	}

	sockAddrSize = sizeof(struct sockaddr_in);
	bzero((char*) &serverAddr, sockAddrSize);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_len = (u_char) sockAddrSize;
	serverAddr.sin_port = htons(1130);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// connect to server
	//printf("VizLink: bind to dashboard\n");
	if (bind(vizSocket, (struct sockaddr*) &serverAddr, sockAddrSize) == ERROR)
	{
		//perror("Camera:viz: bind");
		close(vizSocket);
	}
	//printf("VizLink: bind to dashboard, sock %d\n", vizSocket);
	vizFd = vizSocket;
	return vizSocket;
}

int vizData::getCenter(int &ts, int &ht)
{
	ht = height;
	ts = tstamp;
	return center;
}

int
buf2int(char *buf, int off)
{
	int val = buf[off] + (buf[off+1] << 8) + (buf[off+2] << 16) + (buf[off+3] << 24);
	return val;
}

int vizData::getPacket()
{
	char buf[10];
	int rc;
	rc = recvfrom(vizFd, buf, 10, 0, NULL, NULL);
	
	if (currTime.Get() > 0.25) {
		//printf("got %d errno %d bytes %x %x %x %x\n", rc, errno, buf[6], buf[7], buf[8], buf[9]);
		currTime.Reset();
	}
	if (14 == rc)
	{
		center = buf2int(buf, 6);
		height = buf2int(buf, 10);
		tstamp = buf[2];
	}
	return rc;
}
