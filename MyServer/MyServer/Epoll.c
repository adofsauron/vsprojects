
#ifndef _EPOLL_H_
#define _EPOLL_H_

#include "BaseType.h"

#ifdef __LINUX__

#include "stdafx.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h> 
#include <sys/epoll.h>
#include <fcntl.h>
#include <pthread.h>

#define EVENTS_NOMBER 1024


struct recv
{
	char header[256];
	char data[1024];

	char recvbuf[1024];
	char sendbuf[1024];

	int sockedfd;
	int retfd;
};

struct sock_operations
{
	int(*get_sockfd)(const char *domain, int port);
	int(*setNoneBlocking)(int fd);
	void(*add_eventfd)(int epollfd, int fd);
	void(*pth_work)(pthread_t *pid, void *fd);

};

struct  Recv_sock
{
	struct recv recvdata;
	struct sock_operations operations;
};


int setNoneBlocking(int fd)
{
	int old = fcntl(fd, F_GETFL);
	int new = old | O_NONBLOCK;
	fcntl(fd, F_SETFL, new);
	return old;
}

void addfd(int epollfd, int fd)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setNoneBlocking(fd);
}

void *work(void *recv_sock_addr)
{
	struct Recv_sock *recv_sock = (struct Recv_sock *) recv_sock_addr;
	int retfd = recv_sock->recvdata.retfd;

	bzero(recv_sock->recvdata.recvbuf, sizeof(recv_sock->recvdata.recvbuf));
	bzero(recv_sock->recvdata.sendbuf, sizeof(recv_sock->recvdata.sendbuf));

	int len = recv(retfd, recv_sock->recvdata.recvbuf, sizeof(recv_sock->recvdata.recvbuf), 0);
	printf("recvbuf: %s\n", recv_sock->recvdata.recvbuf);

	sprintf(recv_sock->recvdata.sendbuf, "len: %d, data:%s\n", len, recv_sock->recvdata.recvbuf);
	send(retfd, recv_sock->recvdata.sendbuf, sizeof(recv_sock->recvdata.sendbuf), 0);
	pthread_exit(NULL);
}

void pth_work(pthread_t *pid, void *recv_sock)
{
	pthread_create(pid, NULL, work, recv_sock);
}

int get_sockfd(const char *domain, int port)
{
	int sd;
	struct sockaddr_in addr;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	const char *ip = domain;
	inet_pton(AF_INET, ip, &addr.sin_addr);
	addr.sin_port = port;
	int res = bind(sd, (struct sockaddr *)&addr, sizeof(addr));

	sd = res >= 0 ? sd : -1;

	return sd;

}

struct sock_operations  operations =
{
	.get_sockfd = get_sockfd,
	.setNoneBlocking = setNoneBlocking,
	.add_eventfd = addfd,
	.pth_work = pth_work
};

struct  Recv_sock * init(void)
{
	struct  Recv_sock *recv_sock = (struct Recv_sock *) malloc(sizeof(struct Recv_sock));
	recv_sock->operations = operations;

	return recv_sock = recv_sock == NULL ? NULL : recv_sock;
}

int main(int argc, char **argv)
{
	if(argc<2)
	{
		printf("args should be: <ip> <port>\n");
		assert(0);
	}

	struct Recv_sock *recv_sock = init();

	recv_sock->recvdata.sockedfd = recv_sock->operations.get_sockfd(argv[1], atoi(argv[2]));

	printf("sd: %d\n", recv_sock->recvdata.sockedfd);

	listen(recv_sock->recvdata.sockedfd, 5);

	struct epoll_event events[EVENTS_NOMBER];
	int epollfd = epoll_create(5);

	recv_sock->operations.add_eventfd(epollfd, recv_sock->recvdata.sockedfd);

	pthread_t pid;
	while (1)
	{
		int ret = epoll_wait(epollfd, events, EVENTS_NOMBER, -1);
		int i;
		for (i = 0; i<ret; i++)
		{
			recv_sock->recvdata.retfd = events[i].data.fd;

			if (recv_sock->recvdata.retfd == recv_sock->recvdata.sockedfd)
			{
				struct sockaddr_in client_address;
				socklen_t client_addrlength = sizeof(client_address);
				int connfd = accept(recv_sock->recvdata.sockedfd, (struct sockaddr*)&client_address, &client_addrlength);
				recv_sock->operations.add_eventfd(epollfd, connfd);
			}
			else if (events[i].events & EPOLLIN)
			{
				recv_sock->operations.pth_work(&pid, recv_sock);
				pthread_join(pid, NULL);
			}
			else
			{
				//printf("something happen...\n");
			}
		}
	}


	return 0;
}

#endif //LIINUX

#endif //_EPOLL_H_

