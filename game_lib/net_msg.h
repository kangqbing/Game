#ifndef _NET_MSG_H_
#define _NET_MSG_H_

#include "net_base.h"

enum  nc_codes
{
	nc_playerAuthSession = 0,
	NC_Type_Nums
};

enum  ns_codes
{
	ns_playerAuthSession = 0,
	NS_Type_Nums
};

#pragma pack(push, 1) 

msg_start(nc_playerAuthSession)
	unsigned int playerID;
msg_end

#pragma pack(pop)
#endif