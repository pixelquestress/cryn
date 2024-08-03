// WaitTimer.cpp: implementation of the CWaitTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "WaitTimer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWaitTimer::CWaitTimer()
{
	start_clock_count = 0;
	Start_Clock();
}

CWaitTimer::~CWaitTimer()
{
}

DWORD CWaitTimer::Get_Clock(void)
{
// this function returns the current tick count

// return time
return(GetTickCount());

} // end Get_Clock

///////////////////////////////////////////////////////////

DWORD CWaitTimer::Start_Clock(void)
{
// this function starts the clock, that is, saves the current
// count, use in conjunction with Wait_Clock()

return(start_clock_count = Get_Clock());

} // end Start_Clock

////////////////////////////////////////////////////////////

DWORD CWaitTimer::Wait_Clock(DWORD count)
{
// this function is used to wait for a specific number of clicks
// since the call to Start_Clock
	Sleep(count);
	return 1;

	/*while((Get_Clock() - start_clock_count) < count);

return(Get_Clock());*/

} // end Wait_Clock

DWORD CWaitTimer::Get_Seconds_Elapsed()
{
	// Returns the number of seconds elapsed since clock started.
	return (Get_Clock() - start_clock_count);
}
