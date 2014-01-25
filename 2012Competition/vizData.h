#ifndef VIZ_LINK_H
#define VIZ_LINK_H

class vizData
{
private:
	UINT32 m_ipAddress;
	char* m_addr;
	int vizFd;
	Timer currTime;
	int center, tstamp, height;
	Task task;
	static void s_recv(vizData *ptr);
	void recv();

public:
	vizData(const char* caddr = "10.5.37.21");
	int vizLink();
	int vizData::getCenter(int &ts, int &ht);
	int getHeight();
	int getPacket();
};

#endif
