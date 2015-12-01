#ifndef _CONFIG_INCLUDE_H_
#define _CONFIG_INCLUDE_H_

class Config
{
public:
	Config();
	~Config();

public:
	static	void	loadConfig(char* configFile);

public:
	static	int		tm;
	static	int		ta;
	static	int		ts;
	static	char	ip[32];
	static	int		port;
};

#endif //_CONFIG_INCLUDE_H_