#ifndef _UTIL_H_
#define _UTIL_H_

#include "BaseType.h"

Time_t getNowTime()
{
#ifdef __LINUX__
	Time_t ntime;
	struct timeval getTime;
	gettimeofday(&getTime, NULL);
	ntime = getTime.tv_sec*1000 + getTime.tv_usec/1000;
	return ntime;
#else
	return GetTickCount();
#endif
}

#endif //_UTIL_H_