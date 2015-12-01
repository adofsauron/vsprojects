#include "Main.h"
#include "Config.h"
#include "stdafx.h"
#include "BaseType.h"

class Config;

int main()
{
	Config::loadConfig(CONFIG_NAME);

	int m	 = CONFIG_TM;
	int a	 = CONFIG_TA;
	int s	 = CONFIG_TS;
	char* ip = CONFIG_IP;
	int port = CONFIG_PORT;
	
	printf("m: %d\n", m);
	printf("a: %d\n", a);
	printf("s: %d\n", s);
	printf("ip:%s\n", ip);
	printf("port:%d\n", port);


#ifdef __LINUX__
	printf("\n%s\n", "__LINUX__");
#elif  __WIN__
	printf("\n%s\n", "__WIN__");
	getchar();
#endif
	
	return 0;
}