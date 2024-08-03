// WaitTimer.h: interface for the CWaitTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAITTIMER_H__5F588F59_000E_4FF0_B608_05B12E766AB5__INCLUDED_)
#define AFX_WAITTIMER_H__5F588F59_000E_4FF0_B608_05B12E766AB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>   // include important windows stuff

class CWaitTimer  
{
private:
	DWORD start_clock_count;

public:
	CWaitTimer();
	virtual ~CWaitTimer();

	DWORD Get_Clock(void);
	DWORD Start_Clock(void);
	DWORD Wait_Clock(DWORD count);
	DWORD Get_Seconds_Elapsed();
};

#endif // !defined(AFX_WAITTIMER_H__5F588F59_000E_4FF0_B608_05B12E766AB5__INCLUDED_)
