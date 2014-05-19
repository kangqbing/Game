#include "ClientSocket.h"
#include "..\game_lib\net_msg.h"
#include <thread>
#include "LifeCircleMutexLock.h"
ClientSocket::ClientSocket(void)
{
	m_sendBuff = new char[MAX_SEND_LEN+sizeof(PACKET_HEADER)];
	m_recvBuff = new char[MAX_RECV_LEN];

	memset(m_sendBuff, 0, MAX_SEND_LEN+sizeof(PACKET_HEADER));
	memset(m_recvBuff, 0, MAX_RECV_LEN);

	m_recvPos = 0;
	m_networkObject = new NetworkSession;
}

ClientSocket::~ClientSocket(void)
{
	delete m_sendBuff;
	delete m_recvBuff;
}

int ClientSocket::start(const char* host, unsigned short port)
{
	Init();
	if (Create() == false)
	{
		return -1;
	}
	if (Connect(host, port)==false)
	{
		return -1;
	}

	std::thread recvThread([=]{
		char buff[MAX_SEND_LEN] = {0};
		while (m_bRun)
		{
			int res = recv(m_sock, buff, MAX_RECV_LEN-m_recvPos, 0);
			if(res>0)
			{
				{
					LifeCircleMutexLock(NetworkMessageQueueLock);
					memcpy(m_recvBuff+m_recvPos, buff, res);
					m_recvPos +=res;
				}
				
				while (m_recvPos>=MAX_RECV_LEN)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
				}
			}
			else if (res == 0)	//·þÎñÆ÷¹Ø±Õ
			{
				Close();
				break;
			}
			else if (res == SOCKET_ERROR)
			{
				Close();
				break;
			}	
		}
	});

	return 0;
}

void ClientSocket::ProcessRecvdPacket()
{
	LifeCircleMutexLock(NetworkMessageQueueLock);
	PACKET_HEADER	*pHeader;
	pHeader = (PACKET_HEADER *)m_recvBuff;
	while (pHeader->size+sizeof(PACKET_HEADER)<m_recvPos)
	{
		m_networkObject->OnRecv(m_recvBuff+sizeof(PACKET_HEADER), pHeader->size);
		m_recvPos -=pHeader->size+sizeof(PACKET_HEADER);
		memcpy(m_recvBuff, m_recvBuff+pHeader->size+sizeof(PACKET_HEADER), m_recvPos);
	}
}

int ClientSocket::sendEx(const char* buf, int len, int flags /* =0 */)
{	
	PACKET_HEADER header;
	header.size = len;
 	memcpy(m_sendBuff, &header, sizeof(PACKET_HEADER));
 	memcpy(m_sendBuff+sizeof(PACKET_HEADER), buf, len);
 	len +=sizeof(PACKET_HEADER);

	return Send(m_sendBuff, len, flags);
}

