#include "Thread.h"

Thread::Thread()
{
	m_TID		= 0;
	m_status	= Thread::READY;
	m_hThread = NULL;
}

Thread::~Thread()
{
}

VOID Thread::start()
{
	if (m_status != Thread::READY)
	{
		printf("Thread has ready run\n");
		assert(FALSE);
		return;
	}

#ifdef __WIN__
	::CreateThread(NULL, 0, MyThreadProcess, this, 0, &m_TID);
#else
	INT ret = pthread_create(&m_TID, NULL, MyThreadProcess, this);
	if (ret != 0)
	{
		printf("pthread_create faild\n");
		assert(FALSE);
	}
#endif
}

VOID Thread::stop()
{
	exit(NULL);
}

VOID Thread::exit(VOID* retval)
{
#ifdef __LINUX___
	pthread_detach(pthread_self());
	pthread_exit(retval);
#elif defined __WIN__
	::CloseHandle(m_hThread);
#endif
}


#ifdef __LINUX__
VOID* Thread::MyThreadProcess(VOID* derivedThread)
{
	Thread* thread = (Thread*)derivedThread;
	if(!thread)
	{
		printf("derivedThread is NULL\n");
		return NULL;
	}

	thread->setThreadStatus(Thread::RUNNING);
	thread->run();
	INT	ret = 0;
	thread->exit(&ret);
}
#elif defined __WIN__
ULONG WINAPI Thread::MyThreadProcess(VOID* derivedThread)
{
	Thread* thread = (Thread*)derivedThread;
	if (!thread)
		return 0;

	thread->setThreadStatus(Thread::RUNNING);
	thread->run();
	thread->exit(NULL);
	
	return 0;
}
#endif

VOID Thread::run()
{

}