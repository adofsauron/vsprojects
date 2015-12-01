#ifndef _STDAFX_INCLUDE_H_
#define _STDAFX_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <errno.h>
#include <malloc.h>
#include <time.h>

#ifdef __WIN__
#include <WinSock2.h>
#include <Windows.h>
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include <sys/time.h>
#endif

#ifdef _U_STD_
#include <iostream>
#include <map>
#include <vector>
#include <list>
#endif //_U_STD_


#endif //_STDAFX_INCLUDE_H_