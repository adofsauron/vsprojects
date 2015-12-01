#ifndef _BASETYPE_INCLUDE_H_
#define _BASETYPE_INCLUDE_H_

#include "stdafx.h"

#ifndef __WIN__
#	ifndef __LINUX__
#		define __LINUX__
#	endif
#endif

#ifndef __LINUX__
#define NET_IO_SELECT
#endif

#define VOID			void
#define	TRUE			1
#define FALSE			0
typedef unsigned char	UCHAR;
typedef char			CHAR;
typedef	unsigned int	UINT;
typedef int				INT;
typedef unsigned short	USHORT;
typedef short			SHORT;
typedef unsigned long	ULONG;
typedef long			LONG;
typedef	float			FLOAT;
typedef	double			DOUBLE;

typedef ULONG			IP_t;
typedef USHORT			WORD;
typedef	INT				BOOL;
typedef	LONG			Time_t;
#ifdef __WIN__
typedef ULONG			TID;
#else
typedef pthread_t		TID;
#endif


#ifdef __WIN__
#	define _TRY
#	define _CATCH if(0)
#else
#	define _TRY	try
#	define _CATCH	catch(...){printf("catch error\n")}
#	define _CATCH	catch(...)
#endif

#define MAX_USER		20
#define IP_SIZE			24

#define CONFIG_NAME "Server.xml"

#define CONFIG_TM	Config::tm
#define CONFIG_TA	Config::ta
#define CONFIG_TS	Config::ts
#define CONFIG_IP	Config::ip
#define CONFIG_PORT Config::port

#endif // _BASETYPE_INCLUDE_H_