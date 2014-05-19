#ifndef _net_base_h_
#define _net_base_h_

//======================================================
/// 消息头
typedef struct tagPACKET_HEADER
{
	unsigned short	size;		/// 消息长度
} PACKET_HEADER;

//======================================================
/// 消息部分
struct tagMsg
{
	unsigned short size;
	unsigned int hdCode;
};

// 消息类开头
#define  msg_start(MSGID) \
struct tag##MSGID : public tagMsg \
{\
	tag##MSGID(){hdCode=MSGID;size = sizeof(tag##MSGID);}

// 消息类结束
#define  msg_end \
};

// 消息转换
#define  msg_translate(pMsg, pData, MSGID) \
	tag##MSGID* pMsg = (tag##MSGID*)pData;

template<typename T, typename P = void>
class CodesHandler
{
public:
	char const* name;
	unsigned int dwIndex;
	void (T::*handler)(P* m);
};
#endif