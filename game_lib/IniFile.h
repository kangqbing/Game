#ifndef _ini_file_h_
#define _ini_file_h_

#include <string>
#include <map>
#include "singleton.h"

using std::string;
using std::map;

class IniFile : public singleton<IniFile>
{
public:
	IniFile(void);
	~IniFile(void);

	bool	Load(const char* szPath);
	string	GetString(const char* szValue);
	int		GetInt(const char* szValue);
	double	GetDouble(const char* szValue);
private:
	map<string, string> m_mapValue;
	static const int FILE_MAX_LEN = 256;
};
#endif
