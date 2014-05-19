#pragma once

#ifndef LOGGER_H_
#define LOGGER_H_

#include <Windows.h>
#include <stdio.h>
#include "singleton.h"

//��־�������ʾ��Ϣ
static const char * KEYINFOPREFIX	= " Key: \n";
static const char * ERRORPREFIX	= " Error: \n";
static const char * WARNINGPREFIX	= " Warning: \n";
static const char * INFOPREFIX		= " Info: \n";

static const int MAX_STR_LEN = 1024;
//��־����ö��
typedef enum EnumLogLevel
{
	LogLevelAll = 0,	//������Ϣ��д��־
	LogLevelMid,		//д���󡢾�����Ϣ
	LogLevelNormal,		//ֻд������Ϣ
	LogLevelStop		//��д��־
};
/*
	* ������Logger
	* ���ã��ṩд��־���ܣ�֧�ֶ��̣߳�֧�ֿɱ��β���������֧��д��־���������
	* �ӿڣ�SetLogLevel������д��־����
			TraceKeyInfo��������־����д�ؼ���Ϣ
			TraceError��д������Ϣ
			TraceWarning��д������Ϣ
			TraceInfo��дһ����Ϣ
*/
class Logger : public singleton<Logger>
{
public:
	void init(const char * strLogPath, EnumLogLevel nLogLevel = EnumLogLevel::LogLevelNormal);
	//��������
	virtual ~Logger();
public:
	//д�ؼ���Ϣ
	void TraceKeyInfo(const char * strInfo, ...);
	//д������Ϣ
	void TraceError(const char* strInfo, ...);
	//д������Ϣ
	void TraceWarning(const char * strInfo, ...);
	//дһ����Ϣ
	void TraceInfo(const char * strInfo, ...);
	//����д��־����
	void SetLogLevel(EnumLogLevel nLevel);
private:
	//д�ļ�����
	void Trace(const char * strInfo);
	//��ȡ��ǰϵͳʱ��
	char * GetCurrentTime();
	//������־�ļ�����
	void GenerateLogName();
	//������־·��
	void CreateLogPath();
private:
	//д��־�ļ���
	FILE * m_pFileStream;
	//д��־����
	EnumLogLevel m_nLogLevel;
	//��־��·��
	char m_strLogPath[MAX_STR_LEN];
	//��־������
	char m_strCurLogName[MAX_STR_LEN];
	//�߳�ͬ�����ٽ�������
	CRITICAL_SECTION m_cs;
};
#endif