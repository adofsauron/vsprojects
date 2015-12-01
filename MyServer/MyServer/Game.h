#ifndef _GAME_H_
#define _GAME_H_

#include "stdafx.h"
#include "BaseType.h"
#include "Thread.h"
#include "Util.h"
#include "SocketAPI.h"
#include "Socket.h"

class Game :public Thread
{
public:
	Game();
	~Game();
public:
	VOID			Init();
	virtual VOID	run();	//�߳��������

////////////////////////
// ���ﴦ��
public:
#ifdef NET_IO_SELECT
	BOOL	Select();
#else
	BOOL	Epoll();
#endif

private:
	Socket* s;
	Time_t m_lLastSleepTime;

#ifdef NET_IO_SELECT
	enum{
		SELECT_BAK = 0,	// ��ǰϵͳ�е������������
		SELECT_USE = 1,	// ����select���õľ������
		SELECT_MAX = 2	// �ṹʹ������
	};

	fd_set		m_ReadFDs[SELECT_MAX];		// ��fd��
	fd_set		m_WriteFDs[SELECT_MAX];		// дfd��
	fd_set		m_ExceptFDs[SELECT_MAX];	// �쳣FD��

	timeval		m_Timeout[SELECT_MAX];		// Timeout��

	SOCKET		m_MinFD;
	SOCKET		m_MaxFD;
	INT			m_nFDSize;
#else
	INT					m_nEPollFD;
	INT					m_nReadCnt;
	INT					m_nWriteCnt;
	INT					m_nErrorCnt;
	INT					m_nEpollReturnCnt;
	struct epoll_event*	m_pEpollEventList;
	struct epoll_event	m_ev;
#endif // NET_IO_SELECT

};

#endif //_GAME_H_