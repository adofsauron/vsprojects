#include "CPlayerDeath.h"

BOOL CPlayerDeath::Read(SocketInputStream&)
{
	return TRUE;
}

BOOL CPlayerDeath::Write(SocketOutputStream&)
{
	return TRUE;
}

BOOL CPlayerDeath::Execute()
{
	return TRUE;
}