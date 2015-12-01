#include "Game.h"
#include "Config.h"

Game::Game()
{

}

Game::~Game()
{

}

VOID Game::Init()
{
	char* ip = CONFIG_IP;
	int port = CONFIG_PORT;
	s = new Socket(ip, port);
}

VOID Game::run()
{
	this->Init();
}

#ifdef NET_IO_SELECT
BOOL Game::Select()
{
	m_Timeout[SELECT_USE].tv_sec = m_Timeout[SELECT_BAK].tv_sec;
	m_Timeout[SELECT_USE].tv_usec = m_Timeout[SELECT_BAK].tv_usec;

	m_ReadFDs[SELECT_USE]		= m_ReadFDs[SELECT_BAK];
	m_WriteFDs[SELECT_USE]		= m_WriteFDs[SELECT_BAK];
	m_ExceptFDs[SELECT_USE]		= m_ExceptFDs[SELECT_BAK];

	LONG nowTm = getNowTime();

	INT	iRet = SocketAPI::select_ex((INT)m_MaxFD+1,
		&m_ReadFDs[SELECT_USE],
		&m_WriteFDs[SELECT_USE],
		&m_ExceptFDs[SELECT_USE],
		&m_Timeout[SELECT_USE] );

	if (iRet == SOCKET_ERROR)
	{
		printf("select error\n");
		return FALSE;
	}

	return TRUE;
}
#else
BOOL Game::Epoll()
{
	m_nReadCnt			= 0;
	m_nWriteCnt			= 0;
	m_nErrorCnt			= 0;
	m_nEpollReturnCnt	= 0;

	m_nEpollReturnCnt = epoll_wait(m_nEPollFD, 
		m_pEpollEventList,
		MAX_USER,
		0);
}
#endif