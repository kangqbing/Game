#include "NetworkSession.h"
#include "../game_lib/net_msg.h"

CodesHandler<NetworkSession, tagMsg> NetworkMsgTable[NS_Type_Nums] =
{

};

void NetworkSession::OnRecv(void *pData, unsigned short size)
{
	tagMsg* pMsg = (tagMsg*)pData;
	if(pMsg->hdCode<NS_Type_Nums)
		(this->*(NetworkMsgTable[pMsg->hdCode].handler))(pMsg);
	else
	{
		
	}
}