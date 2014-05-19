#pragma once
#include "ODSocket.h"
#include "NetworkSession.h"
#include "../game_lib/singleton.h"
#define MAX_SEND_LEN 512
#define MAX_RECV_LEN 10240
class ClientSocket : public ODSocket, public singleton<ClientSocket>
{
public:
	ClientSocket(void);
	~ClientSocket(void);
	int start(const char* host, unsigned short port);

	int sendEx(const char* buf, int len, int flags =0);

	void ProcessRecvdPacket();
private:
	char* m_sendBuff;
	bool m_bRun;
	char* m_recvBuff;
	unsigned int  m_recvPos;
	NetworkSession* m_networkObject;
};

