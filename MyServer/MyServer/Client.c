#ifndef _CLIENT_H_
#define _CLIENT_H

#include "BaseType.h"

#ifdef __LINUX__

#include "stdafx.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h> 
#include <errno.h>

int main(int argc, char **argv)
{
	if(argc<2)
	{
		printf("args should be: <ip> <port>\n");
		assert(0);
	}

	int  sd;
	struct sockaddr_in sdaddr;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	sdaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &sdaddr.sin_addr);
	sdaddr.sin_port = atoi(argv[2]);

	int res = connect(sd, (struct sockaddr *)&sdaddr, sizeof(sdaddr));
	printf("res: %d, errno: %d, %s\n", res, errno, strerror(errno));

	//sprintf(str, "%s", "send....");
	char str[1024];
	char buf[1024];
	while (1)
	{
		bzero(str, sizeof(str));
		scanf("%s\n", str);
		send(sd, str, strlen(str), 0);

		bzero(buf, sizeof(buf));
		res = recv(sd, buf, sizeof(buf), 0);
		//printf("res: %d\n", res);

		printf("recv: %s\n", buf);

	}
	return 0;
}


#endif //__LINUX__

#endif //_CLIENT_H_