#include "CStatus.h"

BOOL CStatus::Read(SocketInputStream&)
{
	return TRUE;
}

BOOL CStatus::Write(SocketOutputStream&)
{
	return TRUE;
}

BOOL CStatus::Execute()
{
	return TRUE;
}