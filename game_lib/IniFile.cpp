#include "StdAfx.h"
#include "IniFile.h"
#include <cassert>

IniFile::IniFile(void)
{
}

IniFile::~IniFile(void)
{
}
bool IniFile::Load(const char* szPath)
{
	FILE* pFile;
	fopen_s(&pFile, szPath, "r");
	if (pFile == NULL) 
	{
		assert(0);
		return false;
	}	
	char	szValue[FILE_MAX_LEN]={0};
	string str, strKey, strName, strValue;
	while(!feof(pFile))
	{
		fgets(szValue, FILE_MAX_LEN, pFile);
		str = szValue;
		if (str[0] == '#') // Îª×¢ÊÍ
		{
			continue;
		}
		else if (str.find('[') != string::npos && str.find(']') != string::npos)
		{
			strKey = str.substr(1, str.find_first_of(']')-1);
		}
		else if (str.find('=') != string::npos && str.find('"') != string::npos)
		{
			strName = str.substr(0, str.find_first_of('='));
			strName =strKey + '.' + strName;

			strValue = str.substr(str.find_first_of('"')+1);
			strValue = strValue.substr(0, strValue.find_last_of('"'));

			m_mapValue.insert(make_pair(strName, strValue));
		}
	}
	return true;
}

string IniFile::GetString(const char* szValue)
{
	map<string, string>::iterator iter = m_mapValue.find(szValue);
	if (iter != m_mapValue.end())
	{
		return iter->second;
	}
	assert(0);
	return 0;
}

double IniFile::GetDouble(const char* szValue)
{
	map<string, string>::iterator iter = m_mapValue.find(szValue);
	if (iter != m_mapValue.end())
	{
		return strtod((iter->second).c_str(), NULL);
	}
	assert(0);
	return 0;
}

int IniFile::GetInt(const char* szValue)
{
	map<string, string>::iterator iter = m_mapValue.find(szValue);
	if (iter != m_mapValue.end())
	{
		return (int)strtod((iter->second).c_str(), NULL);
	}
	assert(0);
	return 0;
}