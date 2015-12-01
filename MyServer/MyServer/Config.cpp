#include "Config.h"
#include "tinyxml.h"

int Config::tm = 0;
int Config::ta = 0;
int Config::ts = 0;

char Config::ip[32] = {0};
int	  Config::port	= 0;


Config::Config()
{
}

Config::~Config()
{
}

void Config::loadConfig(char* configFile)
{
	TiXmlDocument myDoc(configFile);
	myDoc.LoadFile();
	TiXmlHandle		docHandle(&myDoc);
	TiXmlElement*	subElem	= docHandle.FirstChildElement().Element();

	TiXmlNode*	test = subElem->FirstChild("TEST");
	tm = atoi(test->FirstChild("TM")->ToElement()->Attribute("value"));
	ta = atoi(test->FirstChild("TA")->ToElement()->Attribute("value"));
	ts = atoi(test->FirstChild("TS")->ToElement()->Attribute("value"));

	TiXmlNode*	net = subElem->FirstChild("Net");
	memcpy(ip, (char*)net->ToElement()->Attribute("ip"),sizeof(ip));
	port = atoi(net->ToElement()->Attribute("port"));
}