#ifndef _THREAD_H_
#define _THREAD_H_

#include "stdafx.h"
#include "BaseType.h"

#ifdef __LINUX__
#include <pthread.h>
#endif

class Thread
{
public:
	enum ThreadStatus
	{
		READY,		// �߳�׼��״̬
		RUNNING,	// ����״̬
		EXITING,	// �����˳�
		EXIT		// �Ѿ��˳�
	};

public:
	Thread();
	virtual ~Thread();

public:
	VOID			start();
	virtual	VOID	stop();
	VOID			exit(VOID* retval=NULL);
	virtual VOID	run();

#ifdef __WIN__
	static ULONG WINAPI MyThreadProcess(VOID* derivedThread);
#elif defined __LINUX__
	static VOID*		MyThreadProcess(VOID* derivedThread);
#endif

public:
	TID				getTID(){ return m_TID; }
	ThreadStatus	getStatus(){ return m_status; }
	inline VOID		setThreadStatus(ThreadStatus status){ m_status = status; }

private:
	TID				m_TID;
	ThreadStatus	m_status;
	VOID*			m_hThread;

};

#endif //_THREAD_H_