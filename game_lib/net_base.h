#ifndef _net_base_h_
#define _net_base_h_

//======================================================
/// ��Ϣͷ
typedef struct tagPACKET_HEADER
{
	unsigned short	size;		/// ��Ϣ����
} PACKET_HEADER;

//======================================================
/// ��Ϣ����
struct tagMsg
{
	unsigned short size;
	unsigned int hdCode;
};

// ��Ϣ�࿪ͷ
#define  msg_start(MSGID) \
struct tag##MSGID : public tagMsg \
{\
	tag##MSGID(){hdCode=MSGID;size = sizeof(tag##MSGID);}

// ��Ϣ�����
#define  msg_end \
};

// ��Ϣת��
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