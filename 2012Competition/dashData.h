#ifndef _H_DASHDATA
#define _H_DASHDATA
class dashData
{
public:
	dashData(const char* caddr = "10.5.37.5");
	int dashLink();
	void dashData::sendFloat(int ttype, float value);
	void dashData::sendInt(int ttype, int value);
	void sendString(char* sb);
private:
	UINT32 m_ipAddress;
	char* m_addr;
	int dashFd;
	Timer currTime;
};

#endif








